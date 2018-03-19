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

    UniformGenerator_Test() : a(0,MAX_VALUE), b(0,MAX_VALUE), u_a(0, MAX_VALUE), u_b(0, MAX_VALUE), 
                              c(0,MAX_VALUE), d(0,MAX_VALUE), u_c(0, MAX_VALUE),u_d(0, MAX_VALUE),
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

    UniformInputGenerator<unsigned int> u_a;
    UniformInputGenerator<unsigned int> u_b;

    UniformInputGenerator<long> c;
    UniformInputGenerator<long> d;

    UniformInputGenerator<unsigned long> u_c;
    UniformInputGenerator<unsigned long> u_d;

    UniformInputGenerator<float> e;
    UniformInputGenerator<float> f;

    UniformInputGenerator<double> g;
    UniformInputGenerator<double> h;


};

TEST_F(UniformGenerator_Test, IntTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(a.get(), b.get());
}

TEST_F(UniformGenerator_Test, IntegersLimits) {

    EXPECT_LE(a.get(), MAX_VALUE);
    EXPECT_LE(b.get(), MAX_VALUE);
    EXPECT_LE(c.get(), MAX_VALUE);
    EXPECT_LE(d.get(), MAX_VALUE);
    EXPECT_LE(u_a.get(), MAX_VALUE);
    EXPECT_LE(u_b.get(), MAX_VALUE);
    EXPECT_LE(u_c.get(), MAX_VALUE);
    EXPECT_LE(u_d.get(), MAX_VALUE);

    EXPECT_GE(a.get(), 0);
    EXPECT_GE(b.get(), 0);
    EXPECT_GE(c.get(), 0);
    EXPECT_GE(d.get(), 0);
    EXPECT_GE(u_a.get(), 0);
    EXPECT_GE(u_b.get(), 0);
    EXPECT_GE(u_c.get(), 0);
    EXPECT_GE(u_d.get(), 0);

}

TEST_F(UniformGenerator_Test, FloatingLimits) {

    EXPECT_LE(e.get(), MAX_VALUE_F);
    EXPECT_LE(f.get(), MAX_VALUE_F);
    EXPECT_LE(g.get(), MAX_VALUE);
    EXPECT_LE(h.get(), MAX_VALUE);

    EXPECT_GE(e.get(), 0);
    EXPECT_GE(f.get(), 0);
    EXPECT_GE(g.get(), 0);
    EXPECT_GE(h.get(), 0);

}


TEST_F(UniformGenerator_Test, UIntTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(u_a.get(), u_b.get());
}

TEST_F(UniformGenerator_Test, LongTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(c.get(), d.get());
}

TEST_F(UniformGenerator_Test, ULongTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(u_c.get(), u_d.get());
}

TEST_F(UniformGenerator_Test, FloatTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(e.get(), f.get());
}

TEST_F(UniformGenerator_Test, DoubleTwoInstance) {

    // This may fail, but it's really improbable
    EXPECT_NE(g.get(), h.get());
}


