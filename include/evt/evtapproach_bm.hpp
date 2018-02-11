#ifndef EVT_EVTAPPROACH_BM_HPP_
#define EVT_EVTAPPROACH_BM_HPP_

#include "evtapproach.hpp"

namespace chronovise {

template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach_BM : public EVTApproach<T_INPUT, T_TIME> {

public:

	EVTApproach_BM(size_t block_size) : block_size(block_size) { }

	virtual void perform(const MeasuresPool<T_INPUT, T_TIME>& original_pool);

private:
	size_t block_size;

};

} // namespace chronovise

#endif
