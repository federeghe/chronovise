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
 * @brief File containing the MeasuresPool and MeasuresPoolSet classes
 */

#ifndef MEASURES_POOL_HPP_
#define MEASURES_POOL_HPP_

#include <algorithm>
#include <cassert>
#include <map>
#include <cmath>
#include <numeric>
#include <utility>
#include <vector>

#include "utility/optional.hpp"

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
     * Returns the average/mean value in the pool. Complexity O(n).
     * @return The average value in the container 
     */
    inline T_TIME avg() const noexcept {
        return std::accumulate(meas_list.begin(), meas_list.end(), 0., 
            [] (double value, const auto& p){return value+p.second;}) / meas_list.size();
    }

    /**
     * Returns the variance value in the pool. Complexity O(n).
     * @return The variance value in the container 
     */
    inline T_TIME var() const noexcept {
        T_TIME mean = this->avg();
        std::vector<T_TIME> diff(this->size());
        std::transform(meas_list.cbegin(), meas_list.cend(), diff.begin(), [mean](const auto& p) { return p.second - mean; });
        double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
        return sq_sum / this->size();
    }

    /**
     * Returns the standard deviation value in the pool. Complexity O(n).
     * @return The standard deviation value in the container 
     */
    inline T_TIME stdev() const noexcept {
        return std::sqrt(this->var());
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
     * Returns the const_iterator to the begin of the underlying container for the input key
     * @return The constant begin iterator 
     */
    inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cbegin(const T_INPUT& input) const noexcept {
        return meas_list.equal_range(input).first;
    }

    /**
     * Returns the const_iterator to the end of the underlying container for the input key
     * @return The constant end iterator 
     */
    inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cend(const T_INPUT&input) const noexcept {
        return meas_list.equal_range(input).second;
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

    inline const std::vector<T_TIME>& get_ordered_vector() const {
        if (time_ordered_vector.size() == 0) {
            populate_ordered_vector();
        }
        return time_ordered_vector;
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

/**
 * The MeasuresPoolSet class is used internally to wrap and split the MeasuresPool into
 * training and test set. It should be used in EVTApproach management only.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class MeasuresPoolSet {

public:
    typedef MeasuresPool<T_INPUT, T_TIME> mp_t;

    /**
     * The constructor of the class with reference_input specification
     * @param mp The original MeasuresPool
     * @param training_set_ratio The ratio of training set/test set ratio
     */
    MeasuresPoolSet(const mp_t& mp, float training_set_ratio) : MeasuresPoolSet(mp, training_set_ratio, nullptr)
    {
    }

    /**
     * The constructor of the class with reference_input specification
     * @param mp The original MeasuresPool
     * @param training_set_ratio The ratio of training set/test set ratio
     * @param reference_input The input to refer in mp
     */
    MeasuresPoolSet(const mp_t& mp, float training_set_ratio, utility::optional<T_INPUT> reference_input)
                   : mp(mp), reference_input(reference_input)
    {
        assert(training_set_ratio >= 0. && training_set_ratio <= 1.);
        this->n_train = mp.size() * training_set_ratio;
    }

    /**
     * Returns the const_iterator to the begin of the training set
     * @return The constant begin iterator 
     */
    inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cbegin_trainset() const noexcept {
            return mp.cbegin();
    }

    /**
     * Returns the const_iterator to the end of the training set
     * @return The constant end iterator 
     */
    inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cend_trainset() const noexcept {
        auto it = mp.cbegin();
        std::advance(it, n_train);
        return it;
    }

    /**
     * Returns the const_iterator to the begin of the test set
     * @return The constant begin iterator 
     */
    inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cbegin_testset() const noexcept {
        return this->cend_trainset();
    }

    /**
     * Returns the const_iterator to the end of the test set
     * @return The constant end iterator 
     */
    inline typename std::multimap<T_INPUT,T_TIME>::const_iterator cend_testset() const noexcept {
        return mp.cend();
    }

    /**
     * Returns the size of the underlying container
     * @return The number of pairs <T_INPUT,T_TIME> of the container
     */
    inline size_t size_trainset() const noexcept {
        return n_train;
    }

    /**
     * Returns the size of the underlying container
     * @return The number of pairs <T_INPUT,T_TIME> of the container
     */
    inline size_t size_testset() const noexcept {
        return mp.size() - n_train;
    }

private:

    typename std::multimap<T_INPUT,T_TIME>::const_iterator get_mp_cbegin() const noexcept {
        if (!reference_input) return this->mp.cbegin();
        else return this->mp.cbegin(*reference_input);
    }

    typename std::multimap<T_INPUT,T_TIME>::const_iterator get_mp_cend() const noexcept {
        if (!reference_input) return this->mp.cend();
        else return this->mp.cend(*reference_input);
    }

    const mp_t &mp;

    size_t n_train;

    utility::optional<T_INPUT> reference_input;

};

} // namespace chronovise

#endif
