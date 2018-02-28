#include "gtest/gtest.h"
#include "evt/ev_distribution.hpp"

#include <cmath>

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class EV_Distribution_Test : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	EV_Distribution_Test() : gumbell(0, 1, 0), weibull(0, 1, -0.5), frechet(0, 1, 0.5),
				 gumbell_noncenter(1000, 20, 0), weibull_noncenter(50, 0.4, -0.25),
				 frechet_noncenter(1e7, 1e6, 0.25)
  	{
		// You can do set-up work for each test here.
	}

	virtual ~EV_Distribution_Test() {
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

	EV_Distribution gumbell;
	EV_Distribution weibull;
	EV_Distribution frechet;
	
	EV_Distribution gumbell_noncenter;
	EV_Distribution weibull_noncenter;
	EV_Distribution frechet_noncenter;


};

TEST_F(EV_Distribution_Test, TestIsMethods_Gumbell) {
	EXPECT_TRUE(gumbell.is_gumbell());
	EXPECT_FALSE(gumbell.is_weibull());
	EXPECT_FALSE(gumbell.is_frechet());

	EXPECT_TRUE(gumbell_noncenter.is_gumbell());
	EXPECT_FALSE(gumbell_noncenter.is_weibull());
	EXPECT_FALSE(gumbell_noncenter.is_frechet());
}

TEST_F(EV_Distribution_Test, TestIsMethods_Weibull) {
	EXPECT_FALSE(weibull.is_gumbell());
	EXPECT_TRUE(weibull.is_weibull());
	EXPECT_FALSE(weibull.is_frechet());

	EXPECT_FALSE(weibull_noncenter.is_gumbell());
	EXPECT_TRUE(weibull_noncenter.is_weibull());
	EXPECT_FALSE(weibull_noncenter.is_frechet());
}
TEST_F(EV_Distribution_Test, TestIsMethods_Frechet) {
	EXPECT_FALSE(frechet.is_gumbell());
	EXPECT_FALSE(frechet.is_weibull());
	EXPECT_TRUE(frechet.is_frechet());

	EXPECT_FALSE(frechet_noncenter.is_gumbell());
	EXPECT_FALSE(frechet_noncenter.is_weibull());
	EXPECT_TRUE(frechet_noncenter.is_frechet());
}

TEST_F(EV_Distribution_Test, TestGetMethods_Centered) {

	EXPECT_EQ(0, gumbell.get_location());
	EXPECT_EQ(0, weibull.get_location());
	EXPECT_EQ(0, frechet.get_location());

	EXPECT_EQ(1, gumbell.get_scale());
	EXPECT_EQ(1, weibull.get_scale());
	EXPECT_EQ(1, frechet.get_scale());

	EXPECT_EQ(0, gumbell.get_shape());
	EXPECT_EQ(-0.5, weibull.get_shape());
	EXPECT_EQ(0.5, frechet.get_shape());
}

TEST_F(EV_Distribution_Test, TestGetMethods_NonCentered) {

	EXPECT_EQ(1000, gumbell_noncenter.get_location());
	EXPECT_EQ(50, weibull_noncenter.get_location());
	EXPECT_EQ(1e7, frechet_noncenter.get_location());

	EXPECT_EQ(20, gumbell_noncenter.get_scale());
	EXPECT_EQ(0.4, weibull_noncenter.get_scale());
	EXPECT_EQ(1e6, frechet_noncenter.get_scale());

	EXPECT_EQ(0, gumbell_noncenter.get_shape());
	EXPECT_EQ(-0.25, weibull_noncenter.get_shape());
	EXPECT_EQ(0.25, frechet_noncenter.get_shape());
}

// Data taken from MATLAB (r) 2017b

