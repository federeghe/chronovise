#include "mergers/trace_merger.hpp"

template <typename Y, typename T>
void TraceMerger<Y,T>::merge(const MeasuresPool<Y, T>& original_pool) {

	Y default_value;

	for (const auto &time_pair : original_pool) {
		this->m_pool.push(default_value, time_pair.second);
	}

}

