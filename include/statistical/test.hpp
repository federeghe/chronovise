#ifndef STATISTICAL_TEST_HPP_
#define STATISTICAL_TEST_HPP_

template <typename T_TIME>
class StatisticalTest {

	virtual void run(const MeasuresPool<T_TIME> &measures) = 0;

	inline double get_power() const noexcept {
		return this->power;
	}

	inline bool get_result() const noexcept {
		return this->passed;
	}

protected:
	bool passed;
	double power;

};


#endif
