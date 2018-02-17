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
 * @file ev_distribution.hpp
 * @author Check commit authors
 * @brief File containing the EV_Distribution class
 */

#ifndef EVT_EV_DISTRIBUTION_HPP_
#define EVT_EV_DISTRIBUTION_HPP_

namespace chronovise {

/**
 * The class used to represent Extreme-Value distribution. This is an immutable-class: you cannot
 * modified it after initialization with exception of operator=.
 * @note The shape parameter may have different conventions depending on considered sign. In this
 *	 software, the convention is the following one:
 *	 - < 0: Weibull distribution
 *	 - = 0: Gumbell distribution
 *	 - > 0: Frechet distribution 
 */
class EV_Distribution {

public:

	/**
	 * The default constructor. It initializes an Extreme-Value
	 * distribution with location=0, scale=1, shape=0.
	 */
	explicit EV_Distribution() noexcept
	: param_location(0), param_scale(1), param_shape(0)
	{
	}

	/**
	 * The full specification constructor. It initializes an Extreme-Value
	 * distribution with the provided values.
	 * @param location The location parameter (\mu)
	 * @param scale    The scale parameter (\sigma)
	 * @param shape    The shape parameter (\xi)
	 * @warning Pay attention to convention on the sign of shape parameter.
	 *          Read the class description.
	 */
	explicit EV_Distribution(double location, double scale, double shape) noexcept
	:  param_location(location), param_scale(scale), param_shape(shape)
	{		
	}

	/**
	 * Getter for the location parameter
	 * @return The location parameter
	 */
	double get_location() const noexcept {
		return this->param_location;
	}

	/**
	 * Getter for the scale parameter
	 * @return The scale parameter
	 */
	double get_scale() const noexcept {
		return this->param_scale;
	}

	/**
	 * Getter for the shape parameter
	 * @return The shape parameter
	 * @warning Pay attention to convention on the sign of shape parameter.
	 *          Read the class description.
	 */
	double get_shape() const noexcept {
		return this->param_shape;
	}

	/**
	 * Check if the distribution is Gumbell or not
	 * @return true if shape == 0.0
	 */
	bool is_gumbell() const noexcept {
		return this->param_shape == 0.0;	// TODO maybe less strict
	}

	/**
	 * Check if the distribution is Weibull or not
	 * @return true if shape < 0.0
	 */
	bool is_weibull() const noexcept {
		return this->param_shape < 0.0;
	}

	/**
	 * Check if the distribution is Frechet or not
	 * @return true if shape > 0.0
	 */
	bool is_frechet() const noexcept {
		return this->param_shape > 0.0;
	}

	/**
	 * Returns the cumulative distribution function of the distribution
	 * @return F(x) : x is the passed parameter
	 */
	double cdf(double x) const noexcept;
	
	/**
	 * Returns the probability distribution function of the distribution
	 * @return f(x) : x is the passed parameter
	 */
	double pdf(double x) const noexcept;

	/**
	 * Returns the p-quantile of the distribution
	 * @return x : p=F(x)
	 */
	double quantile(double p) const;

private:
	double param_location;
	double param_scale;
	double param_shape;

};

} // namespace chronovise

#endif	// EVT_EV_DISTRIBUTION_HPP_
