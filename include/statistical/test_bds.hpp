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
 * @file test_bds.hpp
 * @author Check commit authors
 * @brief File containing the BDS test.
 */

#ifndef STATISTICAL_TEST_BDS_HPP_
#define STATISTICAL_TEST_BDS_HPP_

#include "statistical/test.hpp"
#include "statistical/distribution.hpp"
#include "evt/gev_distribution.hpp"
#include "global.hpp"

#include <cmath>
#include <list>
#include <stdexcept>

#define TEST_BDS_MIN_SAMPLES 10

namespace chronovise {

/**
 * The Brock, Dechert, Scheinkman independence test class.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class TestBDS : public StatisticalTest<T_INPUT, T_TIME> {

public:

    /**
     * The TestBDS constructor.
     * @param significance_level The significance level for the test (alpha)
     */
    TestBDS(double significance_level)
    : StatisticalTest<T_INPUT,T_TIME>(significance_level)
    {
    }

    /**
     * @copydoc StatisticalTest::run()
     */
    virtual void run(const MeasuresPool<T_INPUT, T_TIME> &measures) override;

    /**
     * @copydoc StatisticalTest::get_power()
     */
     virtual double get_power() const override {
        throw std::runtime_error("No power available for this test");
    }

    /**
     * @copydoc StatisticalTest::has_power()
     */
     virtual bool has_power() const noexcept override {
        return false;
    }

    /**
     * @copydoc StatisticalTest::has_safe_power()
     */
     virtual bool has_safe_power() const noexcept override {
        return false;
    }

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size()
     */
    virtual unsigned long get_minimal_sample_size() const noexcept override {
        return TEST_BDS_MIN_SAMPLES;
    }

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size(unsigned short) const
     */
    virtual unsigned long get_minimal_sample_size(unsigned short req_power) const override {
        UNUSED(req_power);
        throw std::runtime_error("No power available for this test");
    }

private:
    uint_fast8_t indicator_function(unsigned long t, unsigned long s, unsigned long m, double epsilon) const noexcept;
    double embedding_dimension(unsigned long m, double epsilon) const noexcept;
    double embedding_dimension_1(unsigned long m, double epsilon) const noexcept;
    double sigma(unsigned long m, double epsilon) const noexcept;
    double k(double epsilon) const noexcept;
    double h_e(T_TIME a, T_TIME b, T_TIME c, double epsilon) const noexcept;

    const MeasuresPool<T_INPUT, T_TIME> *measures_save; // Don't worry about the pointer, it's an ugly but safe trick

};

} // namespace chronovise

#endif // STATISTICAL_TEST_BDS_HPP_

