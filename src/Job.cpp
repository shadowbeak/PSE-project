
#include "Job.h"
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include <iostream>



int Job::getJobNumber() const {
    return jobNumber;
}

void Job::setJobNumber(int jobNumber) {
    REQUIRE(!isNegative(jobNumber), "JobNumber mag niet negatief.");
    Job::jobNumber = jobNumber;
}

int Job::getPageCount() const {
    return pageCount;
}

void Job::setPageCount(int pageCount) {
    REQUIRE(!isNegative(pageCount), "PageCount mag niet negatief.");
    Job::pageCount = pageCount;
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

void Job::setUserName(const std::string &userName) {
    Job::userName = userName;
}

Device *Job::getBeingWorkedOnBy() const {
    return beingWorkedOnBy;
}

void Job::setBeingWorkedOnBy(Device *beingWorkedOnBy) {
    Job::beingWorkedOnBy = beingWorkedOnBy;
}
std::string finishMessage();

Job::Job(int jobNumber, int pageCount, const std::string &userName) : jobNumber(jobNumber), pageCount(pageCount),




                                                                      userName(userName) {}


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
    EXPECT(isInt(JN_temp), "JobNumber moet een integer zijn");
    jobNumber = std::stoi(JN_temp);

    EXPECT(!PC_temp.empty(), "Geen pageCount opgegeven.");
    EXPECT(isInt(PC_temp), "PageCount moet een integer zijn");
    pageCount = std::stoi(PC_temp);

    EXPECT(!UN_temp.empty(), "Geen userName opgegeven.");
    userName = UN_temp;
}

string Job::EndMessage() const {
    REQUIRE(beingWorkedOnBy != NULL, "Job is not assigned to a device");

    return R"(Printer ")" + beingWorkedOnBy->getName() + R"(" finished job:
    Number: )" + std::to_string(jobNumber) + R"(
    Submitted by ")" + userName + R"("
    )" + std::to_string(pageCount) + " pages\n";
}









Job::~Job() {}
