#include "Device.h"
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include <sstream>





Device::Device(const std::string &name, int emission, int speed, const std::deque<Job *> &jobs) : name(name),emission(emission),speed(speed),jobs(jobs) {}
Device::Device(TiXmlElement *device_node) {
    std::string NA_temp;
    std::string EM_temp;
    std::string SP_temp;

    TiXmlNode *node = device_node->FirstChild();
    while (node != nullptr) {

        if (node->FirstChild() == nullptr) {
            node = node->NextSibling();
            continue;
        }

        std::string nodeName = node->Value();
        std::string nodeValue = node->FirstChild()->Value();

        if (nodeName == "name") {
            NA_temp = nodeValue;
        } else if (nodeName == "emission") {
            EM_temp = nodeValue;
        } else if (nodeName == "speed") {
            SP_temp = nodeValue;
        } else {
            EXPECT(false, "Unknown attribute for Device: '" + nodeName + "'");
        }

        node = node->NextSibling();
    }

    EXPECT(!NA_temp.empty(), "Geen name opgegeven.");
    name = NA_temp;

    EXPECT(!EM_temp.empty(), "Geen emission opgegeven.");
    EXPECT(isInt(EM_temp) , "Emission moet een integer zijn.");
    emission = std::stoi(EM_temp);

    EXPECT(!SP_temp.empty(), "Geen speed opgegeven.");
    EXPECT(isInt(SP_temp) , "Speed moet een integer zijn.");
}

Device::~Device() {}

//getters and setters
const std::string &Device::getName() const {
    return name;
}

void Device::setName(const std::string &name) {
    Device::name = name;
}

int Device::getEmission() const {
    return emission;
}

void Device::setEmission(int emission) {
    REQUIRE(!isNegative(emission), "Emission mag niet negatief zijn.");
    Device::emission = emission;
}

int Device::getSpeed() const {
    return speed;
}

void Device::setSpeed(int speed) {
    REQUIRE(!isNegative(speed), "Speed mag niet negatief zijn.");
    Device::speed = speed;
}

const std::deque<Job *>  &Device::getJobs() const {
    return jobs;
}

void Device::setJobs(const std::deque<Job *>  &jobs) {
    Device::jobs = jobs;

}

void Device::addJob(Job *job) {
    REQUIRE(isNotInDevice(job, jobs), "job heeft jobnummer die al aanwezig is in onze device");
    jobs.push_back(job);
    ENSURE(jobs.back() == job, "Job is niet toegevoegd aan de device.");
}

std::string Device::printReport() const {
    std::stringstream report;

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
    ENSURE(jobBurden < 0, "Onze burden is negatief." );

}
















void Device::processJob(Job* job) const {
    // Check if the job and device are valid
    REQUIRE(job != NULL, "Invalid job");

    // Get job details
    int jobNumber = job->getJobNumber();
    int pageCount = job->getPageCount();
    std::string userName = job->getUserName();

    // Print each page
    for (int i = 1; i <= pageCount; ++i) {
        std::cout << "Printing page " << i << " of job number " << jobNumber << " submitted by \"" << userName << "\"" << std::endl;
    }

    // Print job completion message
    std::cout << "Printer \"" << this->getName() << "\" finished job:" << std::endl;
    std::cout << "Number: " << jobNumber << std::endl;
    std::cout << "Submitted by \"" << userName << "\"" << std::endl;
    std::cout << pageCount << " pages" << std::endl;

    // Set the job as finished
    job->setFinished(true);

    // Ensure postcondition
    ENSURE(job->isFinished(), "Job is not finished");
}


