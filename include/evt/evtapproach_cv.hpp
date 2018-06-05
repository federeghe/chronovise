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
 * @file evtapproach_cv.hpp
 * @author Check commit authors
 * @brief File containing the EVTApproach_CV class
 */


#ifndef EVT_EVTAPPROACH_CV_HPP_
#define EVT_EVTAPPROACH_CV_HPP_

#include "evtapproach.hpp"

namespace chronovise {

/**
 * Peak-over-Threshold EVT approach class with threashold based on MBPTA-CV.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach_CV : public EVTApproach<T_INPUT, T_TIME> {

public:

    /**
     * The costructor of the PoT approach
     * @param threshold the value for PoT, below that the samples are discarded
     */
    EVTApproach_CV() { }

    /**
     * @copydoc EVTApproach::~EVTApproach()
     */
    virtual ~EVTApproach_CV() { }

    /**
     * @copydoc EVTApproach::perform()
     */
    virtual void perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) override;

    /**
     * @brief For PoT this value strongly depends on the data, thus we cannot provide a real value
     *       for this. Consider that perform may in any case fail, e.g. if threshold is too high.
     */
    virtual unsigned long get_minimal_sample_size() const noexcept override {
        return 1000;
    }

    /**
     * Return the name of the approach (relative to the class not the object even if not static)
     * @return The string "Peak-over-Threshold"
     */
    virtual const char* to_string() const noexcept override {
        return "Coefficient of Variation";
    }

private:

    void apply_cv(MeasuresPool<T_INPUT, T_TIME> & output_pool,
            typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
            typename std::multimap<T_INPUT,T_TIME>::const_iterator end, T_TIME& threshold);

    T_TIME get_best_threshold(typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
                              typename std::multimap<T_INPUT,T_TIME>::const_iterator end);

    double best_cv;

};

} // namespace chronovise

#endif

