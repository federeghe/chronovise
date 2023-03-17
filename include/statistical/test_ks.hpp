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
 * @file test_ks.hpp
 * @author Check commit authors
 * @brief File containing the Kolmogorov-Smirnov test.
 */

#ifndef STATISTICAL_TEST_KS_HPP_
#define STATISTICAL_TEST_KS_HPP_

#include "test.hpp"
#include "distribution.hpp"
#include "../evt/gev_distribution.hpp"

#include <cmath>
#include <list>

#define TEST_KS_MIN_SAMPLES 20

namespace chronovise {

/**
 * The Kolmogorov-Smirnov goodnes-of-fit test class.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class TestKS : public StatisticalTest_AfterEVT<T_INPUT, T_TIME> {

public:

    /**
     * @copydoc StatisticalTest_AfterEVT::StatisticalTest_AfterEVT()
     * @note T_TIME must be an arithmetic type, otherwise a static_assert triggers.
     */
    TestKS(double significance_level, distribution_t distribution_type)
    : StatisticalTest_AfterEVT<T_INPUT,T_TIME>(significance_level, distribution_type)
    {
        static_assert(std::is_arithmetic<T_TIME>::value,
        "Type must be an integer or floating point type");
    };

    /**
     * @copydoc StatisticalTest::run()
     */
    virtual void run(const MeasuresPool<T_INPUT, T_TIME> &measures) override;

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
        return TEST_KS_MIN_SAMPLES;
    }

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size(unsigned short) const
     */
    virtual unsigned long get_minimal_sample_size(unsigned short req_power) const override;

private:
    double power;


};

} // namespace chronovise

#endif // STATISTICAL_TEST_KS_HPP_
