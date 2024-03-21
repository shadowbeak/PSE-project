#include "Device.h"
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include <sstream>
#include <thread>

#include <random>





Device::Device(const string &name, int emission, int speed, const std::deque<Job *> &jobs) : name(name),emission(emission),speed(speed),jobs(jobs) {}

Device::Device(TiXmlElement *device_node) {
    string NA_temp;
    string EM_temp;
    string SP_temp;

    TiXmlNode *node = device_node->FirstChild();
    while (node != nullptr) {

        if (node->FirstChild() == nullptr) {
            node = node->NextSibling();
            continue;
        }

        string nodeName = node->Value();
        string nodeValue = node->FirstChild()->Value();

        if (nodeName == "name") {
            NA_temp = nodeValue;
        } else if (nodeName == "emission") {
            EM_temp = nodeValue;
        } else if (nodeName == "speed") {
            SP_temp = nodeValue;

        } else {
            EXPECT(false, "Onbekend attribuut voor Device: '" + nodeName + "'");
        }

        node = node->NextSibling();
    }

    EXPECT(!NA_temp.empty(), "Geen name opgegeven.");
    name = NA_temp;

    EXPECT(!EM_temp.empty(), "Geen emission opgegeven.");
    EXPECT(isInt(EM_temp) , "Emission moet een integer zijn.");
    EXPECT(!isNegativeInt(EM_temp), "Emission mag niet negatief zijn");
    emission = stoi(EM_temp);


    EXPECT(!SP_temp.empty(), "Geen speed opgegeven.");
    EXPECT(isInt(SP_temp) , "Speed moet een integer zijn.");
    EXPECT(!isNegativeInt(SP_temp), "Speed mag niet negatief zijn");
    speed = stoi(SP_temp);
}

Device::~Device() {}

//getters and setters
const string &Device::getName() const {
    return name;
}



int Device::getEmission() const {
    return emission;
}



int Device::getSpeed() const {
    return speed;
}




void Device::addJob(Job *job) {
    REQUIRE(isNotInDevice(job, jobs), "job heeft jobnummer die al aanwezig is in onze device");
    jobs.push_back(job);
    ENSURE(jobs.back() == job, "Job is niet toegevoegd aan de device.");
}

string Device::printReport() const {
    try{
        EXPECT(emission >= 0, "Emission is negatief.");
        EXPECT(speed >= 0, "Speed is negatief.");
    }catch(const std::runtime_error& error){
        std::cerr << error.what();
    }

    stringstream report;

    report << name << " (CO2: " << emission << "g/page):" << std::endl;

    if (!jobs.empty()) {
        report << "\t* Current:" << std::endl;
        report << "\t\t[#" << jobs.front()->getJobNumber() << "|" << jobs.front()->getUserName() << "]" << std::endl;

        if (jobs.size() > 1) {
            report << "\t* Queue:" << std::endl;
            for (std::vector<Job*>::size_type i = 1; i < jobs.size(); i++) {
                Job* job = jobs[i];
                report << "\t\t[#" << job->getJobNumber() << "|" << job->getUserName() << "]" << std::endl;
            }
        }
    } else {
        report << "\tNo jobs" << std::endl;
    }
    return report.str();
}

int Device::getJobBurden() const{
    int jobBurden = 0;
    for(Job* job: jobs){
        int addBurden = job->getPageCount();
        jobBurden += addBurden;
    }
    ENSURE(jobBurden >= 0, "Onze burden is negatief." );
    return jobBurden;
}




string Device::processJob() {
    // Check if the job and device are valid
    REQUIRE(jobs.front() != NULL, "Invalid job");

    // De te verwerken taak ophalen
    Job* job = jobs.front();

    // Simuleer verwerkingstijd op basis van factoren
    int verwerkingsTijdMs = 0;

    // verwerkingstijd in seconden
    int speedInSecondsPerPage = speed * 60;

    // Bereken de verwerkingstijd in milliseconden
    verwerkingsTijdMs += (job->getPageCount() / speedInSecondsPerPage) * 1000;

    // Simuleer verwerking met wachttijd
    std::this_thread::sleep_for(std::chrono::milliseconds(verwerkingsTijdMs));

    // Werkstatus bijwerken
    job->setInProcess(false);
    job->setFinished(true);
    jobs.pop_front();


    // Ensure postcondition
    ENSURE(job->isFinished(), "Job is not finished yet");


    return job->EndMessage();
}


