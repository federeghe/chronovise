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
 * @file utility/relation_node.hpp
 * @author Check commit authors
 * @brief File containing the RelationNode and related classes/types
 */

#ifndef UTILITY_RELATION_NODE_HPP_
#define UTILITY_RELATION_NODE_HPP_

#include <list>
#include <memory>

namespace chronovise {

typedef enum class relation_node_e {

    UKNOWN,   /** Error value, it should not be used */
    TEST,     /** Statistical test */
    OPERATOR, /** Operator */

} relation_node_t;

class RelationNode {

public:
    RelationNode(relation_node_t type) : type(type)
    {
    }

    virtual ~RelationNode()
    {
    }

    relation_node_t get_type() const noexcept { return this->type; }

    void add_child(std::unique_ptr<RelationNode> &rn) {
        if (this->type == relation_node_t::TEST) {
            throw std::invalid_argument("A test cannot have children.");
        }
        this->children.push_back(std::move(rn));
    }

    std::list<std::unique_ptr<RelationNode>>::const_iterator cbegin() const noexcept {
        return this->children.cbegin();
    }

    std::list<std::unique_ptr<RelationNode>>::const_iterator cend() const noexcept {
        return this->children.cend();
    }

    const std::list<std::unique_ptr<RelationNode>> & get_children() const noexcept {
        return this->children;
    }

private:
    relation_node_t type;

    std::list<std::unique_ptr<RelationNode>> children;
};

} // namespace chronovise


#endif
