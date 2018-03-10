#include "gtest/gtest.h"
#include "evt/gpd_distribution.hpp"

#include <cmath>

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class GPD_Distribution_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    GPD_Distribution_Test() : standard(0, 1, 0.5), pareto(1, 1, 1), exponential(0, 1, 0),
                 standard_noncenter(10, 1, -0.1), pareto_noncenter(50, 25, 0.5),
                 exponential_noncenter(0, 100, 0)
      {
        // You can do set-up work for each test here.
    }

    virtual ~GPD_Distribution_Test() {
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

    GPD_Distribution standard;
    GPD_Distribution pareto;
    GPD_Distribution exponential;
    
    GPD_Distribution standard_noncenter;
    GPD_Distribution pareto_noncenter;
    GPD_Distribution exponential_noncenter;


};

TEST_F(GPD_Distribution_Test, TestIsMethods_Standard) {
    EXPECT_FALSE(standard.is_exponential());
    EXPECT_FALSE(standard.is_pareto());

    EXPECT_FALSE(standard_noncenter.is_exponential());
    EXPECT_FALSE(standard_noncenter.is_pareto());
}

TEST_F(GPD_Distribution_Test, TestIsMethods_Exponential) {
    EXPECT_TRUE(exponential.is_exponential());
    EXPECT_FALSE(exponential.is_pareto());

    EXPECT_TRUE(exponential_noncenter.is_exponential());
    EXPECT_FALSE(exponential_noncenter.is_pareto());
}
TEST_F(GPD_Distribution_Test, TestIsMethods_Pareto) {
    EXPECT_FALSE(pareto.is_exponential());
    EXPECT_TRUE(pareto.is_pareto());

    EXPECT_FALSE(pareto_noncenter.is_exponential());
    EXPECT_TRUE(pareto_noncenter.is_pareto());
}

TEST_F(GPD_Distribution_Test, TestGetMethods_Centered) {

    EXPECT_EQ(0, standard.get_location());
    EXPECT_EQ(1, pareto.get_location());
    EXPECT_EQ(0, exponential.get_location());

    EXPECT_EQ(1, standard.get_scale());
    EXPECT_EQ(1, pareto.get_scale());
    EXPECT_EQ(1, exponential.get_scale());

    EXPECT_EQ(0.5, standard.get_shape());
    EXPECT_EQ(1, pareto.get_shape());
    EXPECT_EQ(0, exponential.get_shape());
}

TEST_F(GPD_Distribution_Test, TestGetMethods_NonCentered) {

    EXPECT_EQ(10, standard_noncenter.get_location());
    EXPECT_EQ(50, pareto_noncenter.get_location());
    EXPECT_EQ(0, exponential_noncenter.get_location());

    EXPECT_EQ(1, standard_noncenter.get_scale());
    EXPECT_EQ(25, pareto_noncenter.get_scale());
    EXPECT_EQ(100, exponential_noncenter.get_scale());

    EXPECT_EQ(-0.1, standard_noncenter.get_shape());
    EXPECT_EQ(0.5, pareto_noncenter.get_shape());
    EXPECT_EQ(0, exponential_noncenter.get_shape());
}

// Data taken from MATLAB (r) 2017b

TEST_F(GPD_Distribution_Test, TestStandard) {

    EXPECT_NEAR(0, standard.pdf(1000000), 1e-15);
    EXPECT_NEAR(5.689576695493851e-05, standard.pdf(50), 1e-15);
    EXPECT_NEAR(0.004629629629630, standard.pdf(10), 1e-15);
    EXPECT_NEAR(0.023323615160350, standard.pdf(5), 1e-15);
    EXPECT_NEAR(1.000000000000000, standard.pdf(0), 1e-15);
    EXPECT_DOUBLE_EQ(0, standard.pdf(-1));


    EXPECT_NEAR(0.999996015952128, standard.cdf(1000), 1e-15);
    EXPECT_NEAR(0.998520710059172, standard.cdf(50), 1e-15);
    EXPECT_NEAR(0.918367346938776, standard.cdf(5), 1e-15);
    EXPECT_NEAR(0.555555555555556, standard.cdf(1), 1e-15);
    EXPECT_DOUBLE_EQ(0, standard.cdf(0));
    EXPECT_DOUBLE_EQ(0, standard.cdf(-1));

}


