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

    for (TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement())
    {

        string elemName = elem->Value();
        if (elemName == "DEVICE")
            ReadDevice(elemName)
    }

    VerifyConsistency();
    doc.Clear();
}




