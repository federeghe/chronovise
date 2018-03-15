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
 * @file estimator_pwm.hpp
 * @author Check commit authors
 * @brief File containing the Estimator_PWM class
 */

#ifndef STATISTICAL_ESTIMATOR_PWM_HPP_
#define STATISTICAL_ESTIMATOR_PWM_HPP_

#include "statistical/estimator.hpp"
#include "statistical/distribution.hpp"

#include <memory>

namespace chronovise {

/**
 * The Probability Weighted Moment estimator class.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class Estimator_PWM : public Estimator<T_INPUT, T_TIME> {

public:

    /**
     * A simple destructor
     */
    virtual ~Estimator_PWM() {}

    /**
     * @copydoc Estimator::run()
     */
    virtual bool run(const MeasuresPool<T_INPUT, T_TIME> &measures) override;

    /**
     * @copydoc Estimator::get_result()
     */
    virtual std::shared_ptr<Distribution> get_result() const override final {
        if (result == nullptr)
            throw std::runtime_error("Estimator never run");
        
        return result;
    }

    /**
     * @copydoc Estimator::get_status()
     */
    virtual estimator_status_t get_status() const noexcept {
        return status;
    }

    /**
     * @copydoc Estimator::get_minimal_sample_size()
     */
    virtual unsigned long get_minimal_sample_size() const noexcept {
        return 10;
    }

    /**
     * @copydoc Estimator::to_string()
     */
    virtual const char* to_string() const noexcept {
        return "Probabilistic Weighted Moments (PWM)";
    }

private:
    std::shared_ptr<Distribution> result;
    estimator_status_t status=estimator_status_t::UNKNOWN;


    double moment(const MeasuresPool<T_INPUT, T_TIME> &measures, int r) const noexcept;

    void estimator_gpd(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;
    void estimator_gev(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;


};

} // namespace chronovise

#endif // STATISTICAL_ESTIMATOR_PWM_HPP_
