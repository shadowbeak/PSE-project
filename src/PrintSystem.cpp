#include "PrintSystem.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include "Device.h"


using namespace std;
// constructor
PrintSystem::PrintSystem() {}

// Destructor
PrintSystem::~PrintSystem() {
    for (Device* &device : devices) {
        delete device;
    }
    devices.clear();
    for (Job* &job : jobs) {
        delete job;
    }
    jobs.clear();
}

// Functie om rapport af te drukken
// Genereert een rapportbestand met apparaatinformatie
std::string PrintSystem::printReport() const {
    string filename = constructFilename(reportDirectory,reportExtension, reportFileName);
    ofstream report;
    report.open(filename);
    for (size_t i = 0; i < devices.size(); ++i) {
        report << devices[i]->printReport();
        if (i != devices.size() - 1)
            report << "\n";
    }
    report.close();
    return filename;
}





// Functie om gegevens uit het bestand te lezen
void PrintSystem::Readfile(const string &filename) {
    REQUIRE(FileExists(filename), "Bestand bestaat niet.");

    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        cerr << doc.ErrorDesc() << endl;
        return;
    }




    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        cerr << "Fout bij het lezen van het bestand: Geen SYSTEM-root." << endl;
        return;
    }
    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        if (string(elem->Value()) == "DEVICE") {
            ReadDevice(elem);
        } else if (string(elem->Value()) == "JOB") {
            ReadJob(elem);
        } else {
            std::cerr << "Onherkenbaar element" << std::endl;
            continue;
        }

    }
    checkSystem();
    doc.Clear();
}




// Functie om een apparaat uit XML te lezen
void PrintSystem::ReadDevice(TiXmlElement *deviceElement) {
    REQUIRE(deviceElement != NULL, "DeviceElement is een null pointer");

    try{Device* device = new Device(deviceElement);
        devices.push_back(device);
        ENSURE(!devices.empty(), "Er werden geen apparaten gelezen uit ons XML-bestand.");
    }       catch (const std::runtime_error& error) {
        cerr << error.what()<<endl;
    }
}


// Functie om een taak uit XML te lezen
void PrintSystem::ReadJob(TiXmlElement *jobElement) {
    REQUIRE(jobElement != NULL, "JobElement is een null pointer");

    try{Job* job = new Job(jobElement);
        jobs.push_back(job);
        ENSURE(!jobs.empty(), "Er werden geen taken gelezen uit ons XML-bestand.");
    }       catch (const std::runtime_error& error) {
        cerr << error.what() <<endl;
    }
}

// Functie om het minst belaste apparaat op te halen
Device* PrintSystem::getLeastBurdened() const {
    REQUIRE(!devices.empty(), "Geen apparaten gevonden.");

    // Initialiseer het minst belaste apparaat met het eerste apparaat
    Device* leastBurdenedDevice = devices.front();

    // Doorloop alle apparaten en werk het minst belaste apparaat bij indien nodig
    for (std::vector<Device*>::const_iterator it  = devices.begin() + 1; it != devices.end(); ++it) {
        if ((*it)->getJobBurden() < leastBurdenedDevice->getJobBurden()) {
            leastBurdenedDevice = *it;
        }
    }

    return leastBurdenedDevice;
}

// Functie om taak aan apparaat toe te wijzen
Device* PrintSystem::deviceAssignment(Job *job) const {
    REQUIRE(!devices.empty(), "Er werden geen apparaten gevonden");
    REQUIRE(job->getBeingWorkedOnBy() == NULL, "Er wordt al aan deze taak gewerkt op een ander apparaat.");

    Device* device = getLeastBurdened();
    device->addJob(job);
    job ->setBeingWorkedOnBy(device);
    return device;
}

// Functie om alle taken aan apparaten toe te wijzen
void PrintSystem::assignALL() const {
    REQUIRE(!devices.empty(), "Geen apparaten gevonden");
    REQUIRE(!jobs.empty(), "Geen taken gevonden");

    for(Job* job: jobs){
        if(job->getBeingWorkedOnBy() == NULL){
            deviceAssignment(job);
        }
    }
}

// Functie om de eerste niet-verwerkte taak te verwerken
void PrintSystem::processFirstJob() const {
    // Voorwaarden
    REQUIRE(!jobs.empty(), "Geen taken gevonden");
    REQUIRE(!devices.empty(), "Geen apparaten gevonden");
    REQUIRE(getNextPendingJob() != NULL, "Alle taken zijn verwerkt");
    REQUIRE(getNextPendingJob()->getBeingWorkedOnBy() != NULL, "Taak is niet toegewezen aan een apparaat");

    // Haal de eerste onverwerkte taak en het toegewezen apparaat op
    Job *job = getNextPendingJob();
    Device *device = job->getBeingWorkedOnBy();

    // Bewaar de initiële belasting van het apparaat
    int initialBurden = device->getJobBurden();

    // Stel de taak in als zijn de verwerkt
    job->setInProcess(true);

    // Verwerk de taak op het toegewezen apparaat en genereer een bericht
    std::string bericht = device->processJob();

    // Construeer de bestandsnaam voor het schrijven van het bericht naar een bestand
    std::string bestandsnaam = constructFilename(processDirectory, processExtension, processFileName);

    // Schrijf het bericht naar een bestand
    std::ofstream outputFile(bestandsnaam, std::ios_base::app);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Kan het bestand niet openen.");
    }

    try {
        outputFile << bericht << std::endl;
        outputFile.close();
        std::cout << "Bericht succesvol naar bestand geschreven." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fout tijdens het schrijven naar het bestand: " << e.what() << std::endl;
        outputFile.close(); // Sluit het bestand voordat de uitzondering opnieuw wordt gegenereerd
    }

    // Naverzekeringsvoorwaarden
    ENSURE(job->isFinished(), "Taak is niet voltooid");
    ENSURE(job->getBeingWorkedOnBy()->getJobBurden() != initialBurden, "Apparaat heeft de taak niet verwerkt");
}


// Functie om te controleren of alle attributen van taken en apparaten niet-negatief zijn
bool PrintSystem::checkJobs() const {
    for (Job* const& job:jobs) {
        if (isNegative(job->getJobNumber())) {
            return false;
        } else if (isNegative(job->getPageCount())) {
            return false;
        }
    }
    return true;
}

bool PrintSystem::checkDevices() const {
    for (Device* const& device:devices) {
        if (isNegative(device->getSpeed())) {
            return false;
        } else if (isNegative(device->getEmission())) {
            return false;
        }
    }
    return true;
}

// Functie om te controleren of het systeem geldig is
bool PrintSystem::checkSystem() const {
    if (checkJobs() && checkDevices()) {
        return true;
    }
    return false;
}

// Functie om de eerste niet-verwerkte taak op te halen
Job *PrintSystem::getNextPendingJob() const {
    REQUIRE(!jobs.empty(), "Geen taken gevonden");
    for (Job *job : jobs) {
        if (!job->isFinished() && !job->isInProcess()) {
            return job;
        }
    }
    return NULL;
}
//
const vector<Device *> &PrintSystem::getDevices() const {
    return devices;
}

const vector<Job *> &PrintSystem::getJobs() const {
    return jobs;
}
