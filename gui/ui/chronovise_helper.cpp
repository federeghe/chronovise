#include "chronovise_helper.h"
#include "chronovise/measures_pool.hpp"
#include "chronovise/evt/evtapproach_cv.hpp"
#include "chronovise/evt/evtapproach_pot.hpp"
#include "chronovise/evt/evtapproach_bm.hpp"
#include "chronovise/evt/gpd_distribution.hpp"
#include "chronovise/evt/gev_distribution.hpp"
#include "chronovise/evt/pwcet.hpp"
#include "chronovise/statistical/estimator_pwm.hpp"
#include "chronovise/statistical/estimator_mle.hpp"
#include "chronovise/statistical/test_kpss.hpp"
#include "chronovise/statistical/test_bds.hpp"
#include "chronovise/statistical/test_rs.hpp"
#include "chronovise/statistical/test_ks.hpp"
#include "chronovise/statistical/test_ad.hpp"
#include "chronovise/statistical/test_cvm.hpp"
#include "utility.h"



template<typename T>
void execute_pwcet_estimation(const chronovise::MeasuresPool<int, T> &mp, t_computation_param &params ,t_computation_results<T> &results) {

    std::unique_ptr<chronovise::EVTApproach<int, T>> evt_app;

    switch (params.evt_approach) {
        case BM:
                evt_app = std::unique_ptr<chronovise::EVTApproach<int, T>>(new chronovise::EVTApproach_BM<int, T>(20));
            break;
        case PoT:{
                T threshold = search_threshold(mp);
                evt_app = std::unique_ptr<chronovise::EVTApproach<int, T>>(new chronovise::EVTApproach_PoT<int, T>(threshold));
            }
            break;

         case CV:
                T threshold = search_threshold(mp);
                evt_app = std::unique_ptr<chronovise::EVTApproach<int, T>>(new chronovise::EVTApproach_CV<int, T>());
            break;

    }


    chronovise::MeasuresPoolSet<int, T> mps(mp, 0.8, 0.2);

    evt_app->perform(mps);

    const auto &new_mp = evt_app->get_training_pool();

    chronovise::Estimator_PWM<int, T> est_pwm;

    est_pwm.set_source_evt_approach(&typeid(*evt_app));

    est_pwm.run(new_mp);


    std::shared_ptr<chronovise::Distribution> dist;

    // Block-Maxima over GEV distribution
    if (params.evt_approach == BM){

        dist = std::static_pointer_cast<chronovise::GEV_Distribution>(est_pwm.get_result());

    }else{

        dist = std::static_pointer_cast<chronovise::GPD_Distribution>(est_pwm.get_result());
    }

    if (params.evt_estimator == MLE) {
        chronovise::Estimator_MLE<int, T> est_mle;
        est_mle.set_source_evt_approach(&typeid(*evt_app));
        est_mle.set_initial_guess(dist->get_location(), dist->get_scale(), dist->get_shape());
        est_mle.run(new_mp);
        if (params.evt_approach == BM){
            dist = std::static_pointer_cast<chronovise::GEV_Distribution>(est_mle.get_result());
        }else{
            dist = std::static_pointer_cast<chronovise::GPD_Distribution>(est_mle.get_result());
        }
    }
    // GoF test on distribution
    // (i.e. if GoF test passed proceed to compute pWCET)

    std::shared_ptr<chronovise::StatisticalTest_AfterEVT<int,T>> gof;



    switch(params.gof){

        case KS:
            gof = std::make_shared<chronovise::TestKS<int,T>>(0.05,dist->get_type());

            break;
        case AD:
            gof = std::make_shared<chronovise::TestAD<int,T>>(0.05,dist->get_type(),false);

            break;
        case mod_AD:
            gof = std::make_shared<chronovise::TestAD<int,T>>(0.05,dist->get_type(),true);

            break;

    }




    std::shared_ptr<chronovise::pWCET<T>> pwcet = std::make_shared<chronovise::pWCET<T>>(dist);


    // save results
    results.mu = dist->get_location();
    results.sg = dist->get_scale();
    results.xi = dist->get_shape();
    results.type_dist = dist->get_type();
    results.dist = dist;
    results.pwcet = pwcet;
    results.gof = std::make_pair(gof->get_statistic(),gof->get_critical_value());



}



