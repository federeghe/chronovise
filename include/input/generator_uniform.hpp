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
 * @file generator_uniform.hpp
 * @author Check commit authors
 * @brief File containing the UniformInputGenerator class.
 */

#include "input/generator.hpp"

#include <random>

namespace chronovise {

/**
 * An InputGenerator implementation that provides uniformly distributed
 * numbers of generic type T.
 */
template <typename T>
class UniformInputGenerator : public InputGenerator<T> {

public:

    /**
     * Min-Max constructor. It inizializes the seed from
     * a random available device. The numbes are drawn from
     * the interval [min,max] with a uniform probability.
     * @param min The maximum value of the generated values
     * @param max The maximum value of the generated values
     */
    UniformInputGenerator(T min, T max) : mt(rd())
    {
        this->min = min;
        this->max = max;
    } 

    virtual ~UniformInputGenerator() = default;

    /**
     * @copydoc InputGenerator::get()
     */
    virtual T get() noexcept override;

    /**
     * @copydoc InputGenerator::to_string()
     */
    virtual const char* to_string() const noexcept override {
        return "Uniform";
    }


private:
    std::random_device rd;
    std::mt19937 mt;
    
    T min;
    T max;

};

} // namespace chronovise

