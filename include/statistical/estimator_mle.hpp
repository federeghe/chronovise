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
 * @file estimator_mle.hpp
 * @author Check commit authors
 * @brief File containing the Estimator_MLE class
 */

#ifndef STATISTICAL_ESTIMATOR_MLE_HPP_
#define STATISTICAL_ESTIMATOR_MLE_HPP_

#include "statistical/estimator.hpp"
#include "statistical/distribution.hpp"

#include <memory>
#include <stdexcept>

namespace chronovise {

/**
 * The Maximum Likelihood Estimator class. The estimation routine is based on
 * ceres-solver software.
 */
template <typename T_INPUT, typename T_TIME=unsigned long, bool GMLE=false>
class Estimator_MLE : public Estimator<T_INPUT, T_TIME> {

public:

    /**
     * A simple destructor
     */
    virtual ~Estimator_MLE() {}

    /**
     * @copydoc Estimator::run()
     * @note The initial guess for MLE is set to location=0, shape=0,
     * scale=measures.max()/100.
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
        return 2;    // Well... in theory ;-)
    }

    /**
     * @copydoc Estimator::to_string()
     */
    virtual const char* to_string() const noexcept override {
        if(! GMLE) {
            return "Maximum-Likelihood (MLE)";
        } else {
            return "Generalized Maximum-Likelihood (GMLE)";
        }
    }
    
    void set_initial_guess(double mu, double sg, double xi) {
        initial_guess[0] = mu;
        initial_guess[1] = sg;
        initial_guess[2] = xi;
        this->inital_guess_provided = true;
    }

private:
    std::shared_ptr<Distribution> result;
    estimator_status_t status=estimator_status_t::UNKNOWN;
    bool inital_guess_provided = false;
    double initial_guess[3];
};

} // namespace chronovise

#endif
