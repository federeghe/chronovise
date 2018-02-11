#ifndef STATISTICAL_TEST_HPP_
#define STATISTICAL_TEST_HPP_

#include "statistical/ev_distribution.hpp"
#include "measures_pool.hpp"

namespace chronovise {

template <typename T_TIME=unsigned long>
class StatisticalTest {

public:
	StatisticalTest(double significance_level)
			: significance_level(significance_level) {

	}

	virtual void run(const MeasuresPool<T_TIME> &measures) noexcept = 0;

	/**
	 * @brief Returns the statistical test power.
	 * @note The returned value is not usually the computer power that does not provide any
	 *	 statistical information. The power is usually computed a priori from the
	 *	 significance_level provided
	 */
	virtual double get_power() const = 0;

	/**
	 * @brief Returns true if the null hypotesis is rejected
	 */
	bool is_reject() const noexcept {
		return this->reject;
	}

	/**
	 * @brief Returns true if the test has power estimation routine. It can be called before the
	 *	  test
	 */
	virtual bool has_power() const noexcept = 0;

	/**
	 * @brief Returns true if the test performed a power estimation that can be considered
	 *	  "safe", i.e. the value obtained from get_power() is not overestimated. This method
	 *	  returns always false if has_power()==false.
	 * @note  It must be called AFTER the test run.
	 */
	virtual bool has_safe_power() const noexcept = 0;

	/**
	 * @brief It returns the minimal sample size to run the test. If a lower a sample with lower
	 *	  size is provided to run() function, it will probably fail.
	 */
	virtual unsigned int get_minimal_sample_size() const noexcept = 0;

	/**
	 * @brief It provides the minimal sample size to obtain a power of 1 with an accuracy
	 *	  10^(-req_power). The obtained value should be incremented by the caller with
	 *	  an appropriate engineering safety margin
	 * @param req_power The accuracy expressed with 10^(-req_power). Tipical values are 3, 6, or 9
	 * @throw std::logic_error if has_power() == false
	 * @throw std::invalid_argument if the value of req_power is too high and not supported
	 */
	virtual unsigned int get_minimal_sample_size(unsigned short req_power) const = 0;


protected:
	bool reject = false;

	const double significance_level;
};

template <typename T_TIME=unsigned long>
class StatisticalTest_AfterEVT : public StatisticalTest<T_TIME> {

public:
	StatisticalTest_AfterEVT(double significance_level)
	: StatisticalTest<T_TIME>(significance_level) { }

	void set_ref_distribution(const EV_Distribution& ev_distribution) noexcept
	{
		this->ref_distribution = ev_distribution;
	}

protected:
	EV_Distribution ref_distribution;
};

} // chronovise

#endif
