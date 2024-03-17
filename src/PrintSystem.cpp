//
// Created by noahm on 16/03/2024.
//
#include "PrintSystem.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <random>
#include "PrintSystemUtils.h"
#include "DesignByContract.h"
#include "Device.h"
using namespace std;

PrintSystem::PrintSystem(const vector<Device *> &devices, const vector<Job *> &jobs) : devices(devices), jobs(jobs) {}

PrintSystem::~PrintSystem() {
    for (Device* device : devices) {
        delete device;
    }
    for (Job* job : jobs) {
        delete job;
    }
}
std::string PrintSystem::printReport() const {
    string reportExtension = ".txt";
    string storageDirectory = "reports/";

string filename = constructFilename(storageDirectory,reportExtension);
    std::ofstream report;
    report.open(filename);
    for (size_t i = 0; i < devices.size(); ++i) {
        report << devices[i]->printReport();
        if (i != devices.size() - 1)
            report << "\n";
    }
    report.close();
    return filename;
}


void PrintSystem::Readfile(const string &filename) {        // Reading data from file
    REQUIRE(FileExists(filename), "File does not exist.");  // Checking if file exist

    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str())) {
        cerr << doc.ErrorDesc() << "miauw" << endl;
        return;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if (root == nullptr) {
        cerr << "Failed to read the file: No SYSTEM root." << endl;
        return;
    }
    for (TiXmlElement *elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())
    {
        if (string(elem->Value()) == "DEVICE") {
            ReadDevice(elem);
        } else if (string(elem->Value()) == "JOB") {
            ReadJob(elem);
        }
        else{
            std::cerr << "Unrecognizable element"<<std::endl;
            continue;
        }
    }
    doc.Clear();
}


void PrintSystem::ReadDevice(TiXmlElement *deviceElement) {
    REQUIRE(deviceElement != NULL, "DeviceElement is een null pointer");

    Device* device = new Device(deviceElement);
    devices.push_back(device);

    ENSURE(!devices.empty(), "Er werden geen devices gelezen uit onze xml file.");
}

void PrintSystem::ReadJob(TiXmlElement *jobElement) {
    REQUIRE(jobElement != NULL, "JobElement is een null pointer");

    Job* job = new Job(jobElement);
    jobs.push_back(job);

    ENSURE(!jobs.empty(), "Er werden geen jobs gelezen uit onze xml file.");
}

PrintSystem::PrintSystem() {}










