
#include "Device.h"
#include "PrintSystemUtils.h"
#include "DesignByContract.h"




Device::Device(const std::string &name, int emission, int speed, const std::vector<Job *> &jobs) : name(name),emission(emission),speed(speed),jobs(jobs) {}

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

const std::vector<Job *> &Device::getJobs() const {
    return jobs;
}

void Device::setJobs(const std::vector<Job *> &jobs) {
    Device::jobs = jobs;

}

void Device::addJob(Job *job) {
    REQUIRE(isNotInDevice(job, jobs), "job heeft jobnummer die al aanwezig is in onze device");
    jobs.push_back(job);
    ENSURE(jobs.back() == job, "Job is niet toegevoegd aan de device.");
}

