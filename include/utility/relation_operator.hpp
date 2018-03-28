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
 * @file utility/relation_operators.hpp
 * @author Check commit authors
 * @brief File containing the RelationOperator classes
 */

#ifndef UTILITY_RELATION_OPERATOR_HPP_
#define UTILITY_RELATION_OPERATOR_HPP_

#include "utility/relation_node.hpp"

namespace chronovise {

typedef enum class relation_operator_type_e {

    UKNOWN,   /** Error value, it should not be used */
    UNION,    /** Logical union operator */
    INTERSECT,/** Logical intersect operator */

} relation_operator_type_t;

class RelationOperator : public RelationNode {

public:
    RelationOperator(relation_operator_type_t type) :
        RelationNode(relation_node_t::OPERATOR), type(type)
    {
    }

    virtual ~RelationOperator()
    {
    }

    relation_operator_type_t get_oper_type() const noexcept {
        return this->type;
    }

private:
    relation_operator_type_t type;

};

} // namespace chronovise

#endif
