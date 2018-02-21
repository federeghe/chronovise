#include "statistical/test_ljung_box.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>
#include <limits>

namespace chronovise {

/** @private */
namespace local_test_ljung_box {
	static double get_lb_critical_values(double alpha, unsigned long n) {
	}
}

template <typename T_INPUT, typename T_TIME>
void TestLjungBox<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

	if(measures.size() < get_minimal_sample_size()) {
		throw std::invalid_argument("The number of samples is too low for this test");
	}

	

}

TEMPLATE_CLASS_IMPLEMENTATION(TestLjungBox);

} // namespace chronovise
