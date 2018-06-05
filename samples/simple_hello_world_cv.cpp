#include "simple_hello_world.hpp"

#include "evt/evtapproach_cv.hpp"
#include "statistical/estimator_cv.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"
#include "input/generator_null.hpp"

#include <iostream>
#include <iomanip>

using namespace chronovise;

using exit_code_t = AbstractExecutionContext<unsigned int, double>::exit_code_t;

SimpleHelloWorld::SimpleHelloWorld() noexcept {
    // Nothing to do...
}

exit_code_t SimpleHelloWorld::onSetup() noexcept {

    /* ********** PRE-RUN SECTION  ********** */

    // In this simple example we are not interested in multi-input programs, so let's define a
    // a Null input generator.
    std::unique_ptr<chronovise::NullInputGenerator> null_input_gen(new chronovise::NullInputGenerator());
    this->set_input_source(std::move(null_input_gen));

    /* ********** POST-RUN SECTION ********** */

    // Set LjungBox test as the test to be used after the sampling phase.
    // 1st parameter: significance level
    // 2nd parameter: number of lags for the test 
    this->use_LjungBox_as_sample_test(0.01, 10);

    // Select ENVELOPE as merging technique. The possible values are:
    // ENVELOPE: different inputs provide different pWCETs estimation
    // MERGER:   different inputs generating samples that are merged and only 1 pWCET estimation
    //           is performed.
    this->set_merging_technique(merger_type_e::ENVELOPE);

    // Select the EVT approach to use:
    // - Block Maxima -> It will generate a GEV
    // - PoT          -> It will generate a GPD
    this->use_evt_approach_CV(0.1);
    //this->use_evt_approach_PoT(13.5, 0.1);

    // Select the estimator. Currently the only one available is the Maximum-Likelihood-Estimator
    this->use_estimator_CV();

    // Select the Kolmogorov-Smirnov test as test on the estimated probability distribution for
    // pWCET
//    this->use_KS_as_post_evt_test(0.01);

    // Let's print some debug information
    this->print_configuration_info();
    this->print_legend();

    return AEC_OK;
}

exit_code_t SimpleHelloWorld::onConfigure() noexcept
{
    // Since no input generation is provided, we want to execute the estimation only 1 time.
    if (get_input_iteration() > 0)
        return AEC_OK;

    return AEC_CONTINUE;
}

exit_code_t SimpleHelloWorld::onRun() noexcept {

    // Some C++11 stuffs to initialize the random normal distribution
    static std::random_device random_dev;
    static std::mt19937 mt(random_dev());
    static std::normal_distribution<double> distribution(12.0,1.0);

    // Add a new sample as a "time measure" drawned by an i.i.d. normal distribution.
    auto new_sample = distribution(mt);
    this->add_sample(new_sample);
    
    return AEC_OK;
}

exit_code_t SimpleHelloWorld::onMonitor() noexcept {

    // Let chronovise to decide when it's time to stop
    return AEC_SLOTH;
}

exit_code_t SimpleHelloWorld::onRelease() noexcept {

    this->print_evt_info();

    // Print of the results, etc.
    this->print_distributions_summary();

    this->print_wcots();

    std::cout << "pWCET(p=0.999999) is: " << this->get_pwcet_wcet(0.999999) << std::endl;
    std::cout << "pWCET(p=1-10^(-9)) is: " << this->get_pwcet_wcet(1 - std::pow(10., -9.)) << std::endl;
    double prob= this->get_pwcet_probability(16.8);
    std::cout << "pWCET(WCET=16.8) is: " << std::setprecision(16) << prob << std::endl;

    return AEC_OK;
}

