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
	const double mu = this->get_location();
	const double sg = this->get_scale();
	const double xi = this->get_shape();

	// Check the support limits
	if (xi >= 0. && x < mu)
		return 0.;
	if (xi < 0.  && (x < mu || x > mu - sg / xi))
		return 0.;

	const double norm_x = (x-mu)/sg;
	double cond_value = 1. + xi * norm_x;

	double cdf = 0.;

	if (cond_value >= 0. && xi != 0.) {
		cdf = 1 - std::pow(cond_value, - 1. / xi);
	}
	else if (x >= 0. && xi == 0.) {
		cdf = 1 - std::exp(-norm_x);
	}
	
	assert(cdf >= 0. && cdf <= 1. && "Something bad happened in calculation.");
	return cdf;
}

double GPD_Distribution::pdf(double x) const noexcept {
	const double mu = this->get_location();
	const double sg = this->get_scale();
	const double xi = this->get_shape();

	// Check the support limits
	if (xi >= 0. && x < mu)
		return 0.;
	if (xi < 0.  && (x < mu || x > mu - sg / xi))
		return 0.;

	const double norm_x = (x-mu)/sg;
	double cond_value = 1. + xi * norm_x;

	double pdf = 0.;

	if (cond_value >= 0. && xi != 0.) {
		pdf = 1. / sg * std::pow(cond_value, -1./xi - 1.);
	}
	else if (x >= 0. && xi == 0.) {
		pdf = 1. / sg * std::exp(-norm_x);
	}

	assert(pdf >= 0. && pdf <= 1. && "Something bad happened in calculation.");

	return pdf;
}

double GPD_Distribution::quantile(double p) const {

	const double mu = this->get_location();
	const double sg = this->get_scale();
	const double xi = this->get_shape();

	if (p <= 0. || p >= 1.) {
		throw std::invalid_argument("The probability value is not valid.");
	}

	double quantile;

	if (xi != 0.) {
		quantile = mu + sg  * (1. - std::pow(1. - p, -xi)) / (-xi);
	} else {
		quantile = mu - sg * std::log(1. - p);
	}

	return quantile;
}

} // namespace chronovise

