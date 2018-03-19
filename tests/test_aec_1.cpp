#include "gtest/gtest.h"

#define VERBOSITY_NONE 

#include "input/generator_null.hpp"
#include "evt/evtapproach_bm.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"
#include "aec.hpp"
#include "measures_pool.hpp"
#include "timing.hpp"

using namespace chronovise;

#include <cmath>
#include <iostream>


const double normal_nums[500] =
{9.8614,10.432,12.253,9.5404,10.09,12.608,8.9628,10.253,9.7334,11.317,10.112,11.271,10.412,10.758,8.3277,9.2665,8.6768,8.4884,10.911,11.044,9.863,9.0096,11.044,11.825,10.703,9.1778,9.5507,10.703,10.062,11.026,9.0181,11.536,9.7121,9.2887,8.825,10.856,9.6638,9.7258,9.6227,8.9603,9.2916,9.8808,12.169,9.6234,10.799,9.058,10.873,10.896,10.716,10.372,8.1748,9.8584,10.601,8.1907,9.5811,11.198,10.034,11.356,9.6617,11.239,10.16,10.678,8.5583,8.5205,10.488,9.6413,8.1748,9.5469,9.6444,9.1452,8.7532,10.222,10.336,9.1975,11.324,9.5126,8.0193,10.023,10.814,8.1025,11.878,9.7093,9.1771,10.284,9.4605,10.95,11.328,10.437,9.9945,8.2967,9.2362,10.022,8.0018,8.9461,10.15,8.7681,9.2288,10.301,10.189,10.119,12.441,10.671,9.3205,10.049,11.16,11.809,10.685,9.222,10.686,10.568,10.525,9.9463,9.7821,10.097,9.4012,10.594,9.9493,11.332,10.746,10.226,11.332,10.868,10.34,9.0894,11.333,9.8737,9.6484,10.03,11.068,10.119,8.8634,9.7192,9.1938,9.7282,8.7487,10.356,9.6552,9.1161,9.4187,11.27,8.8049,10.486,10.169,8.8064,10.04,9.0747,10.836,10.551,9.883,9.0108,9.4801,9.5019,10.345,11.246,10.759,9.5549,8.117,9.2641,10.353,8.9389,9.9948,11.473,11.625,10.176,11.77,10.57,10.709,10.557,9.507,10.196,10.518,11.186,7.4286,9.146,11.387,10.652,10.218,10.523,11.183,9.0547,10.411,8.1191,10.132,10.096,11.26,9.2653,10.545,10.956,9.2933,10.312,10.049,9.8262,9.5017,9.3377,8.832,9.5367,9.07,9.9538,11.565,9.7037,10.972,10.488,11.35,9.9935,9.9006,9.8487,8.7825,12.032,8.573,9.876,9.6335,10.074,8.5688,10.779,9.9568,9.771,11.422,10.675,11.719,11.314,9.4528,9.7441,11.247,9.5829,9.9248,9.551,10.417,11.075,9.3911,9.4981,10.954,11.71,10.952,8.6271,9.9316,10.315,10.073,9.4711,8.2442,11.207,11.062,10.723,9.6222,8.6855,10.584,9.1387,9.7603,11.25,10.962,9.6709,10.366,9.3372,9.2158,9.8019,8.713,11.888,10.504,9.2376,9.993,10.96,9.8262,9.7701,10.778,11.477,10.869,10.136,10.531,10.023,9.5517,9.3415,9.2148,9.153,10.011,8.4116,9.872,8.4868,9.7316,9.0797,10.146,10.973,8.32,9.2514,9.251,9.5393,9.8062,9.071,9.7437,10.993,10.144,9.5009,10.305,10.544,8.2234,9.8252,11.987,10.057,10.175,11.576,8.7951,10.853,9.6927,10.248,10.603,9.7923,9.364,10.642,9.8769,10.109,10.596,10.901,9.7518,9.0267,10.426,11.311,9.38,10.499,11.414,9.9272,10.331,9.8897,9.0752,9.1991,8.7693,9.8319,11.803,10.234,11.628,9.102,9.5005,11.734,8.641,8.6962,11.997,10.985,10.235,10.064,11.116,10.65,10.752,11.436,11.286,10.24,8.6507,11.37,8.9985,7.5068,10.38,10.149,9.4116,10.149,11.385,10.345,9.7125,10.105,8.341,8.5111,8.9308,8.8557,12.207,10.571,10.988,9.7107,9.2682,10.797,10.409,9.5758,8.2073,12.088,12.02,8.9296,11.248,9.7053,9.3807,8.9617,9.5426,10.166,8.5652,10.115,8.4636,9.8284,9.0429,11.255,9.2975,9.7747,10.428,9.7923,9.4227,8.2341,9.6059,11.141,10.419,8.8406,10.956,9.8617,10.74,10.152,7.68,8.9336,11.597,9.8099,9.3882,10.272,10.574,9.273,10.306,8.7326,9.3166,9.3744,10.189,11.917,10.596,9.0886,8.3215,9.2163,11.494,10.522,8.9126,11.333,9.1543,9.9634,9.2982,9.9871,9.3145,9.2577,9.2574,12.034,7.9941,11.023,9.5367,10.551,11.034,8.5332,10.741,9.7453,8.9694,9.9681,9.9079,10.308,10.404,9.6946,10.748,10.308,11.274,11.424,9.5094,9.7234,11.07,12.027,11.297,9.9991,10.212,11.609,8.8774,9.7541,9.2081,11.397,8.7496,9.4788,10.06,10.33,9.603,8.9837,9.6688,9.6742,8.8149,8.6618,10.204,10.695,10.534,9.9999,9.3735,8.3412,8.9908,9.3788,9.7025,10.243,10.221,10.818,10.34,8.5989,10.777,8.916,9.5172,9.2507,10.618,8.2211,10.575,9.2353,9.1106,8.6325,9.1304,8.7278,9.0512,11.132,9.7645,8.8926,11.135,10.561,10.335,9.4081};


