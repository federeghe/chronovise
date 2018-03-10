#include "gtest/gtest.h"
#include "input/generator_uniform.hpp"

#include <cmath>

#define MAX_VALUE 100000
#define MAX_VALUE_F 2.0

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class UniformGenerator_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    UniformGenerator_Test() : a(0,MAX_VALUE), b(0,MAX_VALUE), c(0,MAX_VALUE), d(0,MAX_VALUE),
                e(0, MAX_VALUE_F), f(0, MAX_VALUE_F),  g(0, MAX_VALUE_F),  h(0, MAX_VALUE_F) 
{
        // You can do set-up work for each test here.
    }

    virtual ~UniformGenerator_Test() {
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
    UniformInputGenerator<int> a;
    UniformInputGenerator<int> b;

    UniformInputGenerator<long> c;
    UniformInputGenerator<long> d;

    UniformInputGenerator<float> e;
    UniformInputGenerator<float> f;

    UniformInputGenerator<double> g;
    UniformInputGenerator<double> h;


};

TEST_F(UniformGenerator_Test, IntTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(a.get(), b.get());
}

TEST_F(UniformGenerator_Test, LongTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(c.get(), d.get());
}

TEST_F(UniformGenerator_Test, FloatTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(e.get(), f.get());
}

TEST_F(UniformGenerator_Test, DoubleTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(g.get(), h.get());
}


