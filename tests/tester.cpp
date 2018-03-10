#include "gtest/gtest.h"


// The fixture for testing class Project1. From google test primer.
class TestSuiteTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    TestSuiteTest() {
        // You can do set-up work for each test here.
    }

    virtual ~TestSuiteTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Project1.
    //Project1 p;
};

TEST_F(TestSuiteTest, FirstTest) {
    int i = 0;
    EXPECT_EQ(0, i);
}

