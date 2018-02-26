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

#include "evt/pwcet.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>

namespace chronovise {

template <typename T>
double pWCET<T>::get_probability(T wcet) const {

	assert(wcet > 0. && "WCET must be positive");

	double cdf = this->evd.cdf(wcet);

	return 1. - cdf;
}

template <typename T>
T pWCET<T>::get_wcet(double probability) const {
	assert(probability > 0. && probability < 1. && "Probability must have a valid value");

	double wcet = this->evd.quantile(probability);

	assert(wcet > 0. && "Something bad happened in calculation.");
	return wcet;

}

template <typename T>
static double get_cumulative_probability(const std::list<pWCET<T>> &pwcet_list, T wcet) noexcept {

	double minimum = 1.;
	for (const auto& pwcet : pwcet_list) {
		double prob = pwcet.get_probability(wcet);
		minimum = prob < minimum ? prob : minimum;
	}
	return minimum;
}

template <typename T>
static T get_cumulative_wcet(const std::list<pWCET<T>> &pwcet_list, double probability) noexcept {

	T maximum = 0;
	for (const auto& pwcet : pwcet_list) {
		T prob = pwcet.get_wcet(probability);
		maximum = prob > maximum ? prob : maximum;
	}
	return maximum;
}

TEMPLATE_CLASS_IMPLEMENTATION_T(pWCET);

} // namespace chronovise

