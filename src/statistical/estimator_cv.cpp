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

#include "statistical/estimator_cv.hpp"

#include "evt/evtapproach_cv.hpp"
#include "evt/gpd_distribution.hpp"
#include "global.hpp"

#include <algorithm>
#include <cmath>

namespace chronovise {


template <typename T_INPUT, typename T_TIME>
void Estimator_CV<T_INPUT, T_TIME>::estimator_gpd(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {
    // Reference:
    // Measurement-Based Worst-Case Execution Time Estimation Using the Coefficient of Variation
    // J. Abella, M. Padilla, J.D. Castillo, and F. J. Cazorla, ACM Trans. Des. Autom. Electron. Syst, 2017
    // DOI: 10.1145/3065924

    const size_t n = measures.size();

    std::vector<T_TIME> exceedence_values;
    
    for (const auto &val : measures) {
            exceedence_values.push_back(val.second - measures[0]);
    }

    // Compute the mean of the vector
    T_TIME sum = std::accumulate(exceedence_values.begin(), exceedence_values.end(), 0.0);
    T_TIME mean = sum / n;

    result = std::make_shared<GPD_Distribution>(measures[0], mean, 0);    //  xi=0 is the exponential distribution

}

template <typename T_INPUT, typename T_TIME>
bool Estimator_CV<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    if (this->ti == nullptr) {
        throw std::runtime_error("Set_source_evt_approach not called.");
    }
    
    // Now we have to select the function to optimize based on the provided type information
    if (*this->ti == typeid(EVTApproach_CV<T_INPUT, T_TIME>)) {
        this->estimator_gpd(measures);
    }
    else {
        throw std::runtime_error("CV estimator is not able to estimate this distribution.");
    }


    status = estimator_status_t::SUCCESS;

    return true;
}

TEMPLATE_CLASS_IMPLEMENTATION(Estimator_CV);

} // namespace chronovise
