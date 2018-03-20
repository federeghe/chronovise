#include "gtest/gtest.h"
#include "statistical/test_ad.hpp"
#include "statistical/distribution_uniform.hpp"
#include "global.hpp"

using namespace chronovise;

#include <cmath>

// The fixture for testing class Project1. From google test primer.
class AD_Test_Test : public ::testing::Test {
protected:


};

TEST_F(AD_Test_Test, GetterSetter) {
    TestAD<unsigned long, unsigned long> ad(0.05, distribution_t::EVT_GEV, false, 0);

    EXPECT_EQ(0.05, ad.get_significance_level());
    EXPECT_EQ(false, ad.is_reject());
    EXPECT_EQ(false, ad.has_power());

}

TEST_F(AD_Test_Test, DistributionACCEPT) {

    DistributionUniform du(1., 2.);
    auto du_ref_shared = std::shared_ptr<Distribution>(&du,[](auto* p){UNUSED(p);});

    TestAD<unsigned int, double> ad(0.05, distribution_t::EVT_GEV, false, 0);
    ad.set_ref_distribution(du_ref_shared);

    double uniform_ok_values[100] = {
1.3111, 1.9234, 1.4302, 1.1848, 1.9049, 1.9797, 1.4389, 1.1111, 1.2581, 1.4087, 1.5949, 1.2622
, 1.6028, 1.7112, 1.2217, 1.1174, 1.2967, 1.3188, 1.4242, 1.5079, 1.0855, 1.2625, 1.8010, 1.0292
, 1.9289, 1.7303, 1.4886, 1.5785, 1.2373, 1.4588, 1.9631, 1.5468, 1.5211, 1.2316, 1.4889, 1.6241
, 1.6791, 1.3955, 1.3674, 1.9880, 1.0377, 1.8852, 1.9133, 1.7962, 1.0987, 1.2619, 1.3354, 1.6797
, 1.1366, 1.7212, 1.1068, 1.6538, 1.4942, 1.7791, 1.7150, 1.9037, 1.8909, 1.3342, 1.6987, 1.1978
, 1.0305, 1.7441, 1.5000, 1.4799, 1.9047, 1.6099, 1.6177, 1.8594, 1.8055, 1.5767, 1.1829, 1.2399
, 1.8865, 1.0287, 1.4899, 1.1679, 1.9787, 1.7127, 1.5005, 1.4711, 1.0596, 1.6820, 1.0424, 1.0714
, 1.5216, 1.0967, 1.8181, 1.8175, 1.7224, 1.1499, 1.6596, 1.5186, 1.9730, 1.6490, 1.8003, 1.4538
, 1.4324, 1.8253, 1.0835, 1.1332
    };

    MeasuresPool<unsigned int, double> mp;
    for (int i=0; i<100; i++) {
        mp.push(i, uniform_ok_values[i]);
    }
    
    ad.run(mp);

    EXPECT_FALSE(ad.is_reject());

}

TEST_F(AD_Test_Test, DistributionREJECT) {

    DistributionUniform du(1., 2.);
    auto du_ref_shared = std::shared_ptr<Distribution>(&du,[](auto* p){UNUSED(p);});

    TestAD<unsigned int, double> ad(0.05, distribution_t::EVT_GEV, true, 0);
    ad.set_ref_distribution(du_ref_shared);

    double normal_values[100] = {
0.6099, 0.4776, 0.7553, 0.2815, 0.6037, 0.5871, 0.5873, 0.3177, 0.5817, 0.3713, 0.2759, 0.1992
,0.7595, 0.2885, 0.4568, 0.1978, 0.4257   -0.3080, 0.2283, 0.1434, 0.2464, 0.4467, 0.4187, 0.9861
, 0.3571, 0.4375, 0.1077, 0.3807, 0.1655, 0.5076, 0.7133, 0.6011, 0.3248, 0.0924, 0.8650, 1.0125
, 0.5301, 0.2525, 0.7994, 0.3518, 0.3825, 0.7216, 0.1537, 0.0108, 0.6052, 0.6002, 0.5238, 0.6242
, 0.7706, 0.7426, 0.3579, 0.7025, 0.5433, 0.3736, 0.2017, 0.6617, 0.4116, 0.5116, 0.3018, 0.1124
, 0.5429, 0.4845, 0.7998, 0.7004, 0.7633, 0.3128, 0.2659, 0.1827, 0.6245, 1.1973, 0.6819, 0.3067
, 0.7092, 0.2179, 0.1439, 0.6794, 0.3055, 0.5790, 0.8516, 0.6003, 0.7324, 0.0985, 0.6654, 1.0346
, 0.6353, 0.1148, 0.4492, 0.3750, 0.5958, 0.6030, 0.6014, 0.4091, 0.3502, 0.3526, 0.7134, 0.0367
, 0.4482, 0.5676, 0.3368, 0.6193
    };

    MeasuresPool<unsigned int, double> mp;
    for (int i=0; i<100; i++) {
        mp.push(i, normal_values[i]);
    }
    
    ad.run(mp);

    EXPECT_TRUE(ad.is_reject());

}

TEST_F(AD_Test_Test, Exceptions) {
     EXPECT_THROW((new TestAD<unsigned int, double>(0.5, distribution_t::EVT_GEV, true, -0.1)),
                 std::invalid_argument);

     DistributionUniform du(1., 2.);
     auto du_ref_shared = std::shared_ptr<Distribution>(&du,[](auto* p){UNUSED(p);});

     TestAD<unsigned int, double> ad(0.05, distribution_t::EVT_GEV, false, 0);

     MeasuresPool<unsigned int, double> mp;
     mp.push(1,1);

     EXPECT_THROW(ad.run(mp), std::invalid_argument);

     for (int i=0; i<100; i++) {
         mp.push(i, i);
     }

     // Missing distribution
     EXPECT_THROW(ad.run(mp), std::invalid_argument);

}
