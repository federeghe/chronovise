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
 * @file distribution_uniform.hpp
 * @author Check commit authors
 * @brief File containing the DistributionUniform class
 */

#ifndef STATISTICAL_DISTRIBUTION_UNIFORM_HPP_
#define STATISTICAL_DISTRIBUTION_UNIFORM_HPP_

#include <utility>

namespace chronovise {


/**
 * A uniform distribution class.
 */
class DistributionUniform : public Distribution {

public:
    
    DistributionUniform(double a, double b) : a(a), b(b)
    {}

    virtual ~DistributionUniform() noexcept { }

    /**
     * @copydoc Distribution::get_type()
     */
    virtual distribution_t get_type() const noexcept {
        return distribution_t::UNIFORM;
    }

    /**
     * @copydoc Distribution::cdf
     */
    virtual double cdf(double x) const noexcept {
        if (x < a) return 0;
        if (x > b) return 1;
        return (x-a)/(b-a);
    }
    
    /**
     * @copydoc Distribution::pdf
     */
    virtual double pdf(double x) const noexcept {
        if (x < a || x > b) return 0;
        return 1. / (b - a);
    }

    /**
     * @copydoc Distribution::quantile
     */
    virtual double quantile(double p) const {
        if (p <= 0. || p >= 1.) {
            throw std::invalid_argument("The probability value is not valid.");
        }

        return a + p * (b-a);
    }

    std::pair<double, double> get_parameters() const noexcept {
        return std::make_pair(a, b);
    }

private:
    double a;
    double b;

};

} // namespace chronovise

#endif    // STATISTICAL_DISTRIBUTION_UNIFORM_HPP_