template<typename T>
void execute_iid_tests(const chronovise::MeasuresPool<int, T> &mp, t_computation_results<T> &results) {
    chronovise::TestKPSS<int, T> test_kpss(0.05, 0);
    chronovise::TestBDS <int, T> test_bds(0.05);
    chronovise::TestRS  <int, T> test_rs(0.05);

    test_kpss.run(mp);

    test_bds.run(mp);

    test_rs.run(mp);

    auto kpss_stats = test_kpss.get_statistic();
    auto kpss_cv    = test_kpss.get_critical_value();
    auto bds_stats  = test_bds.get_statistic();
    auto bds_cv     = test_bds.get_critical_value();
    auto rs_stats   = test_rs.get_statistic();
    auto rs_cv      = test_rs.get_critical_value();

    auto ppi_res = compute_ppi(kpss_stats, bds_stats, rs_stats, kpss_cv, bds_cv, rs_cv);


    results.ppi = ppi_res;
    results.test_1 = std::make_pair(kpss_stats,kpss_cv);
    results.test_2 = std::make_pair(bds_stats,bds_cv);
    results.test_3 = std::make_pair(rs_stats,rs_cv);

}



std::pair<double, double> compute_ppi(double stat_kpss, double stat_bds, double stat_rs, double cv_kpss, double cv_bds, double cv_rs) {

    const double factor = 4.;

    double m_st_kpss = std::exp(- stat_kpss / factor);
    double m_cv_kpss = std::exp(- cv_kpss / factor);


    double k_bds = -std::log(m_cv_kpss) / cv_bds;


    double m_st_bds = std::exp(-k_bds * stat_bds);
    double m_cv_bds = std::exp(-k_bds * cv_bds);


    double k_rs = -std::log(m_cv_kpss) / cv_rs;

    double m_st_rs = std::exp(-k_rs * stat_rs);
    double m_cv_rs = std::exp(-k_rs * cv_rs);

    assert(m_cv_kpss == m_cv_bds && m_cv_kpss == m_cv_rs);

    std::vector<double> violate_set;
    if(m_st_kpss < m_cv_kpss) violate_set.push_back(m_st_kpss);
    if(m_st_bds  < m_cv_bds ) violate_set.push_back(m_st_bds);
    if(m_st_rs   < m_cv_rs  ) violate_set.push_back(m_st_rs);


    double PPI;

    if (violate_set.size() > 0) {
        auto min_value_it = std::min_element(violate_set.begin(), violate_set.end());

        PPI = *min_value_it;

        for (auto it=violate_set.cbegin(); it != violate_set.cend(); it++) {
            if (it != min_value_it) {
                PPI *= (1-(m_cv_kpss - *it));
            }
        }

    } else {
        PPI = (m_st_kpss+m_st_bds+m_st_rs) / 3;
    }

    auto ppi_res = std::make_pair(PPI, m_cv_kpss);




    return ppi_res;

}


template<typename T>
void custom_test(const chronovise::MeasuresPool<int, T> &mp, t_custom_test type, double significance_level, std::pair<double, double> &output){


    switch(type){
        case KPSS:{
            chronovise::TestKPSS<int, T> test_kpss(significance_level, 0);
            test_kpss.run(mp);
            double kpss_stats = test_kpss.get_statistic();
            double kpss_cv    = test_kpss.get_critical_value();

            output =  std::make_pair(kpss_stats,kpss_cv);
         }
            break;
        case BDS:{
            chronovise::TestBDS <int, T> test_bds(significance_level);
            test_bds.run(mp);
            double bds_stats  = test_bds.get_statistic();
            double bds_cv     = test_bds.get_critical_value();

            output =  std::make_pair(bds_stats,bds_cv);
        }
            break;
        case RS:{
            chronovise::TestRS  <int, T> test_rs(significance_level);
            test_rs.run(mp);
            double rs_stats   = test_rs.get_statistic();
            double rs_cv      = test_rs.get_critical_value();

            output =  std::make_pair(rs_stats,rs_cv);
        }
        break;
        case end:{
            output =  std::make_pair(0,0);
        }
            break;



    }

}

// to solve linking error with template funtions
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl

template void custom_test<unsigned long>(const chronovise::MeasuresPool<int, unsigned long> &mp, t_custom_test type, double significance_level, std::pair<double, double> &output);
template void custom_test<double>(const chronovise::MeasuresPool<int, double> &mp, t_custom_test type, double significance_level, std::pair<double, double> &output);

template void execute_pwcet_estimation<unsigned long>(const chronovise::MeasuresPool<int, unsigned long> &mp, t_computation_param &params ,t_computation_results<unsigned long> &results);
template void execute_pwcet_estimation<double>(const chronovise::MeasuresPool<int, double> &mp, t_computation_param &params ,t_computation_results<double> &results);

template void execute_iid_tests<unsigned long>(const chronovise::MeasuresPool<int, unsigned long> &mp, t_computation_results<unsigned long> &results);
template void execute_iid_tests<double>(const chronovise::MeasuresPool<int, double> &mp, t_computation_results<double> &results);
