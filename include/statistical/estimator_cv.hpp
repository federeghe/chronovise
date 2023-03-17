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
 * @brief File containing the Estimator_CV class
 * @note Based on algorithm proposed in https://doi.org/10.1145/3065924
 */

#ifndef STATISTICAL_ESTIMATOR_CV_HPP_
#define STATISTICAL_ESTIMATOR_CV_HPP_

#include "estimator.hpp"
#include "distribution.hpp"

#include <memory>
#include <stdexcept>

namespace chronovise {

/**
 * The MBPTA-CV estimator class.
 * @note This class can estimate only GPD distributions
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class Estimator_CV : public Estimator<T_INPUT, T_TIME> {

public:

    /**
     * Constructor for the MBPTA-CV estimator
     * @param threshold The threshold used for PoT
     *
     */
    Estimator_CV() {
        // Nothing to do
    }

    /**
     * A simple destructor
     */
    virtual ~Estimator_CV() {}

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
    virtual estimator_status_t get_status() const noexcept override {
        return status;
    }

    /**
     * @copydoc Estimator::get_minimal_sample_size()
     */
    virtual unsigned long get_minimal_sample_size() const noexcept override {
        return 50;
    }

    /**
     * @copydoc Estimator::to_string()
     */
    virtual const char* to_string() const noexcept override {
        return "MBPTA-CV";
    }

    double get_cv_value() const noexcept {
        return this->cv_value;
    }

private:

    double cv_value;

    std::shared_ptr<Distribution> result;
    estimator_status_t status=estimator_status_t::UNKNOWN;


    void estimator_gpd(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept;


};

} // namespace chronovise

#endif // STATISTICAL_ESTIMATOR_PWM_HPP_
