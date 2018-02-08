#ifndef MEASURES_POOL_HPP_
#define MEASURES_POOL_HPP_

#include <algorithm>
#include <map>
#include <utility>

template <typename Y, typename T=unsigned long>
class MeasuresPool {

public:
	MeasuresPool() {}

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

	inline typename std::map<Y,T>::const_iterator cbegin() const noexcept {
		return meas_list.cbegin();
	}

	inline typename std::map<Y,T>::const_iterator cend() const noexcept {
		return meas_list.cend();
	}

	inline typename std::map<Y,T>::const_iterator begin() const noexcept {
		return meas_list.cbegin();
	}

	inline typename std::map<Y,T>::const_iterator end() const noexcept {
		return meas_list.cend();
	}

	inline typename std::map<Y,T>::iterator begin() noexcept {
		return meas_list.begin();
	}

	inline typename std::map<Y,T>::iterator end() noexcept {
		return meas_list.end();
	}


	inline size_t size() const noexcept {
		return meas_list.size();
	}

	MeasuresPool(const MeasuresPool& m) = delete;
	MeasuresPool& operator=(MeasuresPool const&) = delete;

private:
	
	template <typename A, typename B>
	static constexpr bool meas_map_compare(std::pair<A ,B> i, std::pair<A, B> j) {
		return i.second < j.second;
	}


	std::multimap<Y, T> meas_list;

	

};

#endif
