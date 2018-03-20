/*
 *  chronovise - Copyright 2018 Politecnico di Milano
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file test_ad.hpp
 * @author Check commit authors
 * @brief File containing the Anderson-Darling test.
 */

#ifndef STATISTICAL_TEST_AD_HPP_
#define STATISTICAL_TEST_AD_HPP_

#include "statistical/test.hpp"
#include "statistical/distribution.hpp"

#include <cmath>
#include <list>

#define TEST_AD_MIN_SAMPLES 10

namespace chronovise {

/**
 * The Anderson-Darling goodnes-of-fit test class. This class can be
 * used for the Modified Anderson-Darling test also.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class TestAD : public StatisticalTest_AfterEVT<T_INPUT, T_TIME> {

public:

    /**
     * @copydoc StatisticalTest_AfterEVT::StatisticalTest_AfterEVT()
     * @note T_TIME must be an arithmetic type, otherwise a static_assert triggers.
     * @param MAD Request the Modified version of Anderson-Darling, i.e. the one
     *            considering the upper-bound only.
     * @param safe_margin A safe margin for the computed AD critical values. The
     *                    critical value is computed via a Monte Carlo simulation
     *                    thus a safety margin may increase reliability. A value of
     *                    1 will double the critical value (!).
     * @throw std::runtime_error if safety_margin < 0. 
     */
    TestAD(double significance_level, distribution_t distribution_type, bool MAD, double safe_margin)
    : StatisticalTest_AfterEVT<T_INPUT,T_TIME>(significance_level, distribution_type),
    MAD(MAD), safe_margin(safe_margin)
    {
        static_assert(std::is_arithmetic<T_TIME>::value,
        "Type must be an integer or floating point type");
        if (safe_margin < 0) {
            throw std::invalid_argument("Safety margin cannot be negative.");
        }
    };

    /**
     * @copydoc StatisticalTest::run()
     */
    virtual void run(const MeasuresPool<T_INPUT, T_TIME> &measures);

    /**
     * @copydoc StatisticalTest::get_power()
     */
     virtual double get_power() const override {
        return this->power;
    }

    /**
     * @copydoc StatisticalTest::has_power()
     */
     virtual bool has_power() const noexcept override;

    /**
     * @copydoc StatisticalTest::has_safe_power()
     */
     virtual bool has_safe_power() const noexcept override;

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size()
     */
    virtual unsigned long get_minimal_sample_size() const noexcept override {
        return TEST_AD_MIN_SAMPLES;
    }

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size(unsigned short) const
     */
    virtual unsigned long get_minimal_sample_size(unsigned short req_power) const override;

private:
    bool MAD;
    double power;
    double safe_margin;
};

} // namespace chronovise

#endif // STATISTICAL_TEST_AD_HPP_
