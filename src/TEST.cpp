#include <gtest/gtest.h>
#include "PrintSystem.h"
#include "PrintSystemUtils.h"

class TestPrintSystem : public ::testing::Test {
protected:
    PrintSystem *system{};

    void SetUp() override {
        system = new PrintSystem();
    }
    void TearDown() override {
        delete system;
    }
};



//Jobs:
TEST_F(TestPrintSystem, NoPageCount){
    system->Readfile("xmlTest/noSpeed.xml");
    EXPECT_TRUE(system->getDevices().empty());
}

TEST_F(TestPrintSystem, NoJobNumber){
    system->Readfile("xmlTest/noSpeed.xml");
    EXPECT_TRUE(system->getDevices().empty());
}

TEST_F(TestPrintSystem, NoUserName){
    system->Readfile("xmlTest/noSpeed.xml");
    EXPECT_TRUE(system->getDevices().empty());
}

//Devices:
TEST_F(TestPrintSystem, NoSpeed){
    system->Readfile("xmlTest/noSpeed.xml");
    EXPECT_TRUE(system->getDevices().empty());
}

TEST_F(TestPrintSystem, NoEmission){
    system->Readfile("xmlTest/NoEmission.xml");
    EXPECT_TRUE(system->getDevices().empty());
}

TEST_F(TestPrintSystem, NoName){
    system->Readfile("xmlTest/noSpeed.xml");
    EXPECT_TRUE(system->getDevices().empty());
}


//Reports:
TEST_F(TestPrintSystem, checkPrintReport){
    system->Readfile("xmlTest/reportCheck");
    system->getDevices()[0]->addJob(system->getJobs()[0]);
    system->getDevices()[1]->addJob(system->getJobs()[1]);
    system->getDevices()[2]->addJob(system->getJobs()[2]);
    std::string fileReport = system->printReport();
    std::string fileToCompare = "reportTest/reportTest1";
    EXPECT_TRUE(FileCompare(fileReport, fileToCompare));

}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // to allow for threadsafe death tests
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}

