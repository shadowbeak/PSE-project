
#ifndef PSE_PROJECT_JOB_H
#define PSE_PROJECT_JOB_H

#include <iostream>
#include "tinyxml.h"
#include "DesignByContract.h"
#include "PrintSystemUtils.h"

class Job {
private:
    int jobNumber;
    int pageCount;
    bool finished = false;
    bool inProcess = false;
    std::string userName;
public:
    Job(int jobNumber, int pageCount, const std::string &userName);
    explicit Job(TiXmlElement *jobElement);


    //getters and setters
    int getJobNumber() const;
    void setJobNumber(int jobNumber);
    int getPageCount() const;
    void setPageCount(int pageCount);
    bool isFinished() const;
    void setFinished(bool finished);
    bool isInProcess() const;
    void setInProcess(bool inProcess);
    const std::string &getUserName() const;
    void setUserName(const std::string &userName);




};


#endif //PSE_PROJECT_JOB_H
