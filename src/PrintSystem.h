
#ifndef PSE_PROJECT_PRINTSYSTEM_H
#define PSE_PROJECT_PRINTSYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml.h"
using namespace std;


static const string reportExtension = ".txt";
static const string storageDirectory = "reports/";

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
    Device* getLeastBurdened() const;
    Device* deviceAssignment(Job *job) const;
    void assignEverything() const;
    void processFirstJob() const;

    Job *getFirstJob() const;
    Job *getFirstUnprocessedJob() const;

    bool checkJobs()const;
    bool checkDevices()const;
    bool checkSystem()const;





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
