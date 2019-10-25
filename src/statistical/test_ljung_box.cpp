#include "statistical/test_ljung_box.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

#define GCEM_INCML_GAMMA_INV_MAX_ITER 35
#define GCEM_INCML_GAMMA_MAX_ITER 55

namespace chronovise {

/** @private */
namespace local_test_ljung_box {

    // lgamma

    /*################################################################################
      ##
      ##   Copyright (C) 2016-2018 Keith O'Hara
      ##
      ##   This file is part of the GCE-Math C++ library.
      ##
      ##   GCE-Math is free software: you can redistribute it and/or modify
      ##   it under the terms of the GNU General Public License as published by
      ##   the Free Software Foundation, either version 2 of the License, or
      ##   (at your option) any later version.
      ##
      ##   GCE-Math is distributed in the hope that it will be useful,
      ##   but WITHOUT ANY WARRANTY; without even the implied warranty of
      ##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      ##   GNU General Public License for more details.
      ##
      ################################################################################*/

    using namespace std;

    constexpr
    bool
    is_odd(const int x)
    {
        return ( x % 2 == 0 ? false : true );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_cf_coef(const T a, const T z, const int depth)
    {
        return ( is_odd(depth) ? - (a - 1 + T(depth+1)/T(2.0)) * z : T(depth)/T(2.0) * z );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_cf_int(const T a, const T z, const int depth)
    {
        return ( depth < GCEM_INCML_GAMMA_MAX_ITER ? (a + depth - 1) + incomplete_gamma_cf_coef(a,z,depth)/incomplete_gamma_cf_int(a,z,depth+1) :
                                                 (a + depth - 1) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_int(const T a, const T z)
    { // lower (regularized) incomplete gamma function
        return ( exp(a*log(z) - z) / tgamma(a) / incomplete_gamma_cf_int(a,z,1) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma(const T a, const T z)
    {
        return ( std::numeric_limits<T>::epsilon() > z ? T(0.0) : 
             std::numeric_limits<T>::epsilon() > a ? T(1.0) : 
             //
             z <= T(0.0) ? T(0.0) : incomplete_gamma_int(a,z) );
    }

    // #define GCEM_INCML_GAMMA_INV_TOL 1e-08

    template<typename T>
    constexpr T incomplete_gamma_inv_decision(const T value, const T a, const T p, const T direc, const T lg_val, const int iter_count);

    //
    // initial value for Halley

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_t_val_1(const T p)
    { // a > 1.0
        return ( p > T(0.5) ? sqrt(-2*log(T(1.0) - p)) : sqrt(-2*log(p)) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_t_val_2(const T a)
    { // a <= 1.0
        return ( T(1.0) - T(0.253) * a - T(0.12) * a*a );
    }

    //

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_initial_val_1_int_begin(const T t_val)
    { // internal for a > 1.0
        return ( t_val - (T(2.515517L) + T(0.802853L)*t_val + T(0.010328L)*t_val*t_val)/(T(1.0) + T(1.432788L)*t_val + T(0.189269L)*t_val*t_val + T(0.001308L)*t_val*t_val*t_val) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_initial_val_1_int_end(const T value_inp, const T a)
    { // internal for a > 1.0
        return max( T(1E-04), a*pow(T(1.0) - T(1.0)/(9*a) - value_inp/(3*sqrt(a)), 3) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_initial_val_1(const T a, const T p, const T t_val)
    { // a > 1.0
        return ( p > T(0.5) ? incomplete_gamma_inv_initial_val_1_int_end(-incomplete_gamma_inv_initial_val_1_int_begin(t_val), a) :
                          incomplete_gamma_inv_initial_val_1_int_end(incomplete_gamma_inv_initial_val_1_int_begin(t_val), a) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_initial_val_2(const T a, const T p, const T t_val)
    { // a <= 1.0
        return ( p < t_val ? pow(p/t_val,T(1.0)/a) : T(1.0) - log(T(1.0) - (p - t_val)/(T(1.0) - t_val)) );
    }

    // initial value

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_initial_val(const T a, const T p)
    {
        return ( a > T(1.0) ? incomplete_gamma_inv_initial_val_1(a,p,incomplete_gamma_inv_t_val_1(p)) :
                          incomplete_gamma_inv_initial_val_2(a,p,incomplete_gamma_inv_t_val_2(a)) );
    }

    //
    // Halley recursion

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_err_val(const T value, const T a, const T p)
    { // err_val = f(x)
        return ( incomplete_gamma(a,value) - p );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_deriv_1(const T value, const T a, const T lg_val)
    { // derivative of the incomplete gamma function w.r.t. x
        return ( exp( - value + (a - T(1.0))*log(value) - lg_val ) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_deriv_2(const T value, const T a, const T deriv_1)
    { // second derivative of the incomplete gamma function w.r.t. x
        return ( deriv_1*((a - T(1.0))/value - T(1.0)) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_ratio_val_1(const T value, const T a, const T p, const T deriv_1)
    {
        return ( incomplete_gamma_inv_err_val(value,a,p) / deriv_1 );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_ratio_val_2(const T value, const T a, const T p, const T deriv_1)
    {
        UNUSED(p);
        return ( incomplete_gamma_inv_deriv_2(value,a,deriv_1) / deriv_1 );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_halley(const T ratio_val_1, const T ratio_val_2)
    {
        return ( ratio_val_1 / max( T(0.8), min( T(1.2), T(1.0) - T(0.5)*ratio_val_1*ratio_val_2 ) ) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_recur(const T value, const T a, const T p, const T deriv_1, const T lg_val, const int iter_count)
    {
        return ( incomplete_gamma_inv_decision( value, a, p, incomplete_gamma_inv_halley(incomplete_gamma_inv_ratio_val_1(value,a,p,deriv_1), 
                                                         incomplete_gamma_inv_ratio_val_2(value,a,p,deriv_1)), lg_val, iter_count ) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_decision(const T value, const T a, const T p, const T direc, const T lg_val, const int iter_count)
    {
        // return ( abs(direc) > GCEM_INCML_GAMMA_INV_TOL ? incomplete_gamma_inv_recur(value - direc, a, p, incomplete_gamma_inv_deriv_1(value,a,lg_val), lg_val) : value - direc );
        return ( iter_count <= GCEM_INCML_GAMMA_INV_MAX_ITER ? incomplete_gamma_inv_recur(value-direc,a,p, incomplete_gamma_inv_deriv_1(value,a,lg_val), lg_val, iter_count+1) : 
                                                           value - direc );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv_int(const T initial_val, const T a, const T p, const T lg_val)
    {
        return ( incomplete_gamma_inv_recur(initial_val,a,p,incomplete_gamma_inv_deriv_1(initial_val,a,lg_val),lg_val,1) );
    }

    template<typename T>
    constexpr
    T
    incomplete_gamma_inv(const T a, const T p)
    {
        return ( incomplete_gamma_inv_int(incomplete_gamma_inv_initial_val(a,p),a,p,lgamma(a)) );
    }

    static inline double qchisq_int(double p, double dof_par)
    {
        return ( 2*incomplete_gamma_inv(dof_par/2.0,p));
    }    

}

template <typename T_INPUT, typename T_TIME>
void TestLjungBox<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    size_t size = measures.size();

    if(size < get_minimal_sample_size()) {
        throw std::invalid_argument("The number of samples is too low for this test");
    }

    if(size <= n_lags) {
        throw std::invalid_argument("The number of samples is too low for this n_lags value");
    }


    // Compute the test statistic
    double Q = 0;


    double mean = measures.avg();

    std::vector<T_TIME> timing;
    timing.reserve(size);
    for (const auto &x : measures) {
        timing.push_back(x.second);
    }
 

    for(size_t i=1; i <= n_lags; i++) {
        double rho = sample_autocorrelation(mean, size, timing, i);
        Q += rho * rho / (size - i);
    }

    Q *= size * (size + 2);

    if(!std::isfinite(Q)) {
        this->reject = true;
        return;
    }

    this->critical_value = local_test_ljung_box::qchisq_int(1. - this->significance_level, n_lags);

    this->statistic = Q;

    if ( Q > this->critical_value) {
        this->reject = true;
    } else {
        this->reject = false;
    }

}

template <typename T_INPUT, typename T_TIME>
double TestLjungBox<T_INPUT, T_TIME>::sample_autocorrelation(double mean, size_t size, const std::vector<T_TIME> &values, int h) noexcept {

    auto autocovariance_f = [size, mean, &values](int h) {
        double autocovariance=0;
        for (size_t i=0; i < size - h; i++) {
            autocovariance += (values[i+h] - mean) * (values[i] - mean);
        }
        autocovariance /= size;
        return autocovariance;
    };

    return autocovariance_f(h) / autocovariance_f(0);

}

TEMPLATE_CLASS_IMPLEMENTATION(TestLjungBox);

} // namespace chronovise
