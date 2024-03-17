
#ifndef PSE_PROJECT_DEVICE_H
#define PSE_PROJECT_DEVICE_H

#include <iostream>
#include <vector>
#include "Job.h"
#include "PrintSystemUtils.h"
#include "DesignByContract.h"


class Device {
private:
    std::string name;
    int emission;
    int speed;
    std::vector<Job*> jobs;
public:
    //constructors
    Device(const std::string &name, int emission, int speed, const std::vector<Job *> &jobs);
    explicit Device(TiXmlElement *device_node);

    //getters and setters
    const std::string &getName() const;
    void setName(const std::string &name);
    int getEmission() const;
    void setEmission(int emission);
    int getSpeed() const;
    void setSpeed(int speed);
    const std::vector<Job *> &getJobs() const;
    void setJobs(const std::vector<Job *> &jobs);
    void addJob(Job *job);
};


#endif //PSE_PROJECT_DEVICE_H
