/*#include "../gtest/include/gtest/gtest.h"

#include "PrintSystem.h"
#include "Device.h"
#include "Job.h"
#include "PrintSystemUtils.h"

using namespace std;

class PrintSystemTest: public ::testing::Test {
protected:
    friend class PrintSystem;
    PrintSystem reader;

    //friend class System;
    //System system;
    friend class Device;
    Device device;
    friend class Job;
    Job job;


    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

};




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} */