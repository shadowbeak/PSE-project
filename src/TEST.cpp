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
    system->Readfile("xmlTests/NoPageCount.xml");

    system->getDevices()[0]->addJob(system->getJobs()[0]);
    system->getDevices()[0]->addJob(system->getJobs()[1]);

    std::string NoPageCountReport = system->printReport();
    EXPECT_TRUE(FileCompare(NoPageCountReport, "TESTS/NPCtest.txt"));

}



TEST_F(TestPrintSystem, NoJobNumber){

}

TEST_F(TestPrintSystem, NoUserName){
}


//Devices:
TEST_F(TestPrintSystem, NoSpeed) {

}

TEST_F(TestPrintSystem, NoEmission){

}

TEST_F(TestPrintSystem, NoName){
}


//Reports:
TEST_F(TestPrintSystem, checkPrintReport){


}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // to allow for threadsafe death tests
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}

