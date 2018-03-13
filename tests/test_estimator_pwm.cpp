#include "gtest/gtest.h"
#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
#include "statistical/estimator_pwm.hpp"
#include "utility/oop.hpp"

using namespace chronovise;

class EstimatorPWM_Test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    EstimatorPWM_Test() 
    {
        // You can do set-up work for each test here.
    }

    virtual ~EstimatorPWM_Test() {
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

TEST_F(EstimatorPWM_Test, GPD_0_1_0) {

    constexpr int n_elem = 200;
    double xs[n_elem] =
    {
1.819034,0.230314,1.167271,0.637650,1.797886,0.507528,1.335710,0.424527,0.372203,0.290150,0.797305,2.479067,1.474134,0.090650,1.881391,0.191382,0.619260,0.003873,2.548799,0.814912,2.238177,0.038847,5.374286,0.255008,0.201745,0.140764,2.471763,0.916834,1.347572,0.223058,0.840687,0.093599,1.704589,1.332553,1.927311,1.994596,0.140076,0.545237,0.598091,1.931333,0.158959,0.474727,1.047105,0.666993,0.911781,2.577460,1.427466,2.092981,1.693321,1.427314,0.874029,3.002668,0.102347,0.056796,0.711588,0.714876,1.085540,0.105301,0.996290,2.196400,0.248138,0.942278,1.420094,0.906558,2.338684,2.025156,0.059696,0.044857,0.553023,2.817092,1.449107,1.040838,0.196996,4.173165,3.146002,1.777916,0.432145,0.312354,0.434257,0.796457,0.603290,1.216313,0.294783,1.666246,0.375748,1.695480,0.998356,0.469014,0.248170,2.511755,0.073231,0.253973,0.719919,0.830437,0.805681,1.183029,0.676273,0.671833,0.201348,0.229625,0.439563,0.971250,0.208772,0.629561,1.047747,0.062938,0.132454,0.597553,0.474052,0.532654,1.571457,1.199827,0.753060,1.467556,0.169237,1.635965,1.487566,1.767801,1.479883,0.830804,1.167634,0.079715,0.843488,1.688393,0.099952,0.020459,0.823552,2.197152,1.354545,0.894725,0.519369,1.338603,0.506098,0.340779,1.506219,2.142018,1.215115,1.143259,0.857629,0.677553,2.459054,1.337572,0.221876,3.532892,0.073804,0.314258,0.716193,0.547273,1.438499,0.779034,0.037610,0.603662,0.651745,1.462768,0.715602,0.471509,0.386935,0.927566,1.001204,0.012091,3.277065,0.121978,0.090705,0.227925,2.315546,1.339903,1.092560,0.386063,1.991041,0.326801,2.237155,0.425019,0.704868,0.249678,0.335421,0.101235,0.115498,1.096126,0.358468,1.620449,3.488687,0.295614,0.693102,0.734131,0.100127,0.494515,0.481807,0.151472,0.216305,0.550396,1.698693,1.427400,0.120461,3.551759,0.713551,1.784225,0.021550,0.338702,0.692204, 0.693211};

    MeasuresPool<int, double> mp;
    for (int i=0; i<n_elem; i++) {
        mp.push(0, xs[i]);
    }

    Estimator_PWM<int, double> mle;
    mle.set_source_evt_approach(&typeid(EVTApproach_PoT<int, double>));
    mle.run(mp);
    auto res = mle.get_result();

    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_location(), 0., 5e-1);    
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_scale(), 1, 5e-1);
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_shape(), 0., 5e-1);

}



TEST_F(EstimatorPWM_Test, GPD_2_20_1) {

    constexpr int n_elem = 200;
    double xs[n_elem] =
    {
2.972253,12.615112,7.854437,12.186839,14.686876,9.724292,8.931033,17.720373,10.825809,2.873886,4.324948,2.573393,9.363876,13.881676,13.124022,21.863925,15.303356,6.609077,9.077864,13.039553,3.194545,2.428168,12.156383,13.166223,6.046873,19.590124,5.452777,7.074252,10.263555,15.940262,10.298249,10.502486,17.870576,20.857918,17.409326,2.219657,5.872224,21.140228,11.152038,16.706098,11.817679,10.357776,21.088323,4.483723,12.320992,18.115788,2.373304,3.947349,9.443776,14.620806,3.432844,4.029801,20.958898,20.237815,17.227604,15.312286,4.914226,21.698486,16.830726,7.574872,20.229929,4.759897,18.666830,12.968636,16.324473,11.045289,2.571211,19.024144,4.633637,12.231589,10.181876,21.932225,12.288877,7.371050,11.260571,2.269745,11.968961,21.005518,19.790748,12.570655,18.697562,12.889600,9.662577,19.700337,20.348584,21.619802,20.255484,13.717492,13.159500,4.875694,17.189338,5.132981,14.503189,21.619719,7.077687,18.711226,21.600973,10.293159,6.018056,8.367920,16.037691,11.298308,18.505867,11.354837,17.756975,8.312181,14.236784,17.408095,10.497336,19.384572,16.302854,20.472004,14.213144,4.590434,9.765381,14.664925,9.097005,9.658657,15.246266,18.689049,3.100474,11.800784,2.925731,12.601912,3.341977,6.165653,12.114481,21.726561,17.195699,13.242380,4.240435,3.735613,9.526876,12.615748,5.516989,14.747101,8.664883,15.034160,19.524621,12.671436,21.198630,11.065567,2.743819,18.308146,21.159540,13.087160,14.085170,2.596475,8.612978,7.396533,19.806913,12.100668,3.491440,8.557256,13.532752,15.623421,2.164351,6.911866,15.488838,14.436164,10.631625,7.352881,13.800982,9.726953,2.559820,4.876822,14.302165,16.537489,5.310755,12.155094,12.585103,19.095248,19.994198,15.940793,2.330914,20.446230,16.749579,14.743267,9.133148,20.073035,21.506312,15.766427,2.915881,3.894031,7.432066,8.885687,9.675695,17.727717,7.845240,18.250215,4.123982,20.837789,15.539371,4.930078,19.568696,6.999093,12.546647,15.949105,9.953557,17.752163
};
    
    MeasuresPool<int, double> mp;
    for (int i=0; i<n_elem; i++) {
        mp.push(0, xs[i]);
    }

    Estimator_PWM<int, double> mle;
    mle.set_source_evt_approach(&typeid(EVTApproach_PoT<int, double>));
    mle.run(mp);
    auto res = mle.get_result();

    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_location(), 2., 5e-1);    
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_scale(), 20., 5e-1);
    EXPECT_NEAR(std::dynamic_pointer_cast<GPD_Distribution>(res)->get_shape(), 1., 5e-1);

}


