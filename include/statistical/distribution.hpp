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
 * @file distribution.hpp
 * @author Check commit authors
 * @brief File containing the Distribution class
 */

#ifndef STATISTICAL_DISTRIBUTION_HPP_
#define STATISTICAL_DISTRIBUTION_HPP_

namespace chronovise {

/**
 * The list of available distributions in the framework. You should add the new distributions here
 * and accordingly implement the Test*
 */
typedef enum class distribution_e {
    UNKNOWN,
    EVT_GEV,
    EVT_GPD,
    UNIFORM
} distribution_t;


/**
 * The abstract class used to represent a generic distribution.
 */
class Distribution {

public:

    /**
     * A default virtual destructor for inheritance
     */
    virtual ~Distribution() noexcept = default;

    /**
     * Returns the type of the distribution
     */
    virtual distribution_t get_type() const noexcept = 0;

    /**
     * Returns the cumulative distribution function of the distribution
     * @return F(x) : x is the passed parameter
     */
    virtual double cdf(double x) const noexcept = 0;
    
    /**
     * Returns the probability density function of the distribution
     * @return f(x) : x is the passed parameter
     */
    virtual double pdf(double x) const noexcept = 0;

    /**
     * Returns the p-quantile of the distribution
     * @param p The probability in the range (0;1) extremes not included
     * @throw std::invalid_argument if p is not a valid probability.
     * @return x : p=F(x)
     */
    virtual double quantile(double p) const = 0;


};

} // namespace chronovise

#endif    // STATISTICAL_DISTRIBUTION_HPP_
