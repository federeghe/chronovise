#include "gtest/gtest.h"
#include "utility/optional.hpp"

#include <cmath>

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class Optional_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    Optional_Test()
    {
        // You can do set-up work for each test here.
    }

    virtual ~Optional_Test() {
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

};

TEST_F(Optional_Test, TestConstructor1) {
    utility::optional<int> test;
    EXPECT_FALSE((bool)test);
}

TEST_F(Optional_Test, TestConstructor2) {
    utility::optional<int> test(5);
  
    ASSERT_TRUE((bool)test);
    EXPECT_EQ(*test, 5);
}

TEST_F(Optional_Test, TestConstructor3) {
    utility::optional<int> test(nullptr);
    EXPECT_FALSE((bool)test);
}


TEST_F(Optional_Test, Test_operator_deref) {

    struct test {
        int ciao;
    } abc;

    abc.ciao = 23;

    utility::optional<struct test*> test(&abc);

    ASSERT_TRUE((bool)test);  
    EXPECT_EQ(23, test->ciao);

}

TEST_F(Optional_Test, Test_set_reset) {
    utility::optional<double> test;

    EXPECT_FALSE((bool)test);

    test.set(3.14);

    ASSERT_TRUE((bool)test);
    EXPECT_EQ(3.14, *test);

    test.reset();

    EXPECT_FALSE((bool)test);
}


