#ifndef UTILITY_H

#define UTILITY_H



#include <set>
#include <chronovise/evt/pwcet.hpp>
#include "chronovise/measures_pool.hpp"

enum t_iid_test  {PPI, Custom};

// "end" enum is used for terminating iteration
enum t_custom_test  {KPSS,BDS,RS, end};
enum t_evt_approach {BM, PoT, CV };
enum t_evt_estimator {MLE, PWM };
enum t_gof_test {KS, AD, mod_AD};

// map custom test enum to string
static const char *custom_test_str[] =
        { "KPSS", "BDS", "RS" };



struct t_computation_param{

    t_iid_test iid_t;
    t_custom_test tests[3];
    t_evt_approach evt_approach;
    t_evt_estimator evt_estimator;
    t_gof_test gof;

};

template<typename D>
struct t_computation_results{


    double mu;
    double sg;
    double xi;
    double wcot;


    std::pair<double, double> ppi;

    std::pair<double, double> test_1;
    std::pair<double, double> test_2;
    std::pair<double, double> test_3;

    std::pair<double, double> gof;

    chronovise::distribution_t type_dist;
    std::shared_ptr<chronovise::Distribution> dist;

    std::shared_ptr<chronovise::pWCET<D>> pwcet;

} ;




template<typename T>
T search_threshold(const chronovise::MeasuresPool<int, T> &mp) {

    std::multiset<T> ordered_nums;

    for (const auto &m : mp) {
        ordered_nums.insert(m.second);
    }

    int size  = ordered_nums.size();
    auto split = ordered_nums.begin();
    std::advance(split, static_cast<int>(size * 0.8));
    return *split;

}


#endif // UTILITY_H

