#include "simple_hello_world.hpp"

#include "evt/evtapproach_bm.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"
#include "input/generator_null.hpp"

#include <iostream>

using namespace chronovise;

using exit_code_t = AbstractExecutionContext<unsigned int, double>::exit_code_t;


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

    this->set_merging_technique(merger_type_e::ENVELOPE);

    this->use_evt_approach_BM(25, 0.1);
    
    this->use_estimator_MLE();

    this->use_KS_test(0.01);

    this->print_configuration_info();

    return AEC_OK;
}

exit_code_t SimpleHelloWorld::onConfigure() noexcept
{
    // Since no input generation is provided, we want to execute the estimation only 1 time.
    if (get_input_iteration() > 1)
        return AEC_OK;

    return AEC_CONTINUE;
}

exit_code_t SimpleHelloWorld::onRun() noexcept {

    static std::random_device random_dev;
    static std::mt19937 mt(random_dev());
    static std::normal_distribution<double> distribution(12.0,1.0);


    auto new_sample = distribution(mt);
    this->add_sample(new_sample);
    
    return AEC_OK;
}

exit_code_t SimpleHelloWorld::onMonitor() noexcept {
    return AEC_SLOTH;
}

exit_code_t SimpleHelloWorld::onRelease() noexcept {

    this->print_distributions_summary();

    this->print_wcots();

    std::cout << "pWCET(p=0.9999) is: " << this->get_pwcet_wcet(0.9999) << std::endl;
    std::cout << "pWCET(WCET=20) is: " << this->get_pwcet_probability(20) << std::endl;

    return AEC_OK;
}

