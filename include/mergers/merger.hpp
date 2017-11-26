#include "measures_pool.hpp"

template <typename Y, typename T=unsigned long>
class Merger {

public:
	virtual void perform(const MeasuresPool<Y, T>& original_pool) = 0;

	MeasuresPool<Y, T>& get_pool() noexcept {
		return this->m_pool;
	}

protected:
	MeasuresPool<Y, T> m_pool;

};
