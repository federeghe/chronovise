#include "statistical/test_rs.hpp"
#include "global.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>
#include <iostream>



namespace chronovise {

template <typename T_INPUT, typename T_TIME>
double TestRS<T_INPUT, T_TIME>::compute_statistics(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

    typedef std::pair<T_INPUT, T_TIME> P;

    size_t nobs   = measures.size();
    T_TIME avg    = measures.avg();
    T_TIME stdev  = measures.stdev();

    // Getting rid of input values
    std::vector<T_TIME> observ;
    observ.reserve(nobs);

    std::transform(measures.cbegin(), measures.cend(), std::back_inserter(observ), 
                   [avg](const P& p) { return p.second - avg; });


    std::vector<T_TIME> cumsum(nobs);
    std::partial_sum (observ.cbegin(), observ.cend(), cumsum.begin());


    double max_el = *std::max_element(cumsum.cbegin(), cumsum.cend());
    double min_el = *std::min_element(cumsum.cbegin(), cumsum.cend());
    double cumsum_diff = max_el - min_el;

    double v = (1. / std::sqrt(nobs)) * (cumsum_diff / stdev);


    return v;

} 

template <typename T_INPUT, typename T_TIME>
double TestRS<T_INPUT, T_TIME>::compute_cv_value(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

    (void)measures;

     // TODO
    return 1.747;

}

template <typename T_INPUT, typename T_TIME>
void TestRS<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    size_t size = measures.size();

    if(size < get_minimal_sample_size()) {
        throw std::invalid_argument("The number of samples is too low for this test");
    }

    if(this->significance_level != 0.05) {
        throw std::invalid_argument("Not implemented");
    }

    this->statistic = compute_statistics(measures);
    this->critical_value = compute_cv_value(measures);


    if ( this->statistic > this->critical_value) {
        this->reject = true;
    } else {
        this->reject = false;
    }

}

TEMPLATE_CLASS_IMPLEMENTATION(TestRS);

} // namespace chronovise
