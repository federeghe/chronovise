#ifndef EVT_EVTAPPROACH_HPP_
#define EVT_EVTAPPROACH_HPP_

#include "measures_pool.hpp"

namespace chronovise {

template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach {

public:
	virtual void perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) = 0;

	MeasuresPool<T_INPUT, T_TIME>& get_pool() noexcept {
		return this->m_pool;
	}

protected:
	MeasuresPool<T_INPUT, T_TIME> m_pool;

};

} // namespace chronovise

#endif
