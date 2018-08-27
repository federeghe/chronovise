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
 * @file fileimporter.hpp
 * @author Check commit authors
 * @brief File containing the FileImporter class
 */

#include <fstream>
#include <string>

namespace chronovise {

namespace utility {

/**
 * The FileImporter class is a helper class to read the input samples
 * from a file.
 */
template <typename T>
class FileImporter {

public:
    /**
     * The constructor of the class. It opens the filename
     * specified. If the filename is not accessible nothing
     * happens, but the first call to draw_sample() will generate
     * a std::ifstream::failure exception.
     * @param filename The file to open
     * @param delim The delimiter (in case of CSV file) or 0 is the
                    file is just a plain list of numbers (space and
                    newlines are not considered delimiters)
     */
    FileImporter(const std::string &filename, char delim=0) noexcept;

    /**
     * Get a sample from the file.
     * @throw std::ifstream::failure in case of file problems
     * @throw std::domain_error in case the delimiter is not found
     *                          or different from the one specified.
     */
    T draw_sample();

private:
    std::ifstream ifs;
    char delim;
    bool first_sample;

};


}

} // namespace chronovise
