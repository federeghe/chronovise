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
 * @file fileimporter.cpp
 * @author Check commit authors
 * @brief File containing the FileImporter class implementation
 */

#include "utility/fileimporter.hpp"

#include "global.hpp"


namespace chronovise {

namespace utility {

template <typename T>
FileImporter<T>::FileImporter(const std::string &filename, char delim) noexcept
    : ifs(filename), delim(delim), first_sample(true)
{
    ifs.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    // Nothing to do
}

template <typename T>
T FileImporter<T>::draw_sample() {
    if (this->delim != 0 && first_sample) {
        char to_read;
        ifs >> to_read;
        if (to_read != this->delim) {
            throw std::domain_error("Wrong delimiter in the input file.");
        }
    }

    this->first_sample = false;

    T temp;
    ifs >> temp;
    return temp;
}

TEMPLATE_CLASS_IMPLEMENTATION_T(FileImporter);

} // namespace utility

} // namespace chronovise
