
#ifndef PSE_PROJECT_DEVICE_H
#define PSE_PROJECT_DEVICE_H

#include <iostream>
#include <vector>
#include "Job.h"
#include <deque>
using namespace std;


class Device {
private:
    string name;
    int emission;
    int speed;
    std::deque<Job *> jobs;

public:
    //constructors
    Device(const string &name, int emission, int speed, const std::deque<Job *>  &jobs);
    explicit Device(TiXmlElement *device_node);
    virtual ~Device();

    //getters and setters
    const string &getName() const;
    void setName(const string &name);
    int getEmission() const;
    void setEmission(int emission);
    int getSpeed() const;
    void setSpeed(int speed);
    const deque<Job *>  &getJobs() const ;
    void setJobs(const deque<Job *>  &jobs);
    void addJob(Job *job);
    string printReport() const;
    string processJob();
    int getJobBurden() const;


};


#endif //PSE_PROJECT_DEVICE_H
