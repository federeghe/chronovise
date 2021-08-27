#include "statistical/test_bds.hpp"
#include "global.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>


#define BDS_DISTANCE 1.5


namespace chronovise {


template <typename T_INPUT, typename T_TIME>
uint_fast8_t TestBDS<T_INPUT, T_TIME>::indicator_function(unsigned long s, unsigned long t, unsigned long m, double epsilon) const noexcept {

    const size_t size = measures_save->size();

    assert(t >= m-1);
    assert(s >= m-1);
    assert(t <= size);
    assert(s <= size);

    auto iterator_a = std::next(measures_save->cbegin(), t - 1);
    auto iterator_b = std::next(measures_save->cbegin(), s - 1);

    for (unsigned long i=0; i<=m-1; i++) {
        T_TIME value_a = iterator_a->second;
        T_TIME value_b = iterator_b->second;

        if (value_a > value_b && ((value_a - value_b) >= epsilon)) {
            return 0;
        }
        if (value_b > value_a && ((value_b - value_a) >= epsilon)) {
            return 0;
        }
        
        iterator_a = std::prev(iterator_a);
        iterator_b = std::prev(iterator_b);
    }
    return 1;

}


template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::embedding_dimension(unsigned long m, double epsilon) const noexcept {

    const size_t size = measures_save->size();

    double coeff = 2./((size-m+1.)*(size - m));

    double sum = 0;

    for (unsigned long s = 1; s <= size; s++) {
        for (unsigned long t = s+1; t <= size; t++) {
            sum += indicator_function(s, t, m, epsilon);
        }
    }

    return coeff * sum;
}



template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::embedding_dimension_1(unsigned long m, double epsilon) const noexcept {

    const size_t size = measures_save->size();

    double coeff = 2./((size-m+1.)*(size - m));

    double sum = 0;

    for (unsigned long s = 1; s <= size; s++) {
        T_TIME value_b = std::next(measures_save->cbegin(), s - 1)->second;
        for (unsigned long t = s+1; t <= size; t++) {
            T_TIME value_a = std::next(measures_save->cbegin(), t - 1)->second;

            if (value_a > value_b && ((value_a - value_b) >= epsilon)) {
                continue;
            }
            if (value_b > value_a && ((value_b - value_a) >= epsilon)) {
                continue;
            }
            sum += 1;
        }
    }

    return coeff * sum;
}


template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::h_e(T_TIME a, T_TIME b, T_TIME c, double epsilon) const noexcept {

    double diff1 = a > b ? a - b : b - a;
    double diff2 = a > c ? a - c : c - a;
    double diff3 = c > b ? c - b : b - c;

    uint_fast8_t term1 = (diff1 < epsilon ? 1 : 0) * (diff3 < epsilon ? 1 : 0);
    uint_fast8_t term2 = (diff2 < epsilon ? 1 : 0) * (diff3 < epsilon ? 1 : 0);
    uint_fast8_t term3 = (diff1 < epsilon ? 1 : 0) * (diff2 < epsilon ? 1 : 0);

    return (term1 + term2 + term3) / 3.;

}

template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::k(double epsilon) const noexcept {

    const size_t size = measures_save->size();

    double coeff = 6. / ( size * (size-1) * (size-2) );

    double sum = 0.;

#if defined(_OPENMP)
    #pragma omp parallel for reduction(+:sum) firstprivate(measures_save, epsilon)
#endif
    for (size_t t=1; t <= size; t++) {
        auto t_value = std::next(measures_save->cbegin(),t-1)->second;
        auto s_iterator = std::next(measures_save->cbegin(),t);
        for (size_t s=t+1; s <= size; s++) {
            auto s_value = s_iterator->second;
            auto r_iterator = std::next(measures_save->cbegin(),s);
            for (size_t r=s+1; r <= size; r++) {
                sum += h_e(
                    t_value,
                    s_value,
                    r_iterator->second,
                    epsilon);
                r_iterator++;
            }
            s_iterator++;
        }
    }

    return coeff * sum;

}


template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::sigma(unsigned long m, double epsilon) const noexcept {

    double sum = 0.;
    double k = this->k(epsilon);
    double c = this->embedding_dimension(1, epsilon);

    sum += std::pow(k, m);

    double term2 = 0.;
    for (unsigned long j=1; j<=m-1; j++) {
        term2 += std::pow(k, m-j) * std::pow(c, 2 * j);
    }
    
    sum += 2. * term2;

    sum += (m-1)*(m-1)*std::pow(c, 2 * m);

    sum -= m*m*k*std::pow(c, 2 * m - 2);


    return 4 * sum;

}


template <typename T_INPUT, typename T_TIME>
void TestBDS<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    size_t size = measures.size();
    this->measures_save = &measures;

    if(size < get_minimal_sample_size()) {
        throw std::invalid_argument("The number of samples is too low for this test");
    }

    if(this->significance_level != 0.05) {
        throw std::invalid_argument("Not implemented");
    }

    auto epsilon = BDS_DISTANCE * std::sqrt(measures.var() * size / (size-1));

    double m = 2;


    auto sigma = std::sqrt(this->sigma(m, epsilon));
    if (sigma == 0) {
        this->reject = true;
        return;
    }

    this->statistic = std::abs(std::sqrt(size-m+1) * (this->embedding_dimension(m, epsilon) - std::pow(this->embedding_dimension_1(m, epsilon),m)) / sigma);

    this->critical_value = 1.96;


    if ( this->statistic > this->critical_value) {
        this->reject = true;
    } else {
        this->reject = false;
    }

}


TEMPLATE_CLASS_IMPLEMENTATION(TestBDS);

} // namespace chronovise
