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
 * @file generator_null.hpp
 * @author Check commit authors
 * @brief File containing the NullInputGenerator class.
 */

#include "input/generator.hpp"

#include <random>

namespace chronovise {

/**
 * An InputGenerator implementation that provides always 0-values. It can be used when the process
 * does not require an input generation phase.
 */
class NullInputGenerator : public InputGenerator<unsigned int> {

public:

    /**
     * @copydoc InputGenerator::get()
     */
    virtual unsigned int get() noexcept override {
        return 0;
    }

    /**
     * @copydoc InputGenerator::to_string()
     */
    virtual const char* to_string() const noexcept {
        return "Null";
    }


private:

};

} // namespace chronovise

