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


//check inconsistency:
/*TEST_F(TestPrintSystem, InconsistentSystem){
    system->Readfile("xmlTests/InconsistentSystemTest.xml");
    EXPECT_FALSE(system->checkSystem());
}

TEST_F(TestPrintSystem, InconsistentDevices){
    system->Readfile("xmlTests/InconsistentDevicesTest.xml");
    EXPECT_TRUE(system->checkDevices());
}

TEST_F(TestPrintSystem, InconsistentJobs){
    system->Readfile("xmlTests/InconsistentJobsTest.xml");
    EXPECT_FALSE(system->checkJobs());
}*/


//Jobs:
TEST_F(TestPrintSystem, NoPageCount){
    system->Readfile("xmlTests/NoPageCount.xml");
    //Job* job = system->getJobs()[1];
    //ASSERT_EQ(job->getPageCount(),NULL);
    EXPECT_TRUE(system->getJobs().empty());
    EXPECT_TRUE(system->getDevices().size() == 1);
}

TEST_F(TestPrintSystem, PageCountIsNeg){
    system->Readfile("xmlTests/PageCountIsNeg.xml");
    EXPECT_TRUE(system->getJobs().size() == 1);
    EXPECT_TRUE(system->getDevices().size() == 1);
}

TEST_F(TestPrintSystem, NoJobNumber){
    system->Readfile("xmlTests/NoJobNumber.xml");
    EXPECT_TRUE(system->getJobs().size() == 1);
    EXPECT_TRUE(system->getDevices().size() == 1);

}
TEST_F(TestPrintSystem, JobNumberIsNeg){
    system->Readfile("xmlTests/JobNumberIsNeg.xml");
    EXPECT_TRUE(system->getJobs().empty());
    EXPECT_TRUE(system->getDevices().size() == 1);
}

TEST_F(TestPrintSystem, NoUserName){
    system->Readfile("xmlTests/NoUsername.xml");
    EXPECT_TRUE(system->getJobs().size() == 1);
    EXPECT_TRUE(system->getDevices().size() == 1);
}


//Devices:
TEST_F(TestPrintSystem, NoSpeed) {
    system->Readfile("xmlTests/NoSpeed.xml");
    EXPECT_TRUE(system->getJobs().size() == 1);
    EXPECT_TRUE(system->getDevices().size() == 1);
}

TEST_F(TestPrintSystem, SpeedIsNeg) {
    system->Readfile("xmlTests/SpeedIsNeg.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().empty() );
}

TEST_F(TestPrintSystem, NoEmission){
    system->Readfile("xmlTests/NoEmission.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().size() == 1);
}

TEST_F(TestPrintSystem, EmissionIsNeg){
    system->Readfile("xmlTests/EmissionIsNeg.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().empty());
}

TEST_F(TestPrintSystem, NoName){
    system->Readfile("xmlTests/NoName.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().size() == 1);
}


//Reports:
TEST_F(TestPrintSystem, checkPrintReport){
    system->Readfile("xmlTests/ReportPrintTest.xml");
    system->assignALL();
    std::string fileReport = system->printReport();
    EXPECT_TRUE(FileCompare(fileReport, "TEST/ReportPrintTest.txt"));
}

TEST_F(TestPrintSystem, checkEmptyReport){
    std::string fileReport = system->printReport();
    EXPECT_TRUE(FileCompare(fileReport, "TEST/EmptyReport.txt"));
}

//assignTests:
TEST_F(TestPrintSystem, checkAssignment) {
    system->Readfile("xmlTests/checkAssignment.xml");
    const std::string regex = "Assertion failed: Geen apparaten gevonden, file C:/Users/adamb/CLionProjects/PSE-projectxe/src/PrintSystem.cpp, line 126";
    EXPECT_DEATH(system->assignALL(), regex);
}

//fileOpeningTest:
TEST_F(TestPrintSystem, cantOpen){
    const std::string regex = "Assertion failed: Bestand bestaat niet., file C:/Users/adamb/CLionProjects/PSE-projectxe/src/PrintSystem.cpp, line 42";
    EXPECT_DEATH(system->Readfile("xmlTests/FileDoesNotExist.xml"), regex);
}













int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // to allow for threadsafe death tests
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}

