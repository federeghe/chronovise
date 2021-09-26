#include "model.h"
#include "evt/evtapproach_cv.hpp"
#include "statistical/estimator_cv.hpp"
#include "statistical/test_ks.hpp"

#include "input/generator_null.hpp"
#include <iostream>
#include <memory>



using exit_code_t = AbstractExecutionContext<unsigned int, double>::exit_code_t;


Model::Model() noexcept
{
    this->input_file = new FileImportModel();
    this->first_pre_test = new TestPreModel();
    this->second_pre_test = new TestPreModel();
    this->third_pre_test = new TestPreModel();
    this->post_test = new TestPostModel();
    this->evt_approach = new EVTApproachModel();
    this->evt_estimator = new EVTEstimatorModel();
    this->distribution = new DistributionModel();
    this->plot_data = new PlotModel();

}

Model::~Model()
{
    delete this->input_file;
    delete this->first_pre_test;
    delete this->second_pre_test;
    delete this->third_pre_test;
    delete this->post_test;
    delete this->evt_approach;
    delete this->evt_estimator;
    delete this->distribution;
    delete this->plot_data;
}

void Model::copy(Model* model)
{
    this->input_file->set_input_file_name(model->get_input_file()->get_input_file_name());

    this->first_pre_test->set_combo_box_index(model->first_pre_test->get_combo_box_index());
    this->first_pre_test->set_significance_level(model->first_pre_test->get_significance_level());
    this->first_pre_test->set_n_lags(model->first_pre_test->get_n_lags());
    this->first_pre_test->set_trend_class(model->first_pre_test->get_trend_class());

    this->second_pre_test->set_combo_box_index(model->second_pre_test->get_combo_box_index());
    this->second_pre_test->set_significance_level(model->second_pre_test->get_significance_level());
    this->second_pre_test->set_n_lags(model->second_pre_test->get_n_lags());
    this->second_pre_test->set_trend_class(model->second_pre_test->get_trend_class());

    this->third_pre_test->set_combo_box_index(model->third_pre_test->get_combo_box_index());
    this->third_pre_test->set_significance_level(model->third_pre_test->get_significance_level());
    this->third_pre_test->set_n_lags(model->third_pre_test->get_n_lags());
    this->third_pre_test->set_trend_class(model->third_pre_test->get_trend_class());

    this->post_test->set_combo_box_index(model->post_test->get_combo_box_index());
    this->post_test->set_significance_level(model->post_test->get_significance_level());

    this->evt_approach->set_combo_box_index(model->evt_approach->get_combo_box_index());
    this->evt_approach->set_block_size(model->evt_approach->get_block_size());
    this->evt_approach->set_threshold(model->evt_approach->get_threshold());
    this->evt_approach->set_samples_test_reserve(model->evt_approach->get_samples_test_reserve());

    this->evt_estimator->set_combo_box_index(model->evt_estimator->get_combo_box_index());
}

void Model::set_pwcet99999(double value)
{
    this->pwcet99999=value;
}
void Model::set_pwcet_109(double value)
{
    this->pwcet_109=value;
}



FileImportModel* Model::get_input_file()
{
    return this->input_file;
}

TestPreModel* Model::get_first_pre_test()
{
    return this->first_pre_test;
}
TestPreModel* Model::get_second_pre_test()
{
    return this->second_pre_test;
}
TestPreModel* Model::get_third_pre_test()
{
    return this->third_pre_test;
}

TestPostModel* Model::get_post_test()
{
    return this->post_test;
}

EVTApproachModel* Model::get_evt_approach()
{
    return this->evt_approach;
}
EVTEstimatorModel* Model::get_evt_estimator()
{
    return this->evt_estimator;
}
DistributionModel* Model::get_distribution()
{
    return this->distribution;
}
PlotModel* Model::get_plot_data()
{
    return this->plot_data;
}

double Model::get_pwcet99999()
{
    return this->pwcet99999;
}
double Model::get_pwcet_109()
{
    return this->pwcet_109;
}




