#include "gtest/gtest.h"
#include "evt/evtapproach_pot.hpp"

using namespace chronovise;

#include <cmath>

// The fixture for testing class Project1. From google test primer.
class EVPoT_Test : public ::testing::Test {
protected:


};

TEST_F(EVPoT_Test, PoTCheck) {

    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    
    EVTApproach_PoT<int, unsigned long> ebm(50);
    ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.5));

    auto &result = ebm.get_training_pool();

    ASSERT_EQ(result.size(), 50);

    int i=51;
    for (auto it = result.cbegin(); it != result.cend(); it++, i++) {
        ASSERT_EQ(it->second, i);
    }

}

TEST_F(EVPoT_Test, PoTCheck_Testset) {
    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    
    EVTApproach_PoT<int, unsigned long> ebm(50);
    ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.5));

    auto &result = ebm.get_test_pool();

    ASSERT_EQ(result.size(), 50);

    int i=51;
    for (auto it = result.cbegin(); it != result.cend(); it++, i++) {
        ASSERT_EQ(it->second, i);
    }


}

TEST_F(EVPoT_Test, PoT_NoSurvivors) {

    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    
    EVTApproach_PoT<int, unsigned long> ebm(150);
    EXPECT_THROW(ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.5)), std::length_error);

}
