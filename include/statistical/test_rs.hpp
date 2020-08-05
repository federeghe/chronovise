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
 * @file test_rs.hpp
 * @author Check commit authors
 * @brief File containing the R/S test.
 */

#ifndef STATISTICAL_TEST_RS_HPP_
#define STATISTICAL_TEST_RS_HPP_

#include "statistical/test.hpp"
#include "statistical/distribution.hpp"
#include "global.hpp"

#include <cmath>
#include <list>
#include <stdexcept>

#define TEST_RS_MIN_SAMPLES 10

namespace chronovise {

/**
 * The Kwiatkowski–Phillips–Schmidt–Shin test class.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class TestRS : public StatisticalTest<T_INPUT, T_TIME> {

public:

    /**
     * The TestRS constructor.
     * @param significance_level The significance level for the test (alpha)
     * @param n_lags The number of lags of the Ljung-Box test. In non-seasonal data
     *               it should be around the value of 10.
     */
    TestRS(double significance_level)
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
        return TEST_RS_MIN_SAMPLES;
    }

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size(unsigned short) const
     */
    virtual unsigned long get_minimal_sample_size(unsigned short req_power) const override {
        UNUSED(req_power);
        throw std::runtime_error("No power available for this test");
    }

private:

    double compute_statistics(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;
    double compute_cv_value(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;


};



} // namespace chronovise

#endif // STATISTICAL_TEST_RSANA_HPP_

