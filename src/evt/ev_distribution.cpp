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

#include "evt/ev_distribution.hpp"

#include <cassert>
#include <cmath>

namespace chronovise {


double EV_Distribution::cdf(double x) const noexcept {
	const double mu = this->get_location();
	const double sg = this->get_scale();
	const double xi = this->get_shape();
	const double norm_x = ( x - mu ) / sg;

	double t_x;	// The value that will contain the t(wcet) value

	if (this->is_gumbell()) {
		t_x = std::exp( - norm_x);
	} else {
		double cond_value =  1. + xi * norm_x;
		if (cond_value < 0.) {
			// This is a problematic case, the F(x) is not defined in this range, because
			// we are in the far right or in the far left of the distribution.
			return xi > 0. ? 0. : 1.;
		}

		// t(x) calculation
		t_x = std::pow(cond_value,  - 1. / xi);
	}

	// 1-CDF calculation
	double cdf = std::exp(-t_x);

	assert(cdf >= 0. && cdf <= 1. && "Something bad happened in calculation.");

	return cdf;
}

} // namespace chronovise

