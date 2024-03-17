
#ifndef PSE_PROJECT_DEVICE_H
#define PSE_PROJECT_DEVICE_H

#include <iostream>
#include <vector>
#include "Job.h"
#include <deque>


class Device {
private:
    std::string name;
    int emission;
    int speed;
    std::deque<Job *> jobs;

public:
    //constructors
    Device(const std::string &name, int emission, int speed, const std::deque<Job *>  &jobs);
    explicit Device(TiXmlElement *device_node);
    virtual ~Device();

    //getters and setters
    const std::string &getName() const;
    void setName(const std::string &name);
    int getEmission() const;
    void setEmission(int emission);
    int getSpeed() const;
    void setSpeed(int speed);
    const std::deque<Job *>  &getJobs() const;
    void setJobs(const std::deque<Job *>  &jobs);
    void addJob(Job *job);
    std::string printReport() const;
    void processJob(Job* job) const;
    int getJobBurden() const;


};


#endif //PSE_PROJECT_DEVICE_H
