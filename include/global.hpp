/*
 * chronovise - Copyright 2018 Politecnico di Milano
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
 * @file global.hpp
 * @author Check commit authors
 * @brief A global header that contains general macro and constants
 */

#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#define CFG_FRAMEWORK_NAME "chronovise"
#define CFG_FRAMEWORK_VERSION "0.1"

#ifdef GIT_VERSION
#define CFG_FRAMEWORK_GIT_VERSION GIT_VERSION
#else
#define CFG_FRAMEWORK_GIT_VERSION "unknown"
#endif

#ifdef VERBOSITY_NONE
#define VERB(x)
#else
#define VERB(x) x
#endif

#define UNUSED(x) ((void)x)

#define TEMPLATE_CLASS_IMPLEMENTATION(class_name) \
template class class_name<char, unsigned long>; \
template class class_name<int, unsigned long>; \
template class class_name<long, unsigned long>; \
template class class_name<float, unsigned long>; \
template class class_name<double, unsigned long>; \
template class class_name<unsigned char, unsigned long>; \
template class class_name<unsigned int, unsigned long>; \
template class class_name<unsigned long, unsigned long>; \
template class class_name<char, double>; \
template class class_name<int, double>; \
template class class_name<long, double>; \
template class class_name<float, double>; \
template class class_name<double, double>; \
template class class_name<unsigned char, double>; \
template class class_name<unsigned int, double>; \
template class class_name<unsigned long, double>



#endif
