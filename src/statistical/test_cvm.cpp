#include "statistical/test_cvm.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>
#include <limits>

namespace chronovise {

/** @private */
namespace local_test_cvm {
    static double get_cvm_critical_values(double alpha, long n) {

        const double lookup_table[][2] = {
            { 0.42480, 0.55058 },
            { 0.43939, 0.63980 },
            { 0.44206, 0.67017 },
            { 0.44697, 0.68352 },
            { 0.44911, 0.69443 },
            { 0.45100, 0.70154 },
            { 0.45240, 0.70720 },
            { 0.45340, 0.71150 },
            { 0.45420, 0.71470 },
            { 0.45778, 0.72895 },
            { 0.45986, 0.73728 },
            { 0.46091, 0.74149 },
            { 0.46119, 0.74262 },
            { 0.46136, 0.74346 }
        };


        const int lookup_table_labels[] = {
            2,3,4,5,6,7,8,9,10,20,50,200,1000,0
        };

        int a;

        if(alpha == 0.05) {
            a = 0;
        } else if (alpha == 0.01) {
            a = 1;
        } else {
            throw std::runtime_error("Critical Value not available for this alpha.");
        }

        long n_pos;
        for (n_pos = 0; n_pos < 13; n_pos++) {
            if (n <= lookup_table_labels[n_pos]) break;
        }

        if (n_pos == 13 || lookup_table_labels[n_pos] == n) {
            return  lookup_table[n_pos][a];
        }


        return ((double)n-lookup_table_labels[n_pos]) 
                / ((double)lookup_table_labels[n_pos-1]-lookup_table_labels[n_pos])
                * (lookup_table[n_pos-1][a] - lookup_table[n_pos][a])
                + (double)lookup_table[n_pos][a]; 

    }

    template <typename T_INPUT, typename T_TIME>
    static double empirical_F(const MeasuresPool<T_INPUT, T_TIME> &measures, double x) {
        const unsigned long n = measures.size();
        double curr_point = measures.min();

        unsigned long i=0;

        // TODO: Maybe we can cache these values to improve speed
        while(curr_point <= x) {
            i++;
            if (i >= n) break;
            curr_point = measures[i];
        } 

        double cumulative_F = ((double)i) / n;
        assert(cumulative_F >= 0. && cumulative_F <= 1.);
        return cumulative_F;
    }

}

template <typename T_INPUT, typename T_TIME>
void TestCvM<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    if(measures.size() < get_minimal_sample_size()) {
        throw std::invalid_argument("The number of samples is too low for this test.");
    }

    if(! this->ref_distribution) {
        throw std::invalid_argument("You must set a reference distribution for this test.");    
    }

    this->reject = false;

    using namespace local_test_cvm;

    const long n = measures.size();
    const double critical_value = get_cvm_critical_values(this->significance_level, n);

    double stat = 1. / (12. * n);

    /* **** Compute the empirical F(x) **** */

    for (int i=0; i<n; i++) {

        double F = this->ref_distribution->cdf(measures[i]);

        double term1 = (2. * i - 1.) / (2.*n);
        stat += (term1 - F) * (term1 - F);
    }

    if ( stat > critical_value) {
        this->reject = true;
    }

}

template <typename T_INPUT, typename T_TIME>
bool TestCvM<T_INPUT, T_TIME>::has_power() const noexcept
{
    return false;
}

template <typename T_INPUT, typename T_TIME>
bool TestCvM<T_INPUT, T_TIME>::has_safe_power() const noexcept
{
    return false;

}

template <typename T_INPUT, typename T_TIME>
unsigned long TestCvM<T_INPUT, T_TIME>::get_minimal_sample_size(unsigned short req_power) const {
    UNUSED(req_power);
    throw std::logic_error("Minimal sample size not available without power estimation routine.");

    return 0;
}

TEMPLATE_CLASS_IMPLEMENTATION(TestCvM);

} // namespace chronovise
