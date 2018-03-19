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
 * @file aec.hpp
 * @author Check commit authors
 * @brief File containing the AbstractExecutionContext class
 */

#ifndef EXPORTER_HPP_
#define EXPORTER_HPP_

#include "aec.hpp"

#include <fstream>
#include <memory>

namespace chronovise {

template<typename T_INPUT, typename T_TIME>
class Exporter {

public:
    explicit Exporter(const AbstractExecutionContext<T_INPUT, T_TIME> &aec, bool binary=false) noexcept
            : aec(aec), binary(binary)

    {
    }

    void save_time_samples(const std::string& filename) const;

    void save_wcots(const std::string& filename) const;

    void save_estimated_distributions(const std::string& filename) const;

private:
    const AbstractExecutionContext<T_INPUT, T_TIME> &aec;
    const bool binary;

    static std::unique_ptr<std::ofstream> open_stream(const std::string& filename);

};

} // namespace chronovise
#endif
