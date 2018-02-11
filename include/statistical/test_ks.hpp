#include "statistical/test.hpp"

#include <cmath>
#include <list>

#define TEST_KS_MIN_SAMPLES 10

namespace chronovise {

template <typename T=unsigned long>
class TestKS : public StatisticalTest_AfterEVT<T> {

public:

	TestKS(double significance_level)
	: StatisticalTest_AfterEVT<T>(significance_level) 
	{
		static_assert(std::is_arithmetic<T>::value,
		"Type must be an integer or floating point type");
	};

	/**
	 * @brief Run the test over the specified values
	 */
	virtual void run(const MeasuresPool<T> &measures) noexcept;

	/**
	 * @brief Returns the test power (if calculated, @see has_power())
	 */
 	virtual double get_power() const override {
		return this->power;
	}

	/**
	 * @brief Returns true if the test power has a power estimation routine
	 */
 	virtual bool has_power() const noexcept override {
		return this->significance_level == 0.05 || this->significance_level == 0.01;
	}

 	virtual bool has_safe_power() const noexcept override {
		return  has_power()
			&& this->ref_distribution.get_shape() != 0.0
			&& std::abs(this->ref_distribution.get_shape()) < 0.5;
	}

	double get_significance_level() const noexcept {
		return this->significance_level;
	}

	virtual unsigned int get_minimal_sample_size() const noexcept {
		return TEST_KS_MIN_SAMPLES;
	}

	virtual unsigned int get_minimal_sample_size(unsigned short req_power) const;

protected:

	double power;


};

} // namespace chronovise