// The fixture for testing class Project1. From google test primer.
class AEC_1_Test : public ::testing::Test {
protected:


};

class EC_1 : public chronovise::AbstractExecutionContext<unsigned int, double> {

public:
    EC_1() : null_input_dist(
        new chronovise::NullInputGenerator
    ) {}

    virtual exit_code_t onSetup() {

        /* ********** PRE-RUN SECTION  ********** */
        this->set_input_source(std::move(null_input_dist));
    //    this->add_input_transformer();        // TODO
    //    this->add_representativity_test();    // TODO

        /* ********** POST-RUN SECTION ********** */
        std::shared_ptr<StatisticalTest<unsigned int,double>> stat_test(
            new TestLjungBox<unsigned int,double>(0.05, 10)
        );
        this->add_sample_test(stat_test);

        this->set_merging_technique(merger_type_e::ENVELOPE);

        std::unique_ptr<EVTApproach<unsigned int, double>> evt_app(
            new EVTApproach_BM<unsigned int, double>(10)
        );
        this->set_evt_approach(std::move(evt_app), 0.45);
        
        std::unique_ptr<Estimator<unsigned int, double>> evt_est(
            new Estimator_MLE<unsigned int, double>()
        );
        this->set_evt_estimator(std::move(evt_est));

        std::shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> aft_test(
            new TestKS<unsigned int, double>(0.05, distribution_t::EVT_GEV)
        );
        this->add_post_evt_test(aft_test);

        return AEC_OK;
    }

    virtual exit_code_t onConfigure() {
        return get_input_iteration() > 0 ? AEC_OK : AEC_CONTINUE;
    }

    virtual exit_code_t onRun() {
        this->add_sample( normal_nums[get_iteration()] );
        return AEC_OK;
    }

    virtual exit_code_t onMonitor() {

        if (get_iteration() >= 500) {
            throw std::runtime_error("Maximum iteration reached.");
        }

        return AEC_SLOTH;
    }

    virtual exit_code_t onRelease() {
        return AEC_OK;
    }

private:
    chronovise::Timing timing;
    std::unique_ptr<chronovise::NullInputGenerator> null_input_dist;


};


TEST_F(AEC_1_Test, 0) {


    chronovise::AbstractExecutionContext<unsigned int, double> *aec = new EC_1();

    testing::internal::CaptureStderr();
    ASSERT_NO_THROW(aec->run());

    const auto &wcot_list = aec->get_wcots();
    EXPECT_EQ(*std::max_element(normal_nums, normal_nums+500), wcot_list.max());

}

