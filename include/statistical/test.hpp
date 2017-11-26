#include <list>

template <typename T>
class StatisticalTest {

public:

	StatisticalTest(double significance_level) : significance_level(significance_level) {

	};

	/**
	 * @brief Run the test over the specified values
	 */
	virtual void run(const std::list<T>& values) noexcept = 0;

	/**
	 * @brief Returns the test power (if calculated, @see has_power())
	 */
 	inline double get_power() const noexcept {
		return this->power;
	}

	/**
	 * @brief Returns true if the test power has a power estimation routine
	 */
 	virtual bool has_power() const noexcept = 0;


	/**
	 * @brief Returns true if the null hypotesis is rejected
	 */
	inline bool is_reject() const noexcept {
		return this->reject;
	}

	inline double get_significance_level() const noexcept {
		return this->significance_level;
	}

protected:

	bool reject;
	double power;

private:
	double significance_level;

};

