#include "safety.hpp"

#include "statistical/test.hpp"

#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>

namespace chronovise {

static double compute_reliability_node(std::shared_ptr<RelationNode> r) {

    //
    // WARNING
    // Recursive function
    //

    if(r->get_type() == relation_node_t::OPERATOR) {
        auto ro = std::dynamic_pointer_cast<RelationOperator>(r);
        assert(ro);

        // TODO check the statistical meaning of the next two formulas
        switch (ro->get_oper_type()) {
            case relation_operator_type_t::UNION:
                // In case of the union we apply the formula of 1-(1-a1)*(1-a2)*...
                return std::accumulate(ro->cbegin(), ro->cend(), 0,
                    [](double accumulate, std::shared_ptr<RelationNode> r_ptr) {
                        return 1 - (1 - accumulate) * (1 - compute_reliability_node(r_ptr));
                    }
                );
            case relation_operator_type_t::INTERSECT:
                return std::accumulate(ro->cbegin(), ro->cend(), 1.,
                    [](double accumulate, std::shared_ptr<RelationNode> r_ptr) {
                        return std::min(accumulate, compute_reliability_node(r_ptr));
                    }
                );
            default:
                throw std::runtime_error("An operator type is invalid.");
        }
    }

    if(r->get_type() == relation_node_t::TEST) {
        assert(r->get_local_size() == 0); // A test is always a leaf of the tree
        auto test = std::dynamic_pointer_cast<PowerEntity>(r);
        assert(test);

        if (!test->has_power()) {
            // We cannot compute it, so we assume zero power
            return 0.;
        }

        return test->get_power();
    }

    throw std::runtime_error("Unable to end a test type.");

}

double Safety::compute_reliability() const {

    if (test_tree_root == nullptr) {
        return -1.;
    }

    return compute_reliability_node(test_tree_root);

}

} // namespace chronovise
