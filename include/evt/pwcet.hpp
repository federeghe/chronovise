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

#include "evt/ev_distribution.hpp"

namespace chronovise {

class pWCET {

public:

	/**
	 * The default constructor. It initializes the pWCET with the provided distribution. The
	 * class is immutable, the EV_Distribution cannot be changed.  
	 */
	explicit pWCET(const EV_Distribution &ev_d) noexcept
	: ev_d(ev_d)
	{
	}

	/**
	 * Returns the underlying distribution passed to the constructor.
	 */
	inline const EV_Distribution & get_ev_distribution() const noexcept {
		return this->ev_d;
	}

	/**
	 * Returns the Extreme-Value probability given the WCET value.
	 * @param wcet
	 * @return The probability in the range [0;1].
	 */
	double get_probability(double wcet) const;

	/**
	 * Returns the Extreme-Value WCET given the probability.
	 * @param probability The probability in the range (0;1). The caller must ensure that the
	 *        probability does not loose precision reaching exactly 1.
	 */
	double get_wcet(double probability) const;

	
private:

	const EV_Distribution ev_d;
};

} // namespace chronovise

#endif	// STATISTICAL_EV_DISTRIBUTION_HPP_
