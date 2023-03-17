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
 * @file estimator.hpp
 * @author Check commit authors
 * @brief File containing the Estimator class
 */


#ifndef STATISTICAL_ESTIMATOR_HPP_
#define STATISTICAL_ESTIMATOR_HPP_

#include "distribution.hpp"
#include "../measures_pool.hpp"

#include <memory>
#include <typeinfo>

namespace chronovise {

/**
 * The enumeration for the estimator status output.
 */
typedef enum class estimator_status_e {
    UNKNOWN,    /** The estimation has not run yet */
    SUCCESS,    /** The estimation has converged and been executed correclty */
    NON_PRECISE,    /** The estimation has been probably converging but maximum steps reached */
    FAILED        /** Some error occurred */
} estimator_status_t;


/**
 * The base class for estimator implementation. As usually, it is based on
 * T_INPUT and T_TIME. T_INPUT is not in fact used, but it's needed to access
 * to the relative MeasuresPool. The goal of the derived classes is to provide
 * an estimation of the EVT distribution given the MeasuresPool provided by
 * the AbstractExecutionContext.
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class Estimator {

public:

    /**
     * Virtual destructor
     */
    virtual ~Estimator() {}

    /**
     * This is used to set the EVT approach used in input sample generations to the estimator,
     * that may usually imply a change in the estimation procedure. In particular, if the
     * approach is Block-Maxima a GEV function is estimated, otherwise if is a
     * Peak-over-Threashold a GPD function is estimated.
     * @param ti A pointer to the type_info object (that is guaranteed to be alive till the end of
     *        the program
      */
    void set_source_evt_approach(const std::type_info* ti) noexcept {
        this->ti = ti;
    }

    /**
     * Run the estimation routine on the dataset provided.
     * @param measures The list of measure provided for estimation of their distribution.
     * @return true if the result is usable (i.e. get_result() returns SUCCESS or NON_PRECISE), false otherwise
     */
    virtual bool run(const MeasuresPool<T_INPUT, T_TIME> &measures) = 0;

    /**
     * Run the result. It must be called after a successful estimator run.
     * @return the EVT distribution estimated.
     * @throws std::runtime_error if the estimation is not yet performed or if it failed
     */
    virtual std::shared_ptr<Distribution> get_result() const = 0;

    /**
     * Run the status of the estimation.
     * @return one of the possible value of estimator_status_t
     */
    virtual estimator_status_t get_status() const noexcept = 0;    

    /**
     * @brief It returns the minimal sample size to run the estimator. If a sample with lower
     *      size is provided to run() function, it will probably fail.
     */
    virtual unsigned long get_minimal_sample_size() const noexcept = 0;

    /**
     * @brief A method returning a constant character string identifying the
     *        EVT estimator
     */
    virtual const char* to_string() const noexcept = 0;

protected:
    const std::type_info *ti = nullptr;
};

} // namespace chronovise

#endif
