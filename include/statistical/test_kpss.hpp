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
 * @file test_kpss.hpp
 * @author Check commit authors
 * @brief File containing the KPSS test.
 */

#ifndef STATISTICAL_TEST_KPSS_HPP_
#define STATISTICAL_TEST_KPSS_HPP_

#include "test.hpp"
#include "distribution.hpp"
#include "../evt/gev_distribution.hpp"
#include "../global.hpp"

#include <cmath>
#include <list>
#include <stdexcept>

#define TEST_KPSS_MIN_SAMPLES 10

namespace chronovise {

typedef enum class test_kpss_trend_e {
    LEVEL,
    TREND
} test_kpss_trend_t;

/**
 * The Kwiatkowski–Phillips–Schmidt–Shin test class.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class TestKPSS : public StatisticalTest<T_INPUT, T_TIME> {

public:

    /**
     * The TestKPSS constructor.
     * @param significance_level The significance level for the test (alpha)
     * @param n_lags The number of lags of the Ljung-Box test. In non-seasonal data
     *               it should be around the value of 10.
     */
    TestKPSS(double significance_level, unsigned int n_lags, test_kpss_trend_t trend_class = test_kpss_trend_t::LEVEL)
    : StatisticalTest<T_INPUT,T_TIME>(significance_level), n_lags(n_lags), trend_class(trend_class)
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
        return TEST_KPSS_MIN_SAMPLES;
    }

    /**
     * @copydoc StatisticalTest::get_minimal_sample_size(unsigned short) const
     */
    virtual unsigned long get_minimal_sample_size(unsigned short req_power) const override {
        UNUSED(req_power);
        throw std::runtime_error("No power available for this test");
    }

private:
    unsigned int n_lags;
    test_kpss_trend_t trend_class;

    double compute_statistics(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;
    double compute_cv_value(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;

    static const std::map<test_kpss_trend_t,std::map<float,std::map<int,std::vector<double>>>> coeff_kpss;

};



} // namespace chronovise

#endif // STATISTICAL_TEST_KPSS_HPP_

