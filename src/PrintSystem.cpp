//
// Created by noahm on 16/03/2024.
//
#include "PrintSystem.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include "Device.h"
using namespace std;

PrintSystem::PrintSystem(const vector<Device *> &devices, const vector<Job *> &jobs) : devices(devices), jobs(jobs) {}

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


std::string PrintSystem::printReport() const {


string filename = constructFilename("reports/",".txt", "report_");
    std::ofstream report;
    report.open(filename);
    for (size_t i = 0; i < devices.size(); ++i) {
        report << devices[i]->printReport();
        if (i != devices.size() - 1)
            report << "\n";
    }
    report.close();
    return filename;
}


void PrintSystem::Readfile(const string &filename) {        // Reading data from file
    REQUIRE(FileExists(filename), "File does not exist.");  // Checking if file exist

    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        cerr << doc.ErrorDesc() << endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        cerr << "Failed to read the file: No SYSTEM root." << endl;
        return;
    }
    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        if (string(elem->Value()) == "DEVICE") {
            ReadDevice(elem);
        } else if (string(elem->Value()) == "JOB") {
            ReadJob(elem);
        }
        else{
            std::cerr << "Unrecognizable element"<<std::endl;
            continue;
        }
    }
    checkSystem();
    doc.Clear();
}





void PrintSystem::ReadDevice(TiXmlElement *deviceElement) {
    REQUIRE(deviceElement != NULL, "DeviceElement is een null pointer");

    Device* device = new Device(deviceElement);
    devices.push_back(device);

    ENSURE(!devices.empty(), "Er werden geen devices gelezen uit onze xml file.");
}

void PrintSystem::ReadJob(TiXmlElement *jobElement) {
    REQUIRE(jobElement != NULL, "JobElement is een null pointer");

    Job* job = new Job(jobElement);
    jobs.push_back(job);

    ENSURE(!jobs.empty(), "Er werden geen jobs gelezen uit onze xml file.");
}

Device* PrintSystem::getLeastBurdened() const {
    REQUIRE(!devices.empty(), "No devices were found.");

    // Initialize the least burdened device with the first device
    Device* leastBurdenedDevice = devices.front();

    // Iterate through all devices and update the least burdened device if necessary
    for (std::vector<Device*>::const_iterator it  = devices.begin() + 1; it != devices.end(); ++it) {
        if ((*it)->getJobBurden() < leastBurdenedDevice->getJobBurden()) {
            leastBurdenedDevice = *it;
        }
    }

    return leastBurdenedDevice;
}



Device* PrintSystem::deviceAssignment(Job *job) const{
    REQUIRE(!devices.empty(), "Er werden geen devices gevonden");
    REQUIRE(job->getBeingWorkedOnBy() == NULL, "Er wordt al aan deze job gewerkt in een ander device.");

    Device* device = getLeastBurdened();
    device->addJob(job);
    job ->setBeingWorkedOnBy(device);
    return device;
}

void PrintSystem::assignEverything() const{
    REQUIRE(!devices.empty(), "No devices were found");
    REQUIRE(!jobs.empty(), "No jobs were found");

    for(Job* job: jobs){
        if(job->getBeingWorkedOnBy() == NULL){
            deviceAssignment(job);
        }
    }
}


Job *PrintSystem::getFirstUnprocessedJob() const
{
    REQUIRE(!jobs.empty(), "No jobs were found");
    for(Job *job : jobs){
        if(!job->isFinished() && !job->isInProcess()) {
            return job;
        }
    }
    return NULL;
}


bool PrintSystem::checkJobs()const{
    for(Job* const& job:jobs){
        if(isNegative(job->getJobNumber())){
            return false;
        }
        else if(isNegative(job->getPageCount())){
            return false;
        }
    }
    return true;
}

bool PrintSystem::checkDevices()const{
    for (Device* const& device:devices){
        if(isNegative(device->getSpeed())){
            return false;
        }
        else if(isNegative(device->getEmission())){
            return false;
        }
    }
    return true;
}

bool PrintSystem::checkSystem()const{
    if(checkJobs() && checkDevices()){
        return true;
    }
    return false;
}






void PrintSystem::processFirstJob() const {
    // Voorwaarden
    REQUIRE(!jobs.empty(), "Geen taken gevonden");
    REQUIRE(!devices.empty(), "Geen apparaten gevonden");
    REQUIRE(getFirstUnprocessedJob() != NULL, "Alle taken zijn verwerkt");
    REQUIRE(getFirstUnprocessedJob()->getBeingWorkedOnBy() != NULL, "Taak is niet toegewezen aan een apparaat");

    // Haal de eerste onverwerkte taak en het toegewezen apparaat op
    Job *job = getFirstUnprocessedJob();
    Device *device = job->getBeingWorkedOnBy();

    // Bewaar de initiële belasting van het apparaat
    int initiëleBelasting = device->getJobBurden();

    // Stel de taak in als zijnde verwerkt
    job->setInProcess(true);

    // Verwerk de taak op het toegewezen apparaat en genereer een bericht
    std::string bericht = device->processJob();

    // Construeer de bestandsnaam voor het schrijven van het bericht naar een bestand
    std::string bestandsnaam = constructFilename("procescases/", ".txt", "proces_");

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
        throw; // Gooi de gevangen uitzondering opnieuw om verder te verspreiden
    }

    // Naverzekeringsvoorwaarden
    ENSURE(job->isFinished(), "Taak is niet voltooid");
    ENSURE(job->getBeingWorkedOnBy()->getJobBurden() != initiëleBelasting, "Apparaat heeft de taak niet verwerkt");
}




PrintSystem::PrintSystem() {}











