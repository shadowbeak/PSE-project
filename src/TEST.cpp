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

/*system->Readfile("xmlTests/NoPageCount.xml");

system->getDevices()[0]->addJob(system->getJobs()[0]);
system->getDevices()[0]->addJob(system->getJobs()[1]);

std::string NoPageCountReport = system->printReport();
EXPECT_TRUE(FileCompare(NoPageCountReport, "TESTS/NPCtest.txt"));$*/


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

TEST_F(TestPrintSystem, SpeedIsNeg) {           //---------------------
    system->Readfile("xmlTests/SpeedIsNeg.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().empty() );

}



TEST_F(TestPrintSystem, NoEmission){
    system->Readfile("xmlTests/NoEmission.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().size() == 1);


}

TEST_F(TestPrintSystem, EmissionIsNeg){             //--------------------------
    system->Readfile("xmlTests/EmissionIsNeg.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().empty());
}

TEST_F(TestPrintSystem, NoName){                   //-----------------------------
    system->Readfile("xmlTests/NoName.xml");
    EXPECT_TRUE(system->getJobs().size() == 2);
    EXPECT_TRUE(system->getDevices().size() == 1);
}


//Reports:
TEST_F(TestPrintSystem, checkPrintReport){
    system->Readfile("xmlTests/NoPageCount.xml");


}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // to allow for threadsafe death tests
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}

