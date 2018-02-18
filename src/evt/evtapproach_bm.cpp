#include "evt/evtapproach_bm.hpp"

#include <limits>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
void EVTApproach_BM<T_INPUT, T_TIME>::perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) {

	this->m_pool.clear();

	// We need at least 2 block ...
	if (original_pool.size_training() < 2*block_size) {
		throw std::length_error("Not enough measures to split over at least 2 blocks");
	}

	size_t i=1;
	T_TIME  curr_max = std::numeric_limits<T_TIME>::min();
	T_INPUT curr_max_input;

	for (auto it = original_pool.cbegin_trainset(); it != original_pool.cend_trainset(); it++, i++) {

		if (curr_max < it->second) {
			curr_max       = it->second;
			curr_max_input = it->first;
		}

		if (i % block_size == 0) {
			this->m_pool.push(curr_max_input, curr_max);
			curr_max = std::numeric_limits<T_TIME>::min();
		}
	}

	if (original_pool.size_training() % block_size != 0) {
		// We need to add the last value becuase the last block is not sufficiently
		// large to reach block_size
		this->m_pool.push(curr_max_input, curr_max);
	}

}



template class EVTApproach_BM<char, unsigned long>;
template class EVTApproach_BM<int, unsigned long>;
template class EVTApproach_BM<long, unsigned long>;
template class EVTApproach_BM<float, unsigned long>;
template class EVTApproach_BM<double, unsigned long>;
template class EVTApproach_BM<unsigned char, unsigned long>;
template class EVTApproach_BM<unsigned int, unsigned long>;
template class EVTApproach_BM<unsigned long, unsigned long>;

} // namespace chronovise

