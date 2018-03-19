#include "gtest/gtest.h"
#include "evt/evtapproach_bm.hpp"

using namespace chronovise;

#include <cmath>

// The fixture for testing class Project1. From google test primer.
class EVBM_Test : public ::testing::Test {
protected:


};

TEST_F(EVBM_Test, BMCheck) {

    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=100; i++) {
        source.push(1,i);
    }
    
    EVTApproach_BM<int, unsigned long> ebm(10);
    ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.5));

    auto &result = ebm.get_training_pool();

    ASSERT_EQ(result.size(), 5);

    int i=0;    
    for (auto it = result.cbegin(); it != result.cend(); it++, i++) {
        EXPECT_EQ(it->second, (i+1) * 10);
    }

}

TEST_F(EVBM_Test, BM_Exception1) {
    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=10; i++) {
        source.push(1,i);
    }
    
    EVTApproach_BM<int, unsigned long> ebm(10); // Requires 20 samples
    EXPECT_THROW(ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.5)), std::length_error);
    
}

TEST_F(EVBM_Test, BM_Exception2) {
    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=50; i++) {
        source.push(1,i);
    }
    
    EVTApproach_BM<int, unsigned long> ebm(10); // Requires 20 samples for both training and test
    EXPECT_THROW(ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.1)), std::length_error);
    
}

TEST_F(EVBM_Test, BMCheck_Incomplete) {

    MeasuresPool<int, unsigned long> source;

    for (int i=1; i<=95; i++) {
        source.push(1,i);
    }
    
    EVTApproach_BM<int, unsigned long> ebm(10);
    ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 0.5));

    auto &result = ebm.get_training_pool();

    ASSERT_EQ(result.size(), 5);

    int i=0;    
    for (auto it = result.cbegin(); it != result.cend(); it++, i++) {
        if (i != 4)
            EXPECT_EQ(it->second, (i+1) * 10);
        else
            EXPECT_EQ(it->second, 47);
    }

}
