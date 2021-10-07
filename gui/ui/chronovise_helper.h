#ifndef CHRONOVISE_HELPER_H
#define CHRONOVISE_HELPER_H

#include "utility.h"



template<typename T>
void execute_pwcet_estimation(const chronovise::MeasuresPool<int, T> &mp, t_computation_param &params ,t_computation_results<T> &results);


template<typename T>
void execute_iid_tests(const chronovise::MeasuresPool<int, T> &mp, t_computation_results<T> &results);


std::pair<double, double> compute_ppi(double stat_kpss, double stat_bds, double stat_rs, double cv_kpss, double cv_bds, double cv_rs);

template<typename T>
void custom_test(const chronovise::MeasuresPool<int, T> &mp, t_custom_test type, double significance_level, std::pair<double, double> &output);


#endif // CHRONOVISE_HELPER_H
