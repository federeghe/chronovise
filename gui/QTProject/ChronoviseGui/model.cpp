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

    /* ********** POST-RUN SECTION ********** */

    switch(this->first_pre_test->get_combo_box_index())
    {
        case 1:             //Kwiatkowski–Phillips–Schmidt–Shin
        {
            this->first_pre_test->set_kpss_test(this->first_pre_test->get_significance_level(), this->first_pre_test->get_n_lags(), this->first_pre_test->get_trend_class());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_1(this->first_pre_test->get_kpss_test());
            this->add_sample_test(stat_test_1);
        }break;

        case 2:             //"Brock–Dechert–Scheinkman"
        {
            this->first_pre_test->set_bds_test(this->first_pre_test->get_significance_level());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_1(this->first_pre_test->get_bds_test());
            this->add_sample_test(stat_test_1);
        }break;

        case 3:              //"LjungBox"
        {
            this->first_pre_test->set_ljungBox_test(this->first_pre_test->get_significance_level(), this->first_pre_test->get_n_lags());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_1(this->first_pre_test->get_ljungBox_test());
            this->add_sample_test(stat_test_1);
        }break;

        case 4:             //"R/S"
        {
            this->first_pre_test->set_rs_test(this->first_pre_test->get_significance_level());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_1(this->first_pre_test->get_rs_test());
            this->add_sample_test(stat_test_1);
        }break;

        default:
            ;
    }

    switch(this->second_pre_test->get_combo_box_index())
    {
        case 1:             //Kwiatkowski–Phillips–Schmidt–Shin
        {
            this->second_pre_test->set_kpss_test(this->second_pre_test->get_significance_level(), this->second_pre_test->get_n_lags(), this->first_pre_test->get_trend_class());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_2(this->second_pre_test->get_kpss_test());
            this->add_sample_test(stat_test_2);
        }break;

        case 2:             //"Brock–Dechert–Scheinkman"
        {
            this->second_pre_test->set_bds_test(this->second_pre_test->get_significance_level());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_2(this->second_pre_test->get_bds_test());
            this->add_sample_test(stat_test_2);
        }break;

        case 3:              //"LjungBox"
        {
            this->second_pre_test->set_ljungBox_test(this->second_pre_test->get_significance_level(), this->second_pre_test->get_n_lags());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_2(this->second_pre_test->get_ljungBox_test());
            this->add_sample_test(stat_test_2);
        }break;


        case 4:             //"R/S"
        {
            this->second_pre_test->set_rs_test(this->second_pre_test->get_significance_level());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_2(this->second_pre_test->get_rs_test());
            this->add_sample_test(stat_test_2);
        }break;

        default:
            ;
    }

    switch(this->third_pre_test->get_combo_box_index())
    {
        case 1:             //Kwiatkowski–Phillips–Schmidt–Shin
        {
            this->third_pre_test->set_kpss_test(this->third_pre_test->get_significance_level(), this->third_pre_test->get_n_lags(), this->first_pre_test->get_trend_class());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_3(this->third_pre_test->get_kpss_test());
            this->add_sample_test(stat_test_3);
        }break;

        case 2:             //"Brock–Dechert–Scheinkman"
        {
            this->third_pre_test->set_bds_test(this->third_pre_test->get_significance_level());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_3(this->third_pre_test->get_bds_test());
            this->add_sample_test(stat_test_3);
        }break;

        case 3:              //"LjungBox"
        {
            this->third_pre_test->set_ljungBox_test(this->third_pre_test->get_significance_level(), this->third_pre_test->get_n_lags());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_3(this->third_pre_test->get_ljungBox_test());
            this->add_sample_test(stat_test_3);
        }break;


        case 4:             //"R/S"
        {
            this->third_pre_test->set_rs_test(this->third_pre_test->get_significance_level());
            std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test_3(this->third_pre_test->get_rs_test());
            this->add_sample_test(stat_test_3);
        }break;

        default:
            ;
    }



    // Select ENVELOPE as merging technique. The possible values are:
    // ENVELOPE: different inputs provide different pWCETs estimation
    // MERGER:   different inputs generating samples that are merged and only 1 pWCET estimation
    //           is performed.

    this->set_merging_technique(merger_type_e::ENVELOPE);

    // Select the EVT approach to use:
    // - Block Maxima -> It will generate a GEV
    // - PoT          -> It will generate a GPD

    if(this->get_evt_approach()->get_combo_box_index()==1)
    {
        this->get_evt_approach()->set_bm_approach(this->get_evt_approach()->get_block_size());
        std::unique_ptr<EVTApproach<unsigned int, double>> evt_app(this->get_evt_approach()->get_bm_approach());
        this->set_evt_approach(std::move(evt_app), 0.1);
    }
    if(this->get_evt_approach()->get_combo_box_index()==2)
    {
        this->get_evt_approach()->set_pot_approach(this->get_evt_approach()->get_threshold());
        std::unique_ptr<EVTApproach<unsigned int, double>> evt_app(this->get_evt_approach()->get_pot_approach());
        this->set_evt_approach(std::move(evt_app), 0.1);
    }



    // Select the estimator.
    switch(this->evt_estimator->get_combo_box_index())
    {
        case 1:             //PWM
        {
            this->evt_estimator->set_pwm_estimator();
            std::unique_ptr<Estimator<unsigned int, double>> evt_est(this->get_evt_estimator()->get_pwm_estimator());
            this->set_evt_estimator(std::move(evt_est));
        } break;

        case 2:             //MLE
        {
            this->evt_estimator->set_mle_estimator();
            std::unique_ptr<Estimator<unsigned int, double>> evt_est(this->get_evt_estimator()->get_mle_estimator());
            this->set_evt_estimator(std::move(evt_est));
        }break;

        case 3:             //GMLE
        {
            this->evt_estimator->set_gmle_estimator();
            std::unique_ptr<Estimator<unsigned int, double>> evt_est(this->get_evt_estimator()->get_gmle_estimator());
            this->set_evt_estimator(std::move(evt_est));
        }break;

        default:
            ;
    }


    //set the gof post-test
    switch(this->get_post_test()->get_combo_box_index())
    {
        case 1:             //Kolmogorov-Smirnov
        {
            this->post_test->set_ks_test(this->post_test->get_significance_level(),this->get_evt_approach()->get_combo_box_index());
            std::shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> aft_test(this->post_test->get_ks_test());
            this->add_post_evt_test(aft_test);
        }break;

        case 2:             //Cramér–von Mises criterion
        {
            this->post_test->set_cvm_test(this->post_test->get_significance_level(),this->get_evt_approach()->get_combo_box_index());
            std::shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> aft_test(this->post_test->get_cvm_test());
            this->add_post_evt_test(aft_test);
        }break;

        case 3:              //Anderson-Darling
        {
            this->post_test->set_ad_test(this->post_test->get_significance_level(),this->get_evt_approach()->get_combo_box_index(),false);
            std::shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> aft_test(this->post_test->get_ad_test());
            this->add_post_evt_test(aft_test);
        }break;


        case 4:             //Modified Anderson-Darling
        {
            this->post_test->set_ad_test(this->post_test->get_significance_level(),this->get_evt_approach()->get_combo_box_index(),true);
            std::shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> aft_test(this->post_test->get_ad_test());
            this->add_post_evt_test(aft_test);
        }break;

        default:
            ;
    }







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
    switch(this->first_pre_test->get_combo_box_index())
    {
        case 1:             //Kwiatkowski–Phillips–Schmidt–Shin
        {
            this->first_pre_test->set_critical_value(this->first_pre_test->get_kpss_test()->get_critical_value());
            this->first_pre_test->set_statistic(this->first_pre_test->get_kpss_test()->get_statistic());
            this->first_pre_test->set_reject(this->first_pre_test->get_kpss_test()->is_reject());
        }break;

        case 2:             //"Brock–Dechert–Scheinkman"
        {
            this->first_pre_test->set_critical_value(this->first_pre_test->get_bds_test()->get_critical_value());
            this->first_pre_test->set_statistic(this->first_pre_test->get_bds_test()->get_statistic());
            this->first_pre_test->set_reject(this->first_pre_test->get_bds_test()->is_reject());
        }break;


        case 3:              //"LjungBox"
        {
            this->first_pre_test->set_critical_value(this->first_pre_test->get_ljungBox_test()->get_critical_value());
            this->first_pre_test->set_statistic(this->first_pre_test->get_ljungBox_test()->get_statistic());
            this->first_pre_test->set_reject(this->first_pre_test->get_ljungBox_test()->is_reject());
        }break;

        case 4:             //"R/S"
        {
            this->first_pre_test->set_critical_value(this->first_pre_test->get_rs_test()->get_critical_value());
            this->first_pre_test->set_statistic(this->first_pre_test->get_rs_test()->get_statistic());
            this->first_pre_test->set_reject(this->first_pre_test->get_rs_test()->is_reject());
        }break;

        default:
            ;
    }

    switch(this->second_pre_test->get_combo_box_index())
    {
        case 1:             //Kwiatkowski–Phillips–Schmidt–Shin
        {
            this->second_pre_test->set_critical_value(this->second_pre_test->get_kpss_test()->get_critical_value());
            this->second_pre_test->set_statistic(this->second_pre_test->get_kpss_test()->get_statistic());
            this->second_pre_test->set_reject(this->second_pre_test->get_kpss_test()->is_reject());
        }break;

        case 2:             //"Brock–Dechert–Scheinkman"
        {
            this->second_pre_test->set_critical_value(this->second_pre_test->get_bds_test()->get_critical_value());
            this->second_pre_test->set_statistic(this->second_pre_test->get_bds_test()->get_statistic());
            this->second_pre_test->set_reject(this->second_pre_test->get_bds_test()->is_reject());
        }break;


        case 3:              //"LjungBox"
        {
            this->second_pre_test->set_critical_value(this->second_pre_test->get_ljungBox_test()->get_critical_value());
            this->second_pre_test->set_statistic(this->second_pre_test->get_ljungBox_test()->get_statistic());
            this->second_pre_test->set_reject(this->second_pre_test->get_ljungBox_test()->is_reject());
        }break;

        case 4:             //"R/S"
        {
            this->second_pre_test->set_critical_value(this->second_pre_test->get_rs_test()->get_critical_value());
            this->second_pre_test->set_statistic(this->second_pre_test->get_rs_test()->get_statistic());
            this->second_pre_test->set_reject(this->second_pre_test->get_rs_test()->is_reject());
        }break;

        default:
            ;
    }

    switch(this->third_pre_test->get_combo_box_index())
    {
        case 1:             //Kwiatkowski–Phillips–Schmidt–Shin
        {
            this->third_pre_test->set_critical_value(this->third_pre_test->get_kpss_test()->get_critical_value());
            this->third_pre_test->set_statistic(this->third_pre_test->get_kpss_test()->get_statistic());
            this->third_pre_test->set_reject(this->third_pre_test->get_kpss_test()->is_reject());
        }break;

        case 2:             //"Brock–Dechert–Scheinkman"
        {
            this->third_pre_test->set_critical_value(this->third_pre_test->get_bds_test()->get_critical_value());
            this->third_pre_test->set_statistic(this->third_pre_test->get_bds_test()->get_statistic());
            this->third_pre_test->set_reject(this->third_pre_test->get_bds_test()->is_reject());
        }break;


        case 3:              //"LjungBox"
        {
            this->third_pre_test->set_critical_value(this->third_pre_test->get_ljungBox_test()->get_critical_value());
            this->third_pre_test->set_statistic(this->third_pre_test->get_ljungBox_test()->get_statistic());
            this->third_pre_test->set_reject(this->third_pre_test->get_ljungBox_test()->is_reject());
        }break;

        case 4:             //"R/S"
        {
            this->third_pre_test->set_critical_value(this->third_pre_test->get_rs_test()->get_critical_value());
            this->third_pre_test->set_statistic(this->third_pre_test->get_rs_test()->get_statistic());
            this->third_pre_test->set_reject(this->third_pre_test->get_rs_test()->is_reject());
        }break;

        default:
            ;
    }

    switch(this->post_test->get_combo_box_index())
    {
        case 1:
        {
            this->post_test->set_reject(this->post_test->get_ks_test()->is_reject());
        }break;

        case 2:
        {
            this->post_test->set_reject(this->post_test->get_cvm_test()->is_reject());
        }break;


        case 3:
        {
            this->post_test->set_reject(this->post_test->get_ad_test()->is_reject());
        }break;

        case 4:
        {
            this->post_test->set_reject(this->post_test->get_ad_test()->is_reject());
        }break;

        default:
            ;
    }

    //retrieve information about the distribution from the estimator
    switch(this->evt_estimator->get_combo_box_index())
    {
        case 1:             //PWM
        {
            std::shared_ptr<Distribution> dist = this->evt_estimator->get_pwm_estimator()->get_result();
            if(this->get_evt_approach()->get_combo_box_index()==1)
            {
                this->get_distribution()->set_gev_distribution(dist);
            }
            if(this->get_evt_approach()->get_combo_box_index()==2)
            {
                this->get_distribution()->set_gpd_distribution(dist);
            }

        }break;

        case 2:             //MLE
        {
            std::shared_ptr<Distribution> dist = this->evt_estimator->get_mle_estimator()->get_result();
            if(this->get_evt_approach()->get_combo_box_index()==1)
            {
                this->get_distribution()->set_gev_distribution(dist);
            }
            if(this->get_evt_approach()->get_combo_box_index()==2)
            {
                this->get_distribution()->set_gpd_distribution(dist);
            }
        }break;

        case 3:             //GMLE
        {
            std::shared_ptr<Distribution> dist = this->evt_estimator->get_gmle_estimator()->get_result();
            if(this->get_evt_approach()->get_combo_box_index()==1)
            {
                this->get_distribution()->set_gev_distribution(dist);
            }
            if(this->get_evt_approach()->get_combo_box_index()==2)
            {
                this->get_distribution()->set_gpd_distribution(dist);
            }
        }break;

    default:
        ;
    }
}
