#include "mergers/merger.hpp"

template <typename Y, typename T=unsigned long>
class TraceMerger : public Merger<Y,T> {

	virtual void merge(const MeasuresPool<Y, T>& original_pool);

};