TEST_F(EV_Distribution_Test, TestGumbell) {

	EXPECT_DOUBLE_EQ(0, gumbell.pdf(1000));
	EXPECT_NEAR(1.928749847963918e-22, gumbell.pdf(50), 1e-15);
	EXPECT_NEAR(4.539786865564983e-05, gumbell.pdf(10), 1e-15);
	EXPECT_NEAR(0.006692699677536, gumbell.pdf(5), 1e-15);
	EXPECT_NEAR(0.367879441171442, gumbell.pdf(0), 1e-15);
	EXPECT_NEAR(0.179374078734017, gumbell.pdf(-1), 1e-15);
	EXPECT_DOUBLE_EQ(0, gumbell.pdf(-20));

	EXPECT_DOUBLE_EQ(1, gumbell.cdf(50));
	EXPECT_NEAR(0.999954601100799, gumbell.cdf(10), 1e-15);
	EXPECT_NEAR(0.993284702067841, gumbell.cdf(5), 1e-15);
	EXPECT_NEAR(0.367879441171442, gumbell.cdf(0), 1e-15);
	EXPECT_NEAR(0.065988035845313, gumbell.cdf(-1), 1e-15);
	EXPECT_DOUBLE_EQ(0, gumbell.cdf(-20));

}


TEST_F(EV_Distribution_Test, TestFrechet) {

	EXPECT_DOUBLE_EQ(0, weibull.pdf(10));
	EXPECT_NEAR(0.234853265703369, weibull.pdf(1.5), 1e-15);
	EXPECT_NEAR(0.389400391535702, weibull.pdf(1), 1e-15);
	EXPECT_NEAR(0.367879441171442, weibull.pdf(0), 1e-15);
	EXPECT_NEAR(0.158098836842797, weibull.pdf(-1), 1e-15);
	EXPECT_NEAR(0.000016747910872, weibull.pdf(-5), 1e-15);
	EXPECT_DOUBLE_EQ(0, weibull.pdf(-100));

	EXPECT_DOUBLE_EQ(1, weibull.cdf(1000));
	EXPECT_NEAR(0.939413062813476, weibull.cdf(1.5), 1e-15);
	EXPECT_NEAR(0.778800783071405, weibull.cdf(1), 1e-15);
	EXPECT_NEAR(0.367879441171442, weibull.cdf(0), 1e-15);
	EXPECT_NEAR(0.105399224561864, weibull.cdf(-1), 1e-15);
	EXPECT_NEAR(0.001930454136228, weibull.cdf(-3), 1e-15);
	EXPECT_NEAR(0.000004785117392, weibull.cdf(-5), 1e-15);
	EXPECT_DOUBLE_EQ(0, weibull.cdf(-100));

}

TEST_F(EV_Distribution_Test, TestWeibull) {

	EXPECT_NEAR(0, frechet.pdf(100000000), 1e-15);
	EXPECT_NEAR(0.004502798505168, frechet.pdf(10), 1e-15);
	EXPECT_NEAR(0.021495287400530, frechet.pdf(5), 1e-15);
	EXPECT_NEAR(0.134609406946660, frechet.pdf(1.5), 1e-15);
	EXPECT_NEAR(0.189979374349616, frechet.pdf(1), 1e-15);
	EXPECT_NEAR(0.367879441171442, frechet.pdf(0), 1e-15);
	EXPECT_DOUBLE_EQ(0, frechet.pdf(-3));

	EXPECT_DOUBLE_EQ(1, frechet.cdf(100000000));
	EXPECT_NEAR(0.972604477116348, frechet.cdf(10), 1e-15);
	EXPECT_NEAR(0.921610447297725, frechet.cdf(5), 1e-15);
	EXPECT_NEAR(0.721422290354756, frechet.cdf(1.5), 1e-15);
	EXPECT_NEAR(0.641180388429955, frechet.cdf(1), 1e-15);
	EXPECT_NEAR(0.367879441171442, frechet.cdf(0), 1e-15);
	EXPECT_NEAR(0.018315638888734, frechet.cdf(-1), 1e-15);
	EXPECT_DOUBLE_EQ(0, frechet.cdf(-3));

}

