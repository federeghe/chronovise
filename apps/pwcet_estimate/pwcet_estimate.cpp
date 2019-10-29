#include "pwcet_estimate.hpp"

#include "evt/evtapproach_bm.hpp"
#include "statistical/estimator_pwm.hpp"

#include "input/generator_null.hpp"

#include <iostream>

using namespace chronovise;

using exit_code_t = AbstractExecutionContext<unsigned int, double>::exit_code_t;


exit_code_t PWCET_Estimate::onSetup() noexcept {

    /* ********** PRE-RUN SECTION  ********** */
    std::unique_ptr<chronovise::NullInputGenerator> null_input_gen(new chronovise::NullInputGenerator());
    this->set_input_source(std::move(null_input_gen));

    /* ********** POST-RUN SECTION ********** */
//    std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test(
//        new TestLjungBox<unsigned int, double>(0.01, 10)
//    );
//    this->add_sample_test(stat_test);


    this->set_merging_technique(merger_type_e::ENVELOPE);

    std::unique_ptr<EVTApproach<unsigned int, double>> evt_app(
        new EVTApproach_BM<unsigned int, double>(20)
    );
    this->set_evt_approach(std::move(evt_app), 0.5);

    std::unique_ptr<Estimator<unsigned int, double>> evt_est(
        new Estimator_PWM<unsigned int, double>()
    );
    this->set_evt_estimator(std::move(evt_est));


    this->ks_test = std::make_shared<TestKS<unsigned int, double>> (
        0.05, distribution_t::EVT_GEV
    );
    this->add_post_evt_test(ks_test);


    this->print_configuration_info();
    this->print_legend();

    return AEC_OK;
}

exit_code_t PWCET_Estimate::onConfigure() noexcept
{
    copy_mp_it = copy_mp.cbegin();

    if (get_input_iteration() > 0)
        return AEC_OK;

    return AEC_CONTINUE;
}

exit_code_t PWCET_Estimate::onRun() noexcept {

    this->add_sample(copy_mp_it->second);

    copy_mp_it++;

    return AEC_OK;
}

exit_code_t PWCET_Estimate::onMonitor() noexcept {

    if (copy_mp_it == copy_mp.cend()) {
        return AEC_OK;
    } else {
        return AEC_CONTINUE;
    }
}

exit_code_t PWCET_Estimate::onRelease() noexcept {

    this->print_distributions_summary();

    this->print_wcots();

    std::cout << "KS-Test result: " << this->ks_test->get_statistic() << ">" << this->ks_test->get_critical_value() << std::endl;

    std::cout << "pWCET(p=0.9999) is: " << this->get_pwcet_wcet(0.9999) << std::endl;
    //this->print_pwcet_probability(1000);

    return AEC_OK;
}

