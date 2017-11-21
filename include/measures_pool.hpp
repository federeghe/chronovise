#ifndef MEASURES_POOL_HPP_
#define MEASURES_POOL_HPP_

#include <algorithm>
#include <vector>

template <typename T=unsigned long>
class MeasuresPool {

public:
	inline void push(T value) noexcept {
		this->meas_list.push_back(value);
	}

	inline T max() const noexcept {
		return *std::max_element(meas_list.begin(), meas_list.end());
	}

private:
	std::vector<T> meas_list;
};

#endif