TEST_F(EV_Distribution_Test, TestGumbell_noncenter) {

	EXPECT_NEAR(0, gumbell_noncenter.pdf(2000), 1e-15);
	EXPECT_NEAR(0.000000186331964, gumbell_noncenter.pdf(1250), 1e-15);
	EXPECT_NEAR(0.003780808995871, gumbell_noncenter.pdf(1050), 1e-15);
	EXPECT_NEAR(0.010756585897012, gumbell_noncenter.pdf(1025), 1e-15);
	EXPECT_NEAR(0.018393972058572, gumbell_noncenter.pdf(1000), 1e-15);
	EXPECT_NEAR(0.015852096053897, gumbell_noncenter.pdf(990), 1e-15);
	EXPECT_DOUBLE_EQ(0, gumbell_noncenter.pdf(800));

	EXPECT_DOUBLE_EQ(1, gumbell_noncenter.cdf(2000));
	EXPECT_NEAR(0.999996273353772, gumbell_noncenter.cdf(1250), 1e-15);
	EXPECT_NEAR(0.921193655175516, gumbell_noncenter.cdf(1050), 1e-15);
	EXPECT_NEAR(0.750883476639395, gumbell_noncenter.cdf(1025), 1e-15);
	EXPECT_NEAR(0.367879441171442, gumbell_noncenter.cdf(1000), 1e-15);
	EXPECT_NEAR(0.192295645547965, gumbell_noncenter.cdf(990), 1e-15);
	EXPECT_DOUBLE_EQ(0, gumbell_noncenter.cdf(800));

}


TEST_F(EV_Distribution_Test, TestWeibull_noncenter) {

	EXPECT_NEAR(0, weibull_noncenter.pdf(100000000), 1e-15);
	EXPECT_NEAR(0, weibull_noncenter.pdf(90), 1e-15);
	EXPECT_NEAR(0, weibull_noncenter.pdf(55), 1e-15);
	EXPECT_NEAR(0.129254439530373, weibull_noncenter.pdf(51), 1e-15);
	EXPECT_NEAR(0.649733144629201, weibull_noncenter.pdf(50.5), 1e-15);
	EXPECT_NEAR(0.919698602928606, weibull_noncenter.pdf(50), 1e-15);
	EXPECT_DOUBLE_EQ(0, weibull_noncenter.pdf(40));

	EXPECT_DOUBLE_EQ(1, weibull_noncenter.cdf(100000000));
	EXPECT_NEAR(1, weibull_noncenter.cdf(90), 1e-15);
	EXPECT_NEAR(1, weibull_noncenter.cdf(55), 1e-15);
	EXPECT_NEAR(0.980418859845197, weibull_noncenter.cdf(51), 1e-15);
	EXPECT_NEAR(0.799791723636727, weibull_noncenter.cdf(50.5), 1e-15);
	EXPECT_NEAR(0.367879441171442, weibull_noncenter.cdf(50), 1e-15);
	EXPECT_DOUBLE_EQ(0, weibull_noncenter.cdf(40));

}

TEST_F(EV_Distribution_Test, TestFrechet_noncenterPDF) {

	EXPECT_NEAR(0.001891322928647e-6, frechet_noncenter.pdf(2e7), 1e-15);
	EXPECT_NEAR(0.054765153057232e-6, frechet_noncenter.pdf(1.3e7), 1e-15);
	EXPECT_NEAR(0.108082937718290e-6, frechet_noncenter.pdf(1.2e7), 1e-15);
	EXPECT_NEAR(0.217551917329768e-6, frechet_noncenter.pdf(1.1e7), 1e-15);
	EXPECT_NEAR(0.367879441171442e-6, frechet_noncenter.pdf(1e7), 1e-15);
	EXPECT_NEAR(0.178693458254981e-6, frechet_noncenter.pdf(0.9e7), 1e-15);
	EXPECT_NEAR(0, frechet_noncenter.pdf(1e5), 1e-15);

}

