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
	ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 1));

	auto &result = ebm.get_pool();

	ASSERT_EQ(result.size(), 10);

	int i=0;	
	for (auto it = result.cbegin(); it != result.cend(); it++, i++) {
		EXPECT_EQ(it->second, (i+1) * 10);
	}

}



TEST_F(EVBM_Test, BMCheck_Incomplete) {

	MeasuresPool<int, unsigned long> source;

	for (int i=1; i<=95; i++) {
		source.push(1,i);
	}
	
	EVTApproach_BM<int, unsigned long> ebm(10);
	ebm.perform(MeasuresPoolSet<int, unsigned long>(source, 1));

	auto &result = ebm.get_pool();

	ASSERT_EQ(result.size(), 10);

	int i=0;	
	for (auto it = result.cbegin(); it != result.cend(); it++, i++) {
		if (i != 9)
			EXPECT_EQ(it->second, (i+1) * 10);
		else
			EXPECT_EQ(it->second, 95);
	}

}
