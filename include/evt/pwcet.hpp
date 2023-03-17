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
 * @file pwcet.hpp
 * @author Check commit authors
 * @brief File containing the pWCET class
 */

#ifndef EVT_PWCET_HPP_
#define EVT_PWCET_HPP_

#include "gev_distribution.hpp"

#include <list>
#include <memory>
#include <stdexcept>

namespace chronovise {

/**
 * The class providing a pWCET estimation from a given distribution.
 */
template <typename T=double>
class pWCET {

public:

    /**
     * The default constructor. It initializes the pWCET with the provided distribution. The
     * class is immutable, the Distribution cannot be changed.
     * @throws std::invalid_argument if ref_distribution is `nullptr`.
     */
    explicit pWCET(std::shared_ptr<const Distribution> ref_distribution)
    : ref_dist(ref_distribution)
    {
        if (! ref_distribution) {
            throw std::invalid_argument("Reference distribution is null.");
        }
    }

    /**
     * Returns the underlying distribution passed to the constructor.
     */
    inline std::shared_ptr<const Distribution> & get_distribution() const noexcept {
        return this->ref_dist;
    }

    /**
     * Returns the Extreme-Value probability given the WCET value.
     * @param wcet
     * @return The probability in the range [0;1].
     */
    double get_probability(T wcet) const;

    /**
     * Returns the Extreme-Value WCET given the probability.
     * @param probability The probability in the range (0;1). The caller must ensure that the
     *        probability does not loose precision reaching exactly 1.
     */
    T get_wcet(double probability) const;

    /**
     * Returns the lowest probability among all the provided pWCETs given a particular WCET
     */
    static double get_cumulative_probability(const std::list<pWCET<T>> &pwcet_list, T wcet) noexcept;

    /**
     * Returns the highest WCET among all the provided pWCETs given a particular probability
     */
    static T get_cumulative_wcet(const std::list<pWCET<T>> &pwcet_list, double probability) noexcept;
    
private:

    mutable std::shared_ptr<const Distribution> ref_dist;
};

} // namespace chronovise

#endif    // EVT_PWCET_HPP_
