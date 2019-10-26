#include "statistical/test_kpss.hpp"
#include "statistical/test_bds.hpp"
#include "statistical/test_rs.hpp"

#include <iomanip>
#include <iostream>
#include <string>

/**
 * Global variables (configuration)
 */
double significance_level = 0.05;
enum { INT, LONG, FLOAT, DOUBLE } datatype = INT;

/**
 * Prototypes
 */
void print_usage(void);
bool check_options(int argc, char*argv[]);
template<typename T> void run_and_print(void);
void compute_and_print_ppi(double stat_kpss, double stat_bds, double stat_rs, double cv_kpss, double cv_bds, double cv_rs);

/**
 * Main function
 */
int main(int argc, char*argv[]) {

    if (! check_options(argc, argv)) {
        print_usage();
        return 1;
    }

    std::cout << "chronovise - PPI calculator" << std::endl;
    std::cout << "---------------------------" << std::endl;

    switch(datatype) {
        case INT:
            run_and_print<unsigned long>(); // Not implemented int version, resume to long one
        break;
        case LONG:
            run_and_print<unsigned long>();
        break;
        case FLOAT:
            run_and_print<double>();    // Not implemented float version, resume to double one
        break;
        case DOUBLE:
            run_and_print<double>();
        break;
    }

    return 0;
}

/**
 * Helpers function
 */
void print_usage(void) {

    std::cout << "ppi [options]" << std::endl;
    std::cout << "  options:" << std::endl;
    std::cout << "  --alpha value [default: 0.05]" << std::endl;
    std::cout << "  --data_type (int|long|float|double) [default: int]" << std::endl;
}

bool check_options(int argc, char*argv[]) {
    if (argc != 1 && argc != 3 && argc != 5) {
        return false;
    }

    if (argc == 1) {
        return true;
    }

    for (int i = 1; i < argc; i += 2) {
        if (std::string(argv[i]) == "--alpha") {
            try {
                significance_level = std::stof(argv[i+1]);
            } catch(...) {
                return false;
            }
        }
        else if (std::string(argv[i]) == "--data_type") {
            std::string dtype(argv[i+1]);
            if (dtype == "int") {
                datatype = INT;
            } else if (dtype == "long") {
                datatype = LONG;
            } else if (dtype == "float") {
                datatype = FLOAT;
            } else if (dtype == "double") {
                datatype = DOUBLE;
            } else {
                return false;
            }

        } else {
            return false;
        }
    }

    return true;

}



template<typename T>
void run_and_print(void) {

    chronovise::MeasuresPool<int, T> mp;    // Input values not used here, we randomly put int.

    T value;

    while (std::cin >> value)
    {
       mp.push(0, value);
    }

    chronovise::TestKPSS<int, T> test_kpss(significance_level, 0);
    chronovise::TestBDS <int, T> test_bds(significance_level);
    chronovise::TestRS  <int, T> test_rs(significance_level);

    std::cout << "Total values: "   << mp.size() << std::endl;
    std::cout << "Basic statistics" << std::endl;
    std::cout << "---"              << std::endl;
    std::cout << "Min:           "  << mp.min() << std::endl;
    std::cout << "Max:           "  << mp.max() << std::endl;
    std::cout << "Mean:          "  << mp.avg() << std::endl;
    std::cout << "Variance:      "  << mp.var() << std::endl;
    std::cout << "Std Deviation: "  << mp.stdev() << std::endl;

    std::cout << "---"              << std::endl;

    std::cout << "KPSS test (stationarity)"  << std::endl;
    test_kpss.run(mp);
    std::cout << "Statistics:     " << test_kpss.get_statistic() << std::endl;
    std::cout << "Critical Value: " << test_kpss.get_critical_value() << std::endl;
    std::cout << "Result:         " << (test_kpss.is_reject() ? "REJECTED" : "PASSED") << std::endl;

    std::cout << "---"              << std::endl;

    std::cout << "BDS test (short-range dependence)"  << std::endl;
    test_bds.run(mp);
    std::cout << "Statistics:     " << test_bds.get_statistic() << std::endl;
    std::cout << "Critical Value: " << test_bds.get_critical_value() << std::endl;
    std::cout << "Result:         " << (test_bds.is_reject() ? "REJECTED" : "PASSED") << std::endl;

    std::cout << "---"              << std::endl;

    std::cout << "R/S test (long-range dependence)"  << std::endl;
    test_rs.run(mp);
    std::cout << "Statistics:     " << test_rs.get_statistic() << std::endl;
    std::cout << "Critical Value: " << test_rs.get_critical_value() << std::endl;
    std::cout << "Result:         " << (test_rs.is_reject() ? "REJECTED" : "PASSED") << std::endl;

    compute_and_print_ppi(test_kpss.get_statistic(), test_bds.get_statistic(), test_rs.get_statistic(), test_kpss.get_critical_value(), test_bds.get_critical_value(), test_rs.get_critical_value());

}

void compute_and_print_ppi(double stat_kpss, double stat_bds, double stat_rs, double cv_kpss, double cv_bds, double cv_rs) {

    std::cout << "---"              << std::endl;
    std::cout << "PPI Computation (NOTE: PPI statistics vs critical value has opposite meaning)"  << std::endl;

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

    double PPI;

    if (m_st_kpss < m_cv_kpss ||
        m_st_bds  < m_cv_bds  ||
        m_st_rs   < m_cv_rs) {

        if (m_st_kpss <= m_st_bds && m_st_kpss <= m_st_rs) {
            PPI = m_st_kpss * (1 - (m_cv_bds - m_st_bds)) * (1 - (m_cv_rs - m_st_rs));
        }
        if (m_st_bds <= m_st_kpss && m_st_bds <= m_st_rs) {
            PPI = m_st_bds  * (1 - (m_cv_kpss - m_st_kpss)) * (1 - (m_cv_rs - m_st_rs));
        }
        if (m_st_rs <= m_st_bds && m_st_rs <= m_st_kpss) {
            PPI = m_st_rs   * (1 - (m_cv_bds - m_st_bds)) * (1 - (m_cv_kpss - m_st_kpss));
        }

    } else {
        PPI = (m_st_kpss+m_st_bds+m_st_rs) / 3;
    }

    
    std::cout << "Statistics:     " << PPI << std::endl;
    std::cout << "Critical Value: " << m_cv_kpss << std::endl;
    std::cout << "Result:         " << (PPI < m_cv_kpss ? "REJECTED" : "PASSED") << std::endl;


}


