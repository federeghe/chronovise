#include "gtest/gtest.h"
#include "evt/pwcet.hpp"

#include <cmath>

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class pWCET_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    pWCET_Test()
    {
        // You can do set-up work for each test here.
    }

    virtual ~pWCET_Test() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
};

class CustomDistribution : public Distribution {
public:
    CustomDistribution(double factor=1.) : factor(factor){}

    virtual distribution_t get_type() const noexcept {
        return distribution_t::UNKNOWN;
    }

    virtual double cdf(double x) const noexcept override {
        return factor*(x/10);
    }
    
    virtual double pdf(double x) const noexcept override {
        return factor*(x/100);
    }

    virtual double quantile(double p) const override {
        return factor*p*10;
    }

private:
    double factor;

};

TEST_F(pWCET_Test, Constructor_and_getters) {
    std::shared_ptr<CustomDistribution> dist = std::make_shared<CustomDistribution>();
   
    EXPECT_THROW(pWCET<double> pwcet(nullptr), std::invalid_argument);

    pWCET<double> pwcet(dist);

    EXPECT_EQ(dist, pwcet.get_distribution());

}

TEST_F(pWCET_Test, Statistical_getters) {
    std::shared_ptr<CustomDistribution> dist = std::make_shared<CustomDistribution>();
   
    pWCET<double> pwcet(dist);

    EXPECT_EQ(0.95, pwcet.get_probability(0.5));
    EXPECT_EQ(5, pwcet.get_wcet(0.5));

}

TEST_F(pWCET_Test, Statistical_cumulative) {
    std::shared_ptr<CustomDistribution> dist = std::make_shared<CustomDistribution>();
    std::shared_ptr<CustomDistribution> dist2 = std::make_shared<CustomDistribution>(2);
    std::shared_ptr<CustomDistribution> dist3 = std::make_shared<CustomDistribution>(4);

    pWCET<double> pwcet(dist);
    pWCET<double> pwcet2(dist2);
    pWCET<double> pwcet3(dist3);

    std::list<pWCET<double>> pwcet_list;
    pwcet_list.push_back(pwcet);
    pwcet_list.push_back(pwcet2);
    pwcet_list.push_back(pwcet3);

    EXPECT_EQ(0.8, pWCET<double>::get_cumulative_probability(pwcet_list, 0.5));
    EXPECT_EQ(20, pWCET<double>::get_cumulative_wcet(pwcet_list, 0.5));

}

