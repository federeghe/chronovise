#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "helpers.hpp"

#include "measures_pool.hpp"
#include "evt/evtapproach_pot.hpp"
#include "evt/evtapproach_bm.hpp"
#include "evt/gpd_distribution.hpp"
#include "evt/pwcet.hpp"
#include "statistical/estimator_pwm.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/test_kpss.hpp"
#include "statistical/test_bds.hpp"
#include "statistical/test_rs.hpp"

bool csv_output = false;
bool use_double = false;
bool use_pot = false;
std::ifstream input_file;
std::istream *input_s = nullptr;

bool parse_parameters(int argc, const char *argv[]) {


    std::vector<std::string> arguments;
    input_s = &std::cin;
    
    for (int i=1; i<argc; i++) {
        std::string curr_arg(argv[i]);
        
        if (curr_arg == "--csv-output") {
            csv_output = true;
        } else if (curr_arg == "--use-double") {
            use_double = true;
        } else if (curr_arg == "--use-pot") {
            use_pot = true;
        } else if (input_s == &std::cin) {
            input_file.open(argv[i]);
            input_s = &input_file;
        } else {
            return true;    // Error
        }
    }

    return false;
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

    return std::make_pair(PPI, m_cv_kpss);

}

template<typename T>
void execute_iid_tests(const chronovise::MeasuresPool<int, T> &mp) {
    chronovise::TestKPSS<int, T> test_kpss(0.05, 0);
    chronovise::TestBDS <int, T> test_bds(0.05);
    chronovise::TestRS  <int, T> test_rs(0.05);
    
    if (! csv_output) { std:: cout << "Running KPSS..." << std::endl; }
    test_kpss.run(mp);
    if (! csv_output) { std:: cout << "Running BDS..." << std::endl; }
    test_bds.run(mp);
    if (! csv_output) { std:: cout << "Running R/S..." << std::endl; }
    test_rs.run(mp);
    
    auto kpss_stats = test_kpss.get_statistic();
    auto kpss_cv    = test_kpss.get_critical_value();
    auto bds_stats  = test_bds.get_statistic();
    auto bds_cv     = test_bds.get_critical_value();
    auto rs_stats   = test_rs.get_statistic();
    auto rs_cv      = test_rs.get_critical_value();
    
    auto pair_output = compute_ppi(kpss_stats, bds_stats, rs_stats, kpss_cv, bds_cv, rs_cv);

    if (csv_output) {
        std::cout << mp.size() << ',' 
                  << kpss_stats << ','
                  << kpss_cv << ','
                  << bds_stats << ','
                  << bds_cv << ','
                  << rs_stats << ','
                  << rs_cv << ','
                  << pair_output.first << ','
                  << pair_output.first << ','
                  << (pair_output.first < pair_output.second ? "R" : "P");
    } else {
        std::cout << "Number of samples:\t" << mp.size() << std::endl;
        std::cout << "KPSS test result:\t"  << kpss_stats << " > " << kpss_cv << "? " << ( kpss_stats > kpss_cv ? "\tREJECT" : "\tPASS" ) << std::endl;
        std::cout << "BDS  test result:\t"  << bds_stats << " > "  << bds_cv << "? " <<  ( bds_stats  > bds_cv ? "\tREJECT" : "\tPASS" ) << std::endl;
        std::cout << "R/S  test result:\t"  << rs_stats << " > "   << rs_cv << "? " <<   ( rs_stats   > rs_cv ? "\tREJECT" : "\tPASS" ) << std::endl;

        std::cout << "PPI  test result:\t"  << pair_output.first << " < "   << pair_output.second << "? " <<   ( pair_output.first   < pair_output.second ? "REJECT" : "PASS" ) << std::endl;
    }
}

template<typename T>
void execute_pwcet_estimation(const chronovise::MeasuresPool<int, T> &mp) {

    std::unique_ptr<chronovise::EVTApproach<int, T>> evt_app;
    
    if (use_pot) {
        T threshold = search_threshold(mp);

        if (! csv_output) { std::cout << "PoT threshold: " << threshold << std::endl; }

        evt_app = std::unique_ptr<chronovise::EVTApproach<int, T>>(new chronovise::EVTApproach_PoT<int, T>(threshold));
     
        if (! csv_output) { std:: cout << "Applying PoT..." << std::endl; }
    } else {
        evt_app = std::unique_ptr<chronovise::EVTApproach<int, T>>(new chronovise::EVTApproach_BM<int, T>(20));
        if (! csv_output) { std:: cout << "Applying BM..." << std::endl; }
    }        
    
    
    chronovise::MeasuresPoolSet<int, T> mps(mp, 0.8, 0.2);
     
    evt_app->perform(mps);

    const auto &new_mp = evt_app->get_training_pool();

    chronovise::Estimator_PWM<int, T> est_pwm;
    chronovise::Estimator_MLE<int, T> est_mle;

    est_pwm.set_source_evt_approach(&typeid(*evt_app));
    est_mle.set_source_evt_approach(&typeid(*evt_app));

    if (! csv_output) { std:: cout << "Executing PWM estimator..." << std::endl; }
    est_pwm.run(new_mp);
    auto dist = std::static_pointer_cast<chronovise::GPD_Distribution>(est_pwm.get_result());
    
    if (!use_pot) {
        if (! csv_output) { std:: cout << "Executing MLE estimator..." << std::endl; }
        est_mle.set_initial_guess(dist->get_location(), dist->get_scale(), dist->get_shape());
        est_mle.run(new_mp);
        
        dist = std::static_pointer_cast<chronovise::GPD_Distribution>(est_mle.get_result());
    }
    
    auto pwcet = chronovise::pWCET<T>(dist);
    
    if (! csv_output) {
        std::cout << std::endl;
        std::cout << "Estimated distribution" << std::endl;
        std::cout << "----------------------" << std::endl;
        std::cout << "Location (\\mu): " << dist->get_location() << std::endl;
        std::cout << "Scale (\\sg):    " << dist->get_scale() << std::endl;
        std::cout << "Shape (\\xi):    " << dist->get_shape() << std::endl;
        std::cout << std::endl;
        std::cout << "WCOT:          " << mp.max() << std::endl;
        std::cout << "WCET @ 10^-9:  " << pwcet.get_wcet(1-1e-9) << std::endl;
    }


}

template<typename T>
void analyze_integer() {
    chronovise::MeasuresPool<int, T> mp;    // Input values not used here, we randomly put int.

    T value;

    while (*input_s >> value)
    {
        mp.push(0, value);
    }
    
    if (mp.size() < 20) {
        std::cerr << "The sample size is too low." << std::endl;
        return;
    }
    
    execute_iid_tests(mp);
    execute_pwcet_estimation(mp);

}

int main(int argc, const char *argv[]) {

    if (parse_parameters(argc, argv)) {
        std::cerr << "Usage: chronovise-app [--csv-output] [--use-double] [--use-pot] [input_file]" << std::endl;
        std::cerr << "If input_file is not specified, it reads from stdin." << std::endl;
        std::cerr << "Options:" << std::endl;
        std::cerr << " --csv-output: output in a CSV format" << std::endl;
        std::cerr << " --use-double: input is in double floating point precision and not in integer" << std::endl;
        std::cerr << " --use-pot:    Use the Peak-over-Threshold method instead of Block-Maxima" << std::endl;
        return -1;
    }

    if (!input_s->good()) {
        std::cerr << "** ERROR **: Unable to open input stream." << std::endl;
        return 1;
    }
    
    if (use_double) {
        analyze_integer<double>();    
    } else {
        analyze_integer<unsigned long>();
    }
    return 0;
}
