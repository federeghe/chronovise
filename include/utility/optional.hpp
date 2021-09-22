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
 * @file optional.hpp
 * @author Check commit authors
 * @brief File containing the optional class
 */

#ifndef UTILITY_OPTIONAL_HPP_
#define UTILITY_OPTIONAL_HPP_

#include "../global.hpp"

#include <cstddef>
#include <type_traits>

namespace chronovise {
namespace utility {

/**
 * A class that implements a similar approach to std::optional of C++17
 * (not available in chronovise since it's using C++14).
 * This class may represent any copy-able datatype T and with default
 * constructor.
 */
template<class T>
class optional {
public:

        /**
         * It initializes the object without any object.
         */
        optional() : is_present(false), value()
        {
             static_assert(std::is_default_constructible<T>(),
                                        "A default constructor must exist.");
             static_assert(std::is_default_constructible<T>(),
                                           "A copy-constructor must exist.");
        }

        /**
         * @copydoc optional::optional()
         */
        optional(std::nullptr_t x) : optional()
        { UNUSED(x); }

        /**
         * It initializes the object with the provided value.
         * @param value The value to set.
         */
        optional(T value) : is_present(true), value(value)
        {
        }

        /**
         * It provides the stored value. The behaviour of this method
         * when called without previously set a value is undefined.
         * @note Using this when T is not a pointer does not make any
         *       sense and may confuse developers. In that case, it
         *       throws an exception.
         */
        T operator->() noexcept {
            static_assert(std::is_pointer<T>::value, "The use of -> "
                                            "requires T to be a pointer.");
            return value;
        }

        /**
         * It provides the value of the stored value. The behaviour of this method
         * when called without previously set a value is undefined.
         */
        T operator*() const {
            return value;
        }

        /**
         * It returns true when the value is present, false otherwise.
         */
        operator bool() const noexcept {
            return is_present;
        }

        /**
         * Set a new valid value
         */
        void set(T value) {
            this->value = value;
            this->is_present = true;
        }

        /**
         * Reset the container to 'no-value'
         */
        void reset() noexcept {
            is_present = false;
        }

    private:
        bool is_present;
        T value;
        
};

}
}

#endif
