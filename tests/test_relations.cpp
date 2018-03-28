#include "gtest/gtest.h"
#include "utility/relation_node.hpp"
#include "utility/relation_operator.hpp"

using namespace chronovise;

// The fixture for testing class Project1. From google test primer.
class Relations_Test : public ::testing::Test {
protected:


};

TEST_F(Relations_Test, TypePersistence) {

    RelationNode relnode(relation_node_t::TEST);

    EXPECT_EQ(relation_node_t::TEST, relnode.get_type());

    RelationNode relnode2(relation_node_t::OPERATOR);

    EXPECT_EQ(relation_node_t::OPERATOR, relnode2.get_type());

}

TEST_F(Relations_Test, Children) {

    std::unique_ptr<RelationNode> child1(new RelationNode(relation_node_t::TEST));
    std::unique_ptr<RelationNode> child2(new RelationNode(relation_node_t::TEST));
    std::unique_ptr<RelationNode> child3(new RelationNode(relation_node_t::TEST));

    std::unique_ptr<RelationNode> interm(new RelationNode(relation_node_t::OPERATOR));
    std::unique_ptr<RelationNode> root (new RelationNode(relation_node_t::OPERATOR));

    interm->add_child(child1);
    interm->add_child(child2);

    root->add_child(child3);
    root->add_child(interm);

    EXPECT_EQ(relation_node_t::TEST, (*root->cbegin())->get_type());

}

TEST_F(Relations_Test, Operator) {

    RelationNode *op = new RelationOperator(relation_operator_type_t::UNION);

    EXPECT_EQ(relation_node_t::OPERATOR, op->get_type());

    RelationOperator *oper = (RelationOperator*) op;

    EXPECT_EQ(relation_operator_type_t::UNION, oper->get_oper_type());

    delete op;
}


TEST_F(Relations_Test, Exceptions) {

    std::unique_ptr<RelationNode> child1(new RelationNode(relation_node_t::TEST));

    EXPECT_THROW(child1->add_child(child1) ,std::invalid_argument);

}
