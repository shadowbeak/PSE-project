
#ifndef PSE_PROJECT_PRINTSYSTEM_H
#define PSE_PROJECT_PRINTSYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml.h"


using namespace std;

class Device;
class Job;

class PrintSystem{
private:
    std::vector<Device *> devices;
    std::vector<Job *> jobs;

public:
    PrintSystem(const vector<Device *> &devices, const vector<Job *> &jobs);
    PrintSystem();
    virtual ~PrintSystem();

    void ReadJob(TiXmlElement *jobElement);
    void ReadDevice(TiXmlElement *deviceElement);
    void Readfile(const string &filename);
    //use_case_2 :
    std::string printReport() const;


    //void clear();
    //void ReadJob(TiXmlElement *job_element);
    //bool Initialization() const { return _init == this; }
    //Device *getFirstDevice() const;
    //Job *getFirstJob() const;
    //Job *getFirstUnfinishedJob() const;
    //Job *getFirstUnprocessedJob() const;
    //const vector<Device *> &getDevices() const;
    //const vector<Job *> &getJobs() const;
    //vector<Job *> getUnfinishedJobs() const;
    //bool isLogErrors() const;
    //void setLogErrors(bool logErrors);
    //bool VerifyConsistency() const;
    //Device *getDeviceWithLeastLoad() const;
    //void processFirstJob() const;

    //atrribute:
    //static bool CheckNotNegative(int num);
    //PrintSystem* _init;
};



#endif //PSE_PROJECT_PRINTSYSTEM_H
