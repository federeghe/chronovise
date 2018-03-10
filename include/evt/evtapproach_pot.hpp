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
 * @file evtapproach_pot.hpp
 * @author Check commit authors
 * @brief File containing the EVTApproach_PoT class
 */


#ifndef EVT_EVTAPPROACH_POT_HPP_
#define EVT_EVTAPPROACH_POT_HPP_

#include "evtapproach.hpp"

namespace chronovise {

template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach_PoT : public EVTApproach<T_INPUT, T_TIME> {

public:

	EVTApproach_PoT(T_TIME threshold) : threshold(threshold) { }

	virtual void perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) override;

	/**
	 * @brief For PoT this value strongly depends on the data, thus we cannot provide a real value
	 * 	  for this. Consider that perform may in any case fail, e.g. if threshold is too high.
	 */
	virtual unsigned long get_minimal_sample_size() const noexcept override {
		return 1;
	}

private:
	T_TIME threshold;

	void apply_pot(MeasuresPool<T_INPUT, T_TIME> & output_pool,
			typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
			typename std::multimap<T_INPUT,T_TIME>::const_iterator end);


};

} // namespace chronovise

#endif

