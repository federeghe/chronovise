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
 * @file test_ks.hpp
 * @author Check commit authors
 * @brief File containing the Kolmogorov-Smirnov test.
 */

#include "statistical/test.hpp"
#include "statistical/distribution.hpp"
#include "evt/ev_distribution.hpp"
#include "global.hpp"

#include <cmath>
#include <list>

#define TEST_LJUNG_BOX_MIN_SAMPLES 10

namespace chronovise {

/**
 * The Kolmogorov-Smirnov goodnes-of-fit test class.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class TestLjungBox : public StatisticalTest<T_INPUT, T_TIME> {

public:

	/**
	 * @copydoc StatisticalTest_AfterEVT::StatisticalTest_AfterEVT()
	 * @throw std::runtime_error("")
	 */
	TestLjungBox(double significance_level, unsigned int n_lags)
	: StatisticalTest<T_INPUT,T_TIME>(significance_level), n_lags(n_lags)
	{
	};

	/**
	 * @copydoc StatisticalTest::run()
	 */
	virtual void run(const MeasuresPool<T_INPUT, T_TIME> &measures);

	/**
	 * @copydoc StatisticalTest::get_power()
	 */
 	virtual double get_power() const override {
		throw std::runtime_error("No power available for this test");
	}

	/**
	 * @copydoc StatisticalTest::has_power()
	 */
 	virtual bool has_power() const noexcept override {
		return false;
	}

	/**
	 * @copydoc StatisticalTest::has_safe_power()
	 */
 	virtual bool has_safe_power() const noexcept override {
		return false;
	}

	/**
	 * @copydoc StatisticalTest::get_minimal_sample_size()
	 */
	virtual unsigned long get_minimal_sample_size() const noexcept override {
		return TEST_LJUNG_BOX_MIN_SAMPLES;
	}

	/**
	 * @copydoc StatisticalTest::get_minimal_sample_size(unsigned short) const
	 */
	virtual unsigned long get_minimal_sample_size(unsigned short req_power) const override {
		UNUSED(req_power);
		throw std::runtime_error("No power available for this test");
	}

private:
	unsigned int n_lags;

	double sample_autocorrelation(const MeasuresPool<T_INPUT, T_TIME> &measures, double h) noexcept;

};

} // namespace chronovise

