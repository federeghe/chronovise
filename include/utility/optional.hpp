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
 * @file utility.hpp
 * @author Check commit authors
 * @brief File containing the optional class
 */

#ifndef UTILITY_OPTIONAL_HPP_
#define UTILITY_OPTIONAL_HPP_

namespace chronovise {
namespace utility {

template<class T>
class optional {
    public:
        optional() : is_present(false), value()
        { }

        optional(nullptr_t) : optional()
        { }

        optional(T value) : is_present(true), value(value)
        { }

        T* operator->() {
            return &value;
        }

        T operator*() {
            return value;
        }

        operator bool() const {
            return is_present;
        }

        void reset() {
            is_present = false;
        }

    private:
        bool is_present;
        T value;
        
};

}
}

#endif
