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
using namespace std;



PrintSystem::PrintSystem() {

}

PrintSystem::~PrintSystem() {
    std::for_each(devices.begin(), devices.end(), [](Device *device) {
        delete device;  // Assuming Device has a virtual destructor
    });

    std::for_each(jobs.begin(), jobs.end(), [](Job *job) {
        delete job;     // Assuming Job is allocated with new
    });

    devices.clear();  // No need to set pointers to NULL
    jobs.clear();
    clear();
}



std::string PrintSystem::printReport() const {

string filename ="adam";
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
    if (!doc.LoadFile("filename")) {
        cerr << doc.ErrorDesc() << endl;
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

    VerifyConsistency();
    doc.Clear();
}

void PrintSystem::ReadDevice(TiXmlElement *device_element) {
    // Check if device_element is not NULL
    REQUIRE(device_element != nullptr, "device_element is a NULL pointer");

    try {
        // Attempt to create a new Device object
        Device* device = new Device(device_element);
        devices.push_back(device);

        // Ensure that devices vector is not empty after reading XML file
        ENSURE(!devices.empty(), "No devices were read after reading xml file");
    }
    catch (const std::runtime_error& error) {
        // Handle runtime errors
        switch (log_errors) {
            case true:
                std::cerr << error.what() << std::endl;
                break;
            case false:
                // If logging errors is disabled, just return
                return;
        }
    }
}







