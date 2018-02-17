/*
 *  chronovise - Copyright 2018 Politecnico di Milano
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file measures_pool.hpp
 * @author Check commit authors
 * @brief File containing the MeasuresPool class
 */

#ifndef MEASURES_POOL_HPP_
#define MEASURES_POOL_HPP_

#include <algorithm>
#include <cassert>
#include <map>
#include <utility>
#include <vector>

namespace chronovise {

/**
 * The MeasuresPool class handles the measured data. It is based on two template arguments, the first
 * for the input type, the second for the time type. This class basically encapsulates a
 * std::multimap and provides methods to access it.
 * @warning This class is NOT thread safe.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class MeasuresPool {

public:

	/**
	 * The constructor. Nothing special is done here.
	 */
	MeasuresPool() {}

	/**
	 * Add a new value in the pool.
	 * @param input_rep The input representing the measurement
	 * @param value The actual measured time value
	 */
	inline void push(T_INPUT input_rep, T_TIME value) noexcept {
		this->meas_list.insert(std::pair<T_INPUT,T_TIME>(input_rep,value));
	}

	/**
	 * Returns the maximum value in the pool. Complexity O(n).
	 * @return The maximum time value in the container 
	 */
	inline T_TIME max() const noexcept {
		auto it = std::max_element(meas_list.begin(), meas_list.end(), meas_map_compare<T_INPUT,T_TIME>);
		return it->second;					
	}

	/**
	 * Returns the minimum value in the pool. Complexity O(n).
	 * @return The minimum time value in the container 
	 */
	inline T_TIME min() const noexcept {
		auto it = std::min_element(meas_list.begin(), meas_list.end(), meas_map_compare<T_INPUT,T_TIME>);
		return it->second;					
	}

	/**
	 * Returns the const_iterator to the begin of the underlying container
	 * @return The constant begin iterator 
	 */
	inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cbegin() const noexcept {
		return meas_list.cbegin();
	}

	/**
	 * Returns the const_iterator to the end of the underlying container
	 * @return The constant end iterator 
	 */
	inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cend() const noexcept {
		return meas_list.cend();
	}

	/**
	 * Returns the const_iterator to the begin of the underlying container
	 * @return The constant begin iterator 
	 */
	inline typename std::multimap<T_INPUT,T_TIME>::const_iterator begin() const noexcept {
		return meas_list.cbegin();
	}

	/**
	 * Returns the const_iterator to the end of the underlying container
	 * @return The constant end iterator 
	 */
	inline typename std::multimap<T_INPUT,T_TIME>::const_iterator end() const noexcept {
		return meas_list.cend();
	}

	/**
	 * Returns the iterator to the begin of the underlying container
	 * @return The begin iterator 
	 */
	inline typename std::multimap<T_INPUT,T_TIME>::iterator begin() noexcept {
		return meas_list.begin();
	}

	/**
	 * Returns the iterator to the end of the underlying container
	 * @return The end iterator 
	 */
	inline typename std::multimap<T_INPUT,T_TIME>::iterator end() noexcept {
		return meas_list.end();
	}

	/**
	 * Delete all the values from the container
	 */
	inline void clear() noexcept {
		this->meas_list.clear();
	}

	/**
	 * Returns the size of the container
	 * @return The number of pairs <T_INPUT,T_TIME> of the container
	 */
	inline size_t size() const noexcept {
		return meas_list.size();
	}

	/**
	 * Ordered access to the timing values regardless of the input value
	 * @note Complexity is O(n log n) amortized: subsequent calls cost O(1).
	 * @param idx Index of the value to access
	 */
	inline const T_TIME& operator[](size_t idx) const {
		if (time_ordered_vector.size() == 0) {
			populate_ordered_vector();
		}
		return time_ordered_vector[idx];
	}


private:


	std::multimap<T_INPUT, T_TIME> meas_list;
	mutable std::vector<T_TIME> time_ordered_vector;

	MeasuresPool(const MeasuresPool& m) = delete;
	MeasuresPool& operator=(MeasuresPool const&) = delete;
	
	template <typename A, typename B>
	static constexpr bool meas_map_compare(std::pair<A ,B> i, std::pair<A, B> j) {
		return i.second < j.second;
	}

	void populate_ordered_vector() const {
		assert(time_ordered_vector.size() == 0);

		std::for_each(meas_list.cbegin(), meas_list.cend(), 
				[&](const auto& element) {
					time_ordered_vector.push_back(element.second);
				});

		std::sort(time_ordered_vector.begin(), time_ordered_vector.end());

		assert(time_ordered_vector.size() == meas_list.size());
	}

};

} // namespace chronovise

#endif
