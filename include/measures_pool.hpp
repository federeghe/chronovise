#ifndef MEASURES_POOL_HPP_
#define MEASURES_POOL_HPP_

#include <algorithm>
#include <map>
#include <utility>

template <typename T_INPUT, typename T_TIME=unsigned long>
class MeasuresPool {

public:
	MeasuresPool() {}

	inline void push(T_INPUT input_rep, T_TIME value) noexcept {
		this->meas_list.insert(std::pair<T_INPUT,T_TIME>(input_rep,value));
	}

	inline T_TIME max() const noexcept {
		auto it = std::max_element(meas_list.begin(), meas_list.end(), meas_map_compare<T_INPUT,T_TIME>);
		return it->second;					
	}

	inline T_TIME min() const noexcept {
		auto it = std::min_element(meas_list.begin(), meas_list.end(), meas_map_compare<T_INPUT,T_TIME>);
		return it->second;					
	}

	inline typename std::map<T_INPUT,T_TIME>::const_iterator cbegin() const noexcept {
		return meas_list.cbegin();
	}

	inline typename std::map<T_INPUT,T_TIME>::const_iterator cend() const noexcept {
		return meas_list.cend();
	}

	inline typename std::map<T_INPUT,T_TIME>::const_iterator begin() const noexcept {
		return meas_list.cbegin();
	}

	inline typename std::map<T_INPUT,T_TIME>::const_iterator end() const noexcept {
		return meas_list.cend();
	}

	inline typename std::map<T_INPUT,T_TIME>::iterator begin() noexcept {
		return meas_list.begin();
	}

	inline typename std::map<T_INPUT,T_TIME>::iterator end() noexcept {
		return meas_list.end();
	}


	inline void clear() noexcept {
		this->meas_list.clear();
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


	std::multimap<T_INPUT, T_TIME> meas_list;

	

};

#endif