//beginning of actual chronovise framework
exit_code_t Model::onSetup() noexcept
{

    /* ********** PRE-RUN SECTION  ********** */

    // In this simple example we are not interested in multi-input programs, so let's define a
    // a Null input generator.
    std::unique_ptr<chronovise::NullInputGenerator> null_input_gen(new chronovise::NullInputGenerator());
    this->set_input_source(std::move(null_input_gen));



    //pre-run test
    this->first_pre_test->set_test(this->first_pre_test->get_combo_box_index());
    if(this->get_first_pre_test()->get_combo_box_index()!=0)
        this->add_sample_test(this->first_pre_test->get_test());

    this->second_pre_test->set_test(this->second_pre_test->get_combo_box_index());
    if(this->get_second_pre_test()->get_combo_box_index()!=0)
        this->add_sample_test(this->second_pre_test->get_test());

    this->third_pre_test->set_test(this->third_pre_test->get_combo_box_index());
    if(this->get_third_pre_test()->get_combo_box_index()!=0)
        this->add_sample_test(this->third_pre_test->get_test());



    // Select ENVELOPE as merging technique. The possible values are:
    // ENVELOPE: different inputs provide different pWCETs estimation
    // MERGER:   different inputs generating samples that are merged and only 1 pWCET estimation
    //           is performed.

    this->set_merging_technique(merger_type_e::ENVELOPE);

    // Select the EVT approach to use:
    // - Block Maxima -> It will generate a GEV
    // - PoT          -> It will generate a GPD

    this->get_evt_approach()->set_approach(this->get_evt_approach()->get_combo_box_index());
    this->set_evt_approach(std::move(this->get_evt_approach()->get_approach()), this->get_evt_approach()->get_samples_test_reserve());

    // Select the estimator.
    this->get_evt_estimator()->set_estimator(this->get_evt_estimator()->get_combo_box_index());
    this->set_evt_estimator(std::move(this->get_evt_estimator()->get_estimator()));


    /* ********** POST-RUN SECTION ********** */

    //set the gof post-test
    this->post_test->set_test(this->post_test->get_combo_box_index(),this->evt_approach->get_combo_box_index());
    if(this->get_post_test()->get_combo_box_index()!=0)
        this->add_post_evt_test(this->post_test->get_test());


    // Let's print some debug information
    this->print_configuration_info();
    this->print_legend();

    // Gather input values from file
    this->use_file_as_source(this->input_file->get_input_file_name());

    return AEC_OK;
}

exit_code_t Model::onConfigure() noexcept
{
    // Since no input generation is provided, we want to execute the estimation only 1 time.
    if (get_input_iteration() > 0)
        return AEC_OK;

    return AEC_CONTINUE;
}

exit_code_t Model::onRun() noexcept
{

//    std::cout << get_iteration() << std::endl;

    try
    {

        // Get a sample from the file specified
        // in onSetup().
        this->add_sample_from_file();

    } catch(const std::ios::failure &ex) {
        std::cout << std::endl << "INPUT ERROR: "
                  << ex.what() << std::endl;
        return AEC_INPUT_ERROR;
    }

    return AEC_OK;
}


exit_code_t Model::onMonitor() noexcept
{
    int size = this->input_file->count_num_line(this->input_file->get_input_file_name());

    if (get_iteration() >= size-1)
    {
        return AEC_OK;
    }
    else
    {
        return AEC_CONTINUE;
    }
}

exit_code_t Model::onRelease() noexcept
{

    this->print_evt_info();

    // Print of the results, etc.
    this->print_distributions_summary();

    this->print_wcots();

    this->set_pwcet99999(this->get_pwcet_wcet(0.999999));
    this->set_pwcet_109(this->get_pwcet_wcet(1 - std::pow(10., -9.)));
    //double prob= this->get_pwcet_probability(16.8);
    //std::cout << "pWCET(WCET=16.8) is: " << std::setprecision(16) << prob << std::endl;

    return AEC_OK;
}

void Model::custom_run()
{
    this->run();

    //retrieve results from pre tests
    if(this->get_first_pre_test()->get_combo_box_index()!=0)
    {
        this->first_pre_test->set_critical_value(this->first_pre_test->get_test()->get_critical_value());
        this->first_pre_test->set_statistic(this->first_pre_test->get_test()->get_statistic());
        this->first_pre_test->set_reject(this->first_pre_test->get_test()->is_reject());
    }

    if(this->get_second_pre_test()->get_combo_box_index()!=0)
    {
        this->second_pre_test->set_critical_value(this->second_pre_test->get_test()->get_critical_value());
        this->second_pre_test->set_statistic(this->second_pre_test->get_test()->get_statistic());
        this->second_pre_test->set_reject(this->second_pre_test->get_test()->is_reject());
    }

    if(this->get_third_pre_test()->get_combo_box_index()!=0)
    {
        this->third_pre_test->set_critical_value(this->third_pre_test->get_test()->get_critical_value());
        this->third_pre_test->set_statistic(this->third_pre_test->get_test()->get_statistic());
        this->third_pre_test->set_reject(this->third_pre_test->get_test()->is_reject());
    }



    //retrieve results from post tests
    if(this->get_post_test()->get_combo_box_index()!=0)
    {
        this->post_test->set_reject(this->post_test->get_test()->is_reject());
        this->post_test->set_critical_value(this->post_test->get_test()->get_critical_value());
        this->post_test->set_statistic(this->post_test->get_test()->get_statistic());
    }



    //retrieve information about the distribution from the estimator
    this->get_distribution()->set_dist(this->get_evt_approach()->get_combo_box_index(),this->get_estimated_distributions());


}
