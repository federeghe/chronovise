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
 * @file test.hpp
 * @author Check commit authors
 * @brief File containing the StatisticalTest class and derived (still abstract) classes.
 */

#ifndef STATISTICAL_TEST_HPP_
#define STATISTICAL_TEST_HPP_

#include "statistical/distribution.hpp"
#include "measures_pool.hpp"

#include <memory>

namespace chronovise {

/**
 * The base abstract class for statistical tests.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class StatisticalTest {

public:
    /**
     * The base constructor. It required the significance level (alpha) to be
     * specified.
     * @param significance_level The significance level, e.g. 0.05.
     */
    StatisticalTest(double significance_level)
            : significance_level(significance_level) {

    }

    /**
     * Run the test.
     * @param measures The list of measures on which performs the test.
     * @throw std::invalid_argument if the number of samples is less than get_minimal_sample_size()
     */
    virtual void run(const MeasuresPool<T_INPUT, T_TIME> &measures) = 0;

    /**
     * Returns the statistical test power.
     * @return The value of statistical power. The value is in the range [0;1].
     * @note The returned value is not usually the computer power that does not provide any
     *     statistical information. The power is usually computed a priori from the
     *     significance_level provided
     * @throws std::runtime_error if has_power()==false (depending on implementation it may not throw
     *                and return garbage)
     */
    virtual double get_power() const = 0;

    /**
     * Returns true if the null hypotesis is rejected.
     * @return true if the null hypotesis is rejected
     * @note A false value does not mean that the hypothesis has been accepted.
     */
    bool is_reject() const noexcept {
        return this->reject;
    }

    /**
     * @brief Returns true if the test has power estimation routine. It can be called before the
     *      test
     */
    virtual bool has_power() const noexcept = 0;

    /**
     * @brief Returns true if the test performed a power estimation that can be considered
     *      "safe", i.e. the value obtained from get_power() is not overestimated. This method
     *      returns always false if has_power()==false.
     * @note  It must be called AFTER the test run.
     */
    virtual bool has_safe_power() const noexcept = 0;

    /**
     * @brief It returns the minimal sample size to run the test. If a lower a sample with lower
     *      size is provided to run() function, it will probably fail.
     * @note This value is always lower than get_minimal_sample_size(unsigned short req_power)
     *       regardless of the requested power.
     */
    virtual unsigned long get_minimal_sample_size() const noexcept = 0;

    /**
     * @brief It provides the minimal sample size to obtain a power of 1 with an accuracy
     *      10^(-req_power). The obtained value should be incremented by the caller with
     *      an appropriate engineering safety margin.
     * @note This value is always greater than get_minimal_sample_size().
     * @param req_power The accuracy expressed with 10^(-req_power). Tipical values are 3, 6, or 9
     * @throw std::logic_error if has_power() == false
     * @throw std::invalid_argument if the value of req_power is too high and not supported
     */
    virtual unsigned long get_minimal_sample_size(unsigned short req_power) const = 0;

    /**
     * Returns the significance level (alpha).
     * @return The significance level.
     */
    double get_significance_level() const noexcept {
        return this->significance_level;
    }


protected:
    const double significance_level;

    bool reject = false;
};

/**
 * The base abstract class for goodnes-of-fit tests.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class StatisticalTest_AfterEVT : public StatisticalTest<T_INPUT, T_TIME> {

public:

    /**
     * The constructor for goodness-of-fit tests. It requires the significance level to be
     * specified and the reference distribution type.
     * @param significance_level The significance level, e.g. 0.05.
     * @param distribution_type The type of the distribution to be used as a reference for
     *                          goodness-of-fit test.
     */
    StatisticalTest_AfterEVT(double significance_level, distribution_t distribution_type)
    : StatisticalTest<T_INPUT,T_TIME>(significance_level), distribution_type(distribution_type)
    {}

    /**
     * Set the reference (i.e. estimated) distribution to verify
     * @param distribution The EV distribution to verify. The value is internally
     *               copied
     */
    void set_ref_distribution(std::shared_ptr<Distribution> distribution) noexcept
    {
        this->ref_distribution = distribution;
    }

protected:
    std::shared_ptr<Distribution> ref_distribution;
    distribution_t distribution_type;
};

} // chronovise

#endif
