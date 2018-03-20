#include "gtest/gtest.h"
#include "statistical/distribution_uniform.hpp"

#include <cmath>

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class Uniform_Distribution_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    Uniform_Distribution_Test() : u1(-1,1), u2(0,5)
    {
       // You can do set-up work for each test here.
    }

    virtual ~Uniform_Distribution_Test() {
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


    DistributionUniform u1, u2;

};

TEST_F(Uniform_Distribution_Test, TypeConforming) {

    EXPECT_EQ(distribution_t::UNIFORM, u1.get_type());
    EXPECT_EQ(distribution_t::UNIFORM, u2.get_type());

}


TEST_F(Uniform_Distribution_Test, CDF) {
    EXPECT_DOUBLE_EQ(0, u1.cdf(-2));
    EXPECT_DOUBLE_EQ(1, u1.cdf(2));
    EXPECT_DOUBLE_EQ(0, u2.cdf(-1));
    EXPECT_DOUBLE_EQ(1, u2.cdf(10));

    EXPECT_DOUBLE_EQ(0.75, u1.cdf(0.5));
    EXPECT_DOUBLE_EQ(0.1, u2.cdf(0.5));
    EXPECT_DOUBLE_EQ(0.55, u1.cdf(0.1));
    EXPECT_DOUBLE_EQ(0.02, u2.cdf(0.1));
}

TEST_F(Uniform_Distribution_Test, PDF) {
    EXPECT_DOUBLE_EQ(0, u1.pdf(-2));
    EXPECT_DOUBLE_EQ(0, u1.pdf(2));
    EXPECT_DOUBLE_EQ(0, u2.pdf(-1));
    EXPECT_DOUBLE_EQ(0, u2.pdf(10));

    EXPECT_DOUBLE_EQ(0.5, u1.pdf(0.5));
    EXPECT_DOUBLE_EQ(0.2, u2.pdf(0.5));
    EXPECT_DOUBLE_EQ(0.5, u1.pdf(0.1));
    EXPECT_DOUBLE_EQ(0.2, u2.pdf(0.1));
}

TEST_F(Uniform_Distribution_Test, Quantile) {
    EXPECT_THROW(u1.quantile(-0.1), std::invalid_argument);
    EXPECT_THROW(u2.quantile(1.5), std::invalid_argument);

    EXPECT_DOUBLE_EQ(0, u1.quantile(0.5));
    EXPECT_DOUBLE_EQ(2.5, u2.quantile(0.5));
    EXPECT_DOUBLE_EQ(-0.8, u1.quantile(0.1));
    EXPECT_DOUBLE_EQ(0.5, u2.quantile(0.1));
}

TEST_F(Uniform_Distribution_Test, ParameterCheck) {

    EXPECT_EQ(-1, u1.get_parameters().first);
    EXPECT_EQ(1, u1.get_parameters().second);
    EXPECT_EQ(0, u2.get_parameters().first);
    EXPECT_EQ(5, u2.get_parameters().second);

}
