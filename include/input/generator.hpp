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
 * @file generator.hpp
 * @author Check commit authors
 * @brief File containing the InputGenerator abstract base class.
 */

#ifndef INPUT_GENERATOR_HPP_
#define INPUT_GENERATOR_HPP_

namespace chronovise {

/**
 * The InputGenerator base class. It is in charge of generating inputs
 * that should be passed to program that is being measuring.
 */
template <typename T>
class InputGenerator {

public:

    /**
     * Generates a new input value.
     */
    virtual T get() noexcept = 0;

};

} // namespace chronovise

#endif
