#ifndef EVT_EVTAPPROACH_HPP_
#define EVT_EVTAPPROACH_HPP_

#include "measures_pool.hpp"

namespace chronovise {

template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach {

public:
	virtual void perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) = 0;

	MeasuresPool<T_INPUT, T_TIME>& get_training_pool() noexcept {
		return this->training_pool;
	}

	MeasuresPool<T_INPUT, T_TIME>& get_test_pool() noexcept {
		return this->test_pool;
	}

	/**
	 * @brief It returns the minimal sample size to run the estimator. If a sample with lower
	 *	  size is provided to run() function, it will probably fail.
	 */
	virtual unsigned long get_minimal_sample_size() const noexcept = 0;

protected:
	MeasuresPool<T_INPUT, T_TIME> training_pool;
	MeasuresPool<T_INPUT, T_TIME> test_pool;

};

} // namespace chronovise

#endif
