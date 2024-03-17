//
// Created by noahm on 16/03/2024.
//

#ifndef PSE_PROJECT_PRINTSYSTEM_H
#define PSE_PROJECT_PRINTSYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml.h"
#include "Device.h"
#include "Job.h"

static const std::string REPORT_FILE_EXTENSION = ".txt";
using namespace std;

class PrintSystem
{
public:
    PrintSystem();
    virtual ~PrintSystem();

    void clear();

    void Readfile(const string &filename);

    void ReadDevice(TiXmlElement *device_element);

    void ReadJob(TiXmlElement *job_element);

    bool Initialization() const { return _init == this; }


    Device *getFirstDevice() const;

    Job *getFirstJob() const;

    Job *getFirstUnfinishedJob() const;

    Job *getFirstUnprocessedJob() const;

    const vector<Device *> &getDevices() const;

    const vector<Job *> &getJobs() const;

    vector<Job *> getUnfinishedJobs() const;

    bool isLogErrors() const;

    void setLogErrors(bool logErrors);

    string printReport() const;

    bool VerifyConsistency() const;

    Device *getDeviceWithLeastLoad() const;



    void processFirstJob() const;

private:
    static bool CheckNotNegative(int num);

private:
    PrintSystem* _init;
    std::vector<Device *> devices;
    std::vector<Job *> jobs;
    bool log_errors;
};



#endif //PSE_PROJECT_PRINTSYSTEM_H
