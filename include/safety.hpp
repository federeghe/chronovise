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
 * @file safety.hpp
 * @author Check commit authors
 * @brief File containing the Safety class
 */

#ifndef SAFETY_HPP_
#define SAFETY_HPP_

#include "utility/relation_operator.hpp"

#include <memory>

namespace chronovise {

/**
 * The Safety class handles all the data
 */
class Safety {

public:

    /**
     * The constructor. Nothing special is done here.
     */
    Safety() {}

    /**
     * Setter for the reliability requirement.
     * @param reliability_requirement The reliability expressed as the probability that the WCET
     *        is greater than the computed one.
     */
    void set_reliability_requirement(double reliability_requirement) noexcept {
        this->reliability_req = reliability_requirement;
        reliability_req_opt = true;
    }

    bool has_reliability_requirement() const noexcept {
        return this->reliability_req_opt;
    }

    double get_reliability_requirement() const noexcept {
        return this->reliability_req;
    }

    void set_input_representativity(bool is_representativity) noexcept {
        this->input_representativity = is_representativity;
    }

    /**
     * Provides the information on safety of the representativeness of the input data.
     * @return true if the input data have been successfully tested.
     * @note If the application returns AEC_OK in onConfigure(), this value is always false.
     */
    bool is_input_representativity() const noexcept {
        return this->input_representativity;
    }

    void set_evt_safe(bool is_safe) noexcept {
        this->evt_safe = is_safe;
    }

    bool is_evt_safe() const noexcept {
        return this->evt_safe;
    }

    void set_test_tree(std::shared_ptr<RelationOperator> root) noexcept {
        this->test_tree_root = root;
    }

    /**
     * It computes the reliability given the statistical test power. It return -1
     * if the calculation is not possible or the tests' tree is not provided by the
     * set_test_tree() method.
     * @throw std::runtime_error in case of malformed tests' tree.
     */
    double compute_reliability() const;

private:
    bool input_representativity = true;
    bool evt_safe = true;
    bool reliability_req_opt = false; // True of realibility_req setted
    double reliability_req;

    std::shared_ptr<RelationOperator> test_tree_root;

};

} // namespace chronovise

#endif
