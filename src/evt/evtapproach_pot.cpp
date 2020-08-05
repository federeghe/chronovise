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

#include "evt/evtapproach_pot.hpp"
#include "global.hpp"

#include <limits>
#include <stdexcept>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
void EVTApproach_PoT<T_INPUT, T_TIME>::perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) {

    this->training_pool.clear();
    this->test_pool.clear();


    apply_pot(this->training_pool,
         original_pool.cbegin_trainset(),
         original_pool.cend_trainset());

    apply_pot(this->test_pool,
         original_pool.cbegin_testset(),
         original_pool.cend_testset());


}

template <typename T_INPUT, typename T_TIME>
void EVTApproach_PoT<T_INPUT, T_TIME>::apply_pot(MeasuresPool<T_INPUT, T_TIME> & output_pool,
                           typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
                           typename std::multimap<T_INPUT,T_TIME>::const_iterator end) {

    size_t i=1;

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

TEMPLATE_CLASS_IMPLEMENTATION(EVTApproach_PoT);

} // namespace chronovise

