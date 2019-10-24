#include "gtest/gtest.h"
#include "statistical/test_kpss.hpp"
#include "statistical/distribution_uniform.hpp"
#include "global.hpp"

using namespace chronovise;

#include <cmath>

// The fixture for testing class Project1. From google test primer.
class Test_KPSS_Test : public ::testing::Test {
protected:


};

TEST_F(Test_KPSS_Test, GetterSetter) {
    TestKPSS<unsigned long, unsigned long> jb(0.01, 10);

    EXPECT_EQ(0.01, jb.get_significance_level());
    EXPECT_EQ(false, jb.is_reject());
    EXPECT_EQ(false, jb.has_power());

}

TEST_F(Test_KPSS_Test, DistributionACCEPT) {

    TestKPSS<unsigned int, double> jb(0.05, 0);

    double norm_ind_values[100] = {
1.8339,-2.2588,0.8622,0.3188,-1.3077,-0.4336,0.3426,3.5784,2.7694,-1.3499,3.0349,0.7254
,-0.0631,0.7147,-0.2050,-0.1241,1.4897,1.4090,1.4172,0.6715,-1.2075,0.7172,1.6302,0.4889
,1.0347,0.7269,-0.3034,0.2939,-0.7873,0.8884,-1.1471,-1.0689,-0.8095,-2.9443,1.4384,0.3252
,-0.7549,1.3703,-1.7115,-0.1022,-0.2414,0.3192,0.3129,-0.8649,-0.0301,-0.1649,0.6277,1.0933
,1.1093,-0.8637,0.0774,-1.2141,-1.1135,-0.0068,1.5326,-0.7697,0.3714,-0.2256,1.1174,-1.0891
,0.0326,0.5525,1.1006,1.5442,0.0859,-1.4916,-0.7423,-1.0616,2.3505,-0.6156,0.7481,-0.1924
,0.8886,-0.7648,-1.4023,-1.4224,0.4882,-0.1774,-0.1961,1.4193,0.2916,0.1978,1.5877,-0.8045
,0.6966,0.8351,-0.2437,0.2157,-1.1658,-1.1480,0.1049,0.7223,2.5855,-0.6669,0.1873,-0.0825
,-1.9330,-0.4390,-1.7947,0.8404
    };

    MeasuresPool<unsigned int, double> mp;
    for (int i=0; i<100; i++) {
        mp.push(i, norm_ind_values[i]);
    }
    
    jb.run(mp);

    EXPECT_FALSE(jb.is_reject());

}

TEST_F(Test_KPSS_Test, DistributionREJECT_1) {

    TestKPSS<unsigned int, double> jb(0.05, 0);

    double start = 1.0;

    MeasuresPool<unsigned int, double> mp;
    for (int i=0; i<100; i++) {
        mp.push(i, start/(i+1));
    }
    
    jb.run(mp);

    EXPECT_TRUE(jb.is_reject());

}

TEST_F(Test_KPSS_Test, DistributionREJECT_2) {

    TestKPSS<unsigned int, double> jb(0.05, 0);

    double start = 1.0;

    MeasuresPool<unsigned int, double> mp;
    double a_2 = 0;
    double a_1 = 0;

    for (int i=0; i<100; i++) {
        double a = start/(i+1);
        mp.push(i, a + a_1 + a_2);
        a_2 = a_1;
        a_1 = a;
    }
    
    jb.run(mp);

    EXPECT_TRUE(jb.is_reject());

}

