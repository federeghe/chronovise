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


#include "utility/relation_node.hpp"
#include <stdexcept>

namespace chronovise {

void RelationNode::add_child(std::shared_ptr<RelationNode> rn) {
    if (this->type == relation_node_t::TEST) {
        throw std::invalid_argument("A test cannot have children.");
    }
    this->children.push_back(rn);
}



size_t RelationNode::get_total_size() const noexcept {
    if (this->children.empty()) {
        return 0;
    }

    return std::accumulate(this->children.cbegin(), this->children.cend(),
        0,
        [](size_t accumulator, std::shared_ptr<RelationNode> n1){
            return accumulator + n1->get_total_size();
        });
}


} // namespace chronovise
