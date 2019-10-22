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

    for (unsigned long i=0; i<=m-1; i++) {
        T_TIME value_a = std::next(measures_save->cbegin(), t - i - 1)->second;
        T_TIME value_b = std::next(measures_save->cbegin(), s - i - 1)->second;

        if (value_a > value_b && ((value_a - value_b) >= epsilon)) {
            return 0;
        }
        if (value_b > value_a && ((value_b - value_a) >= epsilon)) {
            return 0;
        }
    }
    return 1;

}

template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::embedding_dimension(unsigned long m) const noexcept {

    const size_t size = measures_save->size();
    const auto epsilon = BDS_DISTANCE;

    double Tm = size - m + 1
    double coeff = 2./(size*(size - 1));

    double sum = 0;

    for (unsigned long s = 1; s <= size; s++) {
        for (unsigned long t = s+1; t <= size; t++) {
            sum += indicator_function(s, t, m, epsilon);
        }
    }

    return coeff * sum;
}


template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::h_e(T_TIME a, T_TIME b, T_TIME c, double epsilon) const noexcept {

    uint_fast8_t diff1 = a > b ? a - b : b - a;
    uint_fast8_t diff2 = a > c ? a - c : c - a;
    uint_fast8_t diff3 = c > b ? c - b : b - c;

    uint_fast8_t term1 = (diff1 < epsilon ? 1 : 0) * (diff3 < epsilon ? 1 : 0);
    uint_fast8_t term2 = (diff2 < epsilon ? 1 : 0) * (diff3 < epsilon ? 1 : 0);
    uint_fast8_t term3 = (diff1 < epsilon ? 1 : 0) * (diff2 < epsilon ? 1 : 0);

    return 1./3. * (term1 + term2 + term3);

}

template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::k(double epsilon) const noexcept {

    const size_t size = measures_save->size();

    double coeff = 6. / ( size * (size-1) * (size-2) );

    double sum = 0.;

    for (size_t t=1; t <= size; t++) {
        for (size_t s=t+1; s <= size; s++) {
            for (size_t r=s+1; r <= size; r++) {
                sum += h_e(
                    std::next(measures_save->cbegin(),t-1)->second,
                    std::next(measures_save->cbegin(),s-1)->second,
                    std::next(measures_save->cbegin(),r-1)->second,
                    epsilon);
            }
        }
    }

    return coeff * sum;

}


template <typename T_INPUT, typename T_TIME>
double TestBDS<T_INPUT, T_TIME>::sigma(unsigned long m, double epsilon) const noexcept {

    double sum = 0.;
    double k = this->k(epsilon);
    double c = this->embedding_dimension(1);

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


    auto epsilon = BDS_DISTANCE * measures.stdev();

    std::cout << "EPS = " << epsilon << std::endl;

    double m = 2;

    std::cout << "A = " << this->embedding_dimension(m) << std::endl;
    std::cout << "B = " << this->embedding_dimension(1) << std::endl;

    auto sigma = std::sqrt(this->sigma(m, epsilon));
    if (sigma == 0) {
        this->reject = true;
        return;
    }

    double statistics = std::abs(std::sqrt(size) * (this->embedding_dimension(m) - std::pow(this->embedding_dimension(1),m)) / sigma);

    double critical_value = 1.96;

    std::cout << "Statistics = " << statistics << " CV = " << critical_value << std::endl;

    if ( statistics > critical_value) {
        this->reject = true;
    } else {
        this->reject = false;
    }

}


TEMPLATE_CLASS_IMPLEMENTATION(TestBDS);

} // namespace chronovise
