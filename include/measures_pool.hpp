#ifndef MEASURES_POOL_HPP_
#define MEASURES_POOL_HPP_

#include <algorithm>
#include <map>
#include <utility>

template <typename Y, typename T=unsigned long>
class MeasuresPool {

public:
	inline void push(Y input_rep, T value) noexcept {
		this->meas_list.insert(std::pair<Y,T>(input_rep,value));
	}

	inline T max() const noexcept {
		auto it = std::max_element(meas_list.begin(), meas_list.end(), meas_map_compare<Y,T>);
		return it->second;					
	}

	inline T min() const noexcept {
		auto it = std::min_element(meas_list.begin(), meas_list.end(), meas_map_compare<Y,T>);
		return it->second;					
	}

	inline typename std::map<Y,T>::iterator cbegin() const noexcept {
		return meas_list.cbegin();
	}

	inline typename std::map<Y,T>::iterator cend() const noexcept {
		return meas_list.cend();
	}

	inline size_t size() const noexcept {
		return meas_list.size();
	}

private:
	
	template <typename A, typename B>
	static constexpr bool meas_map_compare(std::pair<A ,B> i, std::pair<A, B> j) {
		return i.second < j.second;
	}


	std::multimap<Y, T> meas_list;

	

};

#endif
