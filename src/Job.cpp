
#include "Job.h"
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include <iostream>
#include <sstream>




int Job::getJobNumber() const {
    return jobNumber;
}


int Job::getPageCount() const {
    return pageCount;
}


bool Job::isFinished() const {
    return finished;
}

void Job::setFinished(bool finished) {
    Job::finished = finished;
}

bool Job::isInProcess() const {
    return inProcess;
}

void Job::setInProcess(bool inProcess) {
    Job::inProcess = inProcess;
}

const std::string &Job::getUserName() const {
    return userName;
}


Device *Job::getBeingWorkedOnBy() const {
    return beingWorkedOnBy;
}

void Job::setBeingWorkedOnBy(Device *beingWorkedOnBy) {
    Job::beingWorkedOnBy = beingWorkedOnBy;
}

Job::Job(int jobNumber, int pageCount, const std::string &userName) : jobNumber(jobNumber), pageCount(pageCount), userName(userName) {}


Job::Job(TiXmlElement *job_element) {
    std::string JN_temp;
    std::string PC_temp;
    std::string UN_temp;

    TiXmlNode *node = job_element->FirstChild();
    while (node != NULL) {

        TiXmlNode *childNode = node->FirstChild();
        if (childNode != NULL) {

            std::string nodeName = node->Value();
            std::string nodeValue = childNode->Value();

            if (nodeName == "jobNumber") {
                JN_temp = nodeValue;

            } else if (nodeName == "pageCount") {
                PC_temp = nodeValue;

            } else if (nodeName == "userName") {
                UN_temp = nodeValue;
            } else {
                EXPECT(false, "Onbekend attribuut voor Taak: '" + nodeName + "'");
            }
        }
        node = node->NextSibling();
    }

    EXPECT(!JN_temp.empty(), "Geen jobNumber opgegeven.");
    EXPECT(isInt(JN_temp), "JobNumber moet een integer zijn.");
    EXPECT(!isNegativeInt(JN_temp), "JobNumber mag niet negatief zijn.");
    jobNumber = std::stoi(JN_temp);


    EXPECT(!PC_temp.empty(), "Geen pageCount opgegeven.");
    EXPECT(isInt(PC_temp), "PageCount moet een integer zijn");
    EXPECT(!isNegativeInt(PC_temp), "PageCount mag niet negatief zijn.");
    pageCount = std::stoi(PC_temp);


    EXPECT(!UN_temp.empty(), "Geen userName opgegeven.");
    userName = UN_temp;
}

std::string Job::EndMessage() const{

    REQUIRE(getBeingWorkedOnBy() != NULL, "Job is not assigned to a device");

    std::stringstream endmessage;

    endmessage << "Printer " << '"' << getBeingWorkedOnBy()->getName() << '"' << " finished job:" << std::endl;
    endmessage << "\tNumber: " << jobNumber << std::endl;
    endmessage << "\tSubmitted by " << '"' << userName << '"' << std::endl;
    endmessage << "\t" << pageCount << " pages" << std::endl;
    cout << endmessage.str() << endl;
    return endmessage.str();
}




Job::~Job() {}
