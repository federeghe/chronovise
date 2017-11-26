#include "mergers/merger.hpp"

class TraceMerger : public Merger {

	virtual void merge(const MeasuresPool<Y, T>& original_pool);

};
