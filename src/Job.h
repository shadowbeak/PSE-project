
#ifndef PSE_PROJECT_JOB_H
#define PSE_PROJECT_JOB_H

#include <iostream>
#include "tinyxml.h"

class Device;

class Job {
private:
    int jobNumber;
    int pageCount;
    std::string userName;
    bool finished = false;
    bool inProcess = false;
    Device* beingWorkedOnBy = NULL;

public:
    //constructors en destructor
    Job(int jobNumber, int pageCount, const std::string &userName);
    explicit Job(TiXmlElement *jobElement);
    virtual ~Job();

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

    Device *getBeingWorkedOnBy() const;

    void setBeingWorkedOnBy(Device *beingWorkedOnBy);


};


#endif //PSE_PROJECT_JOB_H
