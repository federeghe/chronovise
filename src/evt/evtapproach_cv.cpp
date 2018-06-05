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

#include "evt/evtapproach_cv.hpp"
#include "global.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace chronovise {

template <typename T_TIME>
static double compute_cv(typename std::vector<T_TIME>::const_iterator begin,
                         typename std::vector<T_TIME>::const_iterator end, size_t n) {

    // Compute the mean of the vector
    T_TIME sum = std::accumulate(begin, end, 0.0);
    T_TIME mean = sum / n;

    // Now compute the stddev
    std::vector<T_TIME> diff(n);
    std::transform(begin, end, diff.begin(), 
        [mean](T_TIME x) { return x - mean; }
    );
    T_TIME sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / n);

    return stdev / mean;

}


template <typename T_INPUT, typename T_TIME>
void EVTApproach_CV<T_INPUT, T_TIME>::perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) {

    T_TIME best_threshold = 0;

    // We need to find the value of threshold that leads to the best
    // 

    this->training_pool.clear();


    apply_cv(this->training_pool,
         original_pool.cbegin_trainset(),
         original_pool.cend_trainset(), best_threshold);



    // Skim the test_pool with the same (best) value selected for training
    this->test_pool.clear();

    apply_cv(this->test_pool,
         original_pool.cbegin_testset(),
         original_pool.cend_testset(), best_threshold);


}

template <typename T_INPUT, typename T_TIME>
T_TIME EVTApproach_CV<T_INPUT, T_TIME>::get_best_threshold(typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
                          typename std::multimap<T_INPUT,T_TIME>::const_iterator end) {

    std::vector<T_TIME> local_copy;

    for (auto it=begin; it!=end; it++) {
        local_copy.push_back(it->second);
    }

    std::sort (local_copy.begin(), local_copy.end(), std::greater<>());

    const int min_values = 10;

    this->best_cv = 10e5;
    int best_nr_values = 0;

    for (unsigned int i=0; i < local_copy.size() / 2; i++) {
        double currcv = compute_cv<T_TIME>(local_copy.cend() - min_values - i, local_copy.cend(), min_values+i);

        currcv = std::abs(currcv);

        if (currcv < best_cv) {
            best_nr_values = min_values + i;
            this->best_cv = currcv;
        }
    }

    return local_copy[local_copy.size() - best_nr_values];
}


template <typename T_INPUT, typename T_TIME>
void EVTApproach_CV<T_INPUT, T_TIME>::apply_cv(MeasuresPool<T_INPUT, T_TIME> & output_pool,
                           typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
                           typename std::multimap<T_INPUT,T_TIME>::const_iterator end, T_TIME& threshold) {

    size_t i=1;

    if(threshold == 0) {
        threshold = get_best_threshold(begin, end);
    }

    for (auto it = begin; it != end; it++, i++) {
        auto curr_max       = it->second;
        auto curr_max_input = it->first;

        if (curr_max > threshold) {
            output_pool.push(curr_max_input, curr_max);
        }

    }

    if (output_pool.size() == 0) {
        throw std::length_error("PoT threshold is too high: no samples survived.");
    }

}

TEMPLATE_CLASS_IMPLEMENTATION(EVTApproach_CV);

} // namespace chronovise

