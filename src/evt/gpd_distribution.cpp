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
 * @file gpd_distribution.cpp
 * @author Check commit authors
 * @brief File containing the GPD_Distribution class
 */

#include "evt/gpd_distribution.hpp"

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace chronovise {


double GPD_Distribution::cdf(double x) const noexcept {
	// TODO

	return 0.;
}

double GPD_Distribution::pdf(double x) const noexcept {
	const double mu = this->get_location();
	const double sg = this->get_scale();
	const double xi = this->get_shape();


	double cond_value = 1. + xi * x / mu;

	double pdf = 0.;

	if (cond_value  >= 0. && xi != 0. && mu > 0.) {
		pdf = 1. / mu * cond_value;
	}

	if (x >= 0. && xi == 0. && mu > 0.) {
		pdf = 1. / mu * std::exp(-x / mu);
	}

	assert(pdf >= 0. && pdf <= 1. && "Something bad happened in calculation.");


	return pdf;
}

double GPD_Distribution::quantile(double p) const {

	if (p <= 0. || p >= 1.) {
		throw std::invalid_argument("The probability value is not valid.");
	}

	return 0.;
}

} // namespace chronovise

