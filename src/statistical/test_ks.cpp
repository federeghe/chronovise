#include "statistical/test_ks.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>

namespace chronovise {

/** @private */
namespace local_test_ks {
	static double get_ks_critical_values(double alpha, unsigned long n) {
		return std::sqrt(-0.5 * std::log(alpha/2))/std::sqrt(n);
	}

}

template <typename T_INPUT, typename T_TIME>
void TestKS<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

	assert(measures.size() > get_minimal_sample_size() );

	using namespace local_test_ks;

	const unsigned long n = measures.size();
	const double critical_value = get_ks_critical_values(this->significance_level, n);

	// Compute the 

	// Compute the empirical F(x)

}

template <typename T_INPUT, typename T_TIME>
unsigned long TestKS<T_INPUT, T_TIME>::get_minimal_sample_size(unsigned short req_power) const {

// TODO Add citation

	if (req_power == 0 || req_power > 9) {
		throw std::invalid_argument("Requested power with unsupported accuracy");
	}

	const double alpha = this->significance_level;

	if (alpha != 0.05 && alpha != 0.01) {
		throw std::logic_error("This test has no power estimation if alpha is not 0.01 or 0.05");
	}

	// The next switch is a worst-case for the three types distribution.
	switch(req_power) {
		case 1:
			return alpha == 0.05 ? 300 : 400;
		case 2:
			return alpha == 0.05 ? 400 : 750;
		case 3:
			return alpha == 0.05 ? 500 : 750;
		case 4: /*[[fallthrough]];*/
		case 5: /*[[fallthrough]];*/
		case 6: /*[[fallthrough]];*/
		case 7:
			return 750;
		case 8:
			return alpha == 0.05 ? 1000 : 2500;
		case 9:
			return 2500;
	}


#ifdef __GNUG__
	__builtin_unreachable();
#endif
	return 0;
}

TEMPLATE_CLASS_IMPLEMENTATION(TestKS);

} // namespace chronovise