TEST_F(EV_Distribution_Test, TestFrechet_noncenterCDF) {
	EXPECT_NEAR(0.993358264430476, frechet_noncenter.cdf(2e7), 1e-15);
	EXPECT_NEAR(0.898865163508697, frechet_noncenter.cdf(1.3e7), 1e-15);
	EXPECT_NEAR(0.820754808298268, frechet_noncenter.cdf(1.2e7), 1e-15);
	EXPECT_NEAR(0.663915763335474, frechet_noncenter.cdf(1.1e7), 1e-15);
	EXPECT_NEAR(0.367879441171442, frechet_noncenter.cdf(1e7), 1e-15);
	EXPECT_NEAR(0.042404795269493, frechet_noncenter.cdf(0.9e7), 1e-15);
	EXPECT_NEAR(0, frechet_noncenter.cdf(1e5), 1e-15);

}

TEST_F(EV_Distribution_Test, TestQuantile) {

	EXPECT_THROW(gumbell.quantile(0), std::invalid_argument);
	EXPECT_NEAR(-0.326634259978281, gumbell.quantile(0.25), 1e-15);
	EXPECT_NEAR(0.366512920581664, gumbell.quantile(0.5), 1e-15);
	EXPECT_NEAR(1.245899323707238, gumbell.quantile(0.75), 1e-15);
	EXPECT_THROW(gumbell.quantile(1), std::invalid_argument);

	EXPECT_THROW(weibull.quantile(0), std::invalid_argument);
	EXPECT_NEAR(-0.354820045030949, weibull.quantile(0.25), 1e-15);
	EXPECT_NEAR(0.334890777684605, weibull.quantile(0.5), 1e-15);
	EXPECT_NEAR(0.927279957394697, weibull.quantile(0.75), 1e-15);
	EXPECT_THROW(weibull.quantile(1), std::invalid_argument);

	EXPECT_THROW(frechet.quantile(0), std::invalid_argument);
	EXPECT_NEAR(-0.301356399423962, frechet.quantile(0.25), 1e-15);
	EXPECT_NEAR(0.402244817572900, frechet.quantile(0.5), 1e-15);
	EXPECT_NEAR(1.728838691486778, frechet.quantile(0.75), 1e-15);
	EXPECT_THROW(frechet.quantile(1), std::invalid_argument);
}

TEST_F(EV_Distribution_Test, TestQuantileGumbell_noncenter) {

	EXPECT_THROW(gumbell_noncenter.quantile(0), std::invalid_argument);
	EXPECT_NEAR(0.993467314800434e3, gumbell_noncenter.quantile(0.25), 1e-12);
	EXPECT_NEAR(1.007330258411633e3, gumbell_noncenter.quantile(0.5), 1e-12);
	EXPECT_NEAR(1.024917986474145e3, gumbell_noncenter.quantile(0.75), 1e-12);
	EXPECT_THROW(gumbell_noncenter.quantile(1), std::invalid_argument);
}

TEST_F(EV_Distribution_Test, TestQuantileFrechet_noncenter) {

	EXPECT_THROW(frechet_noncenter.quantile(0), std::invalid_argument);
	EXPECT_NEAR(0.968634626759456e7, frechet_noncenter.quantile(0.25), 1e-8);
	EXPECT_NEAR(1.038382920978717e7, frechet_noncenter.quantile(0.5), 1e-8);
	EXPECT_NEAR(1.146174967678804e7, frechet_noncenter.quantile(0.75), 1e-8);
	EXPECT_THROW(frechet_noncenter.quantile(1), std::invalid_argument);
}

TEST_F(EV_Distribution_Test, TestQuantileWeibull_noncenter) {

	EXPECT_THROW(weibull_noncenter.quantile(0), std::invalid_argument);
	EXPECT_NEAR(49.863863583228664, weibull_noncenter.quantile(0.25), 1e-8);
	EXPECT_NEAR(50.140089110745556, weibull_noncenter.quantile(0.5), 1e-8);
	EXPECT_NEAR(50.428214330803286, weibull_noncenter.quantile(0.75), 1e-8);
	EXPECT_THROW(weibull_noncenter.quantile(1), std::invalid_argument);
}

TEST_F(EV_Distribution_Test, TestExtraQuantile) {

	EV_Distribution weibull_test(14.063, 0.410583, -0.189839);

	EXPECT_NEAR(15.642968703665069, weibull_test.quantile(0.999), 1e-8);

}