TEST_F(GPD_Distribution_Test, TestPareto) {

    EXPECT_NEAR(0, pareto.pdf(1e9), 1e-15);
    EXPECT_NEAR(0.0001, pareto.pdf(100), 1e-15);
    EXPECT_NEAR(0.01, pareto.pdf(10), 1e-15);
    EXPECT_NEAR(0.04, pareto.pdf(5), 1e-15);
    EXPECT_NEAR(0.444444444444444, pareto.pdf(1.5), 1e-15);
    EXPECT_NEAR(1., pareto.pdf(1), 1e-15);
    EXPECT_DOUBLE_EQ(0, pareto.pdf(-1));

    EXPECT_NEAR(0.99, pareto.cdf(100), 1e-15);
    EXPECT_NEAR(0.9, pareto.cdf(10), 1e-15);
    EXPECT_NEAR(0.8, pareto.cdf(5), 1e-15);
    EXPECT_NEAR(0.333333333333333, pareto.cdf(1.5), 1e-15);
    EXPECT_DOUBLE_EQ(0, pareto.cdf(1));
    EXPECT_DOUBLE_EQ(0, pareto.cdf(-1));

}

TEST_F(GPD_Distribution_Test, TestExponential) {

    EXPECT_NEAR(0, exponential.pdf(1e9), 1e-15);
    EXPECT_NEAR(0, exponential.pdf(100), 1e-15);
    EXPECT_NEAR(0.000045399929762, exponential.pdf(10), 1e-15);
    EXPECT_NEAR(0.006737946999085, exponential.pdf(5), 1e-15);
    EXPECT_NEAR(0.223130160148430, exponential.pdf(1.5), 1e-15);
    EXPECT_NEAR(0.367879441171442, exponential.pdf(1), 1e-15);
    EXPECT_DOUBLE_EQ(1, exponential.pdf(0));
    EXPECT_DOUBLE_EQ(0, exponential.pdf(-1));

    EXPECT_NEAR(1, exponential.cdf(1e9), 1e-15);
    EXPECT_NEAR(1, exponential.cdf(100), 1e-15);
    EXPECT_NEAR(0.999954600070238, exponential.cdf(10), 1e-15);
    EXPECT_NEAR(0.993262053000915, exponential.cdf(5), 1e-15);
    EXPECT_NEAR(0.776869839851570, exponential.cdf(1.5), 1e-15);
    EXPECT_NEAR(0.632120558828558, exponential.cdf(1), 1e-15);
    EXPECT_DOUBLE_EQ(0, exponential.cdf(-1));
}

TEST_F(GPD_Distribution_Test, TestPareto_noncenter) {

    EXPECT_NEAR(0.000000000000000, pareto_noncenter.pdf(1e9), 1e-15);
    EXPECT_NEAR(0.000625000000000, pareto_noncenter.pdf(200), 1e-15);
    EXPECT_NEAR(0.005000000000000, pareto_noncenter.pdf(100), 1e-15);
    EXPECT_NEAR(0.011851851851852, pareto_noncenter.pdf(75), 1e-15);
    EXPECT_NEAR(0.040000000000000, pareto_noncenter.pdf(50), 1e-15);
    EXPECT_NEAR(0., pareto_noncenter.pdf(10), 1e-15);

    EXPECT_NEAR(0.999999999999997, pareto_noncenter.cdf(1e9), 1e-15);
    EXPECT_NEAR(0.937500000000000, pareto_noncenter.cdf(200), 1e-15);
    EXPECT_NEAR(0.750000000000000, pareto_noncenter.cdf(100), 1e-15);
    EXPECT_NEAR(0.555555555555556, pareto_noncenter.cdf(75), 1e-15);
    EXPECT_NEAR(0.305555555555556, pareto_noncenter.cdf(60), 1e-15);
    EXPECT_NEAR(0., pareto_noncenter.cdf(10), 1e-15);

}

TEST_F(GPD_Distribution_Test, TestQuantileStandard) {

    EXPECT_THROW(standard.quantile(0), std::invalid_argument);
    EXPECT_NEAR(0.309401076758503, standard.quantile(0.25), 1e-15);
    EXPECT_NEAR(0.828427124746190, standard.quantile(0.5), 1e-15);
    EXPECT_NEAR(2.000000000000000, standard.quantile(0.75), 1e-15);
    EXPECT_THROW(standard.quantile(1), std::invalid_argument);

}

TEST_F(GPD_Distribution_Test, TestQuantilePareto) {

    EXPECT_THROW(pareto.quantile(0), std::invalid_argument);
    EXPECT_NEAR(1.333333333333333, pareto.quantile(0.25), 1e-15);
    EXPECT_NEAR(2.000000000000000, pareto.quantile(0.5), 1e-15);
    EXPECT_NEAR(4.000000000000000, pareto.quantile(0.75), 1e-15);
    EXPECT_THROW(pareto.quantile(1), std::invalid_argument);
}

TEST_F(GPD_Distribution_Test, TestQuantileExponential) {
    EXPECT_THROW(exponential.quantile(0), std::invalid_argument);
    EXPECT_NEAR(0.287682072451781, exponential.quantile(0.25), 1e-15);
    EXPECT_NEAR(0.693147180559945, exponential.quantile(0.5), 1e-15);
    EXPECT_NEAR(1.386294361119891, exponential.quantile(0.75), 1e-15);
    EXPECT_THROW(exponential.quantile(1), std::invalid_argument);

}

