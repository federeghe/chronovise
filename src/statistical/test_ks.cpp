#include "statistical/test_ks.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>
#include <limits>

namespace chronovise {

/** @private */
namespace local_test_ks {
	static double get_ks_critical_values(double alpha, unsigned long n) {
		return std::sqrt(-0.5 * std::log(alpha/2))/std::sqrt(n);
	}

	template <typename T_INPUT, typename T_TIME>
	static double empirical_F(const MeasuresPool<T_INPUT, T_TIME> &measures, double x) {
		const unsigned long n = measures.size();
		double curr_point = measures.min();

		unsigned long i=0;

		// TODO: Maybe we can cache these values to improve speed
		while(curr_point <= x) {
			i++;
			if (i >= n) break;
			curr_point = measures[i];
		} 

		double cumulative_F = ((double)i) / n;
		assert(cumulative_F >= 0. && cumulative_F <= 1.);
		return cumulative_F;
	}

}

template <typename T_INPUT, typename T_TIME>
void TestKS<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

	if(measures.size() < get_minimal_sample_size()) {
		throw std::invalid_argument("The number of samples is too low for this test.");
	}

	if(! this->ref_distribution) {
		throw std::invalid_argument("You must set a reference distribution for this test.");	
	}

	this->reject = false;

	using namespace local_test_ks;

	const unsigned long n = measures.size();
	const double critical_value = get_ks_critical_values(this->significance_level, n);

	/* **** Compute the empirical F(x) **** */
	const double min_meas = measures.min();
	const double max_meas = measures.max();
	const double step_f   = (max_meas - min_meas) / n;

	for (double x = min_meas; x <= max_meas; x += step_f) {
		double Fn = empirical_F(measures, x);
		double F = this->ref_distribution->cdf(x);

		if ( std::abs(F - Fn) > critical_value) {
			this->reject = true;
			break;
		}
	}

	// Now, we checked all the values that are in the domain of Fn, but we may miss
	// some values outside. So, just check (min_meas - epsilon) and (min_meas + epsilon)

	double min_epsilon = this->ref_distribution->cdf(min_meas - std::numeric_limits<double>::epsilon());
	double max_epsilon = 1. - this->ref_distribution->cdf(max_meas - std::numeric_limits<double>::epsilon());

	if ( min_epsilon > critical_value || max_epsilon > critical_value) {
		this->reject = true;
	}

}

template <typename T_INPUT, typename T_TIME>
bool TestKS<T_INPUT, T_TIME>::has_power() const noexcept
{
	if (this->distribution_type == distribution_t::EVT_GEV)
		return this->significance_level == 0.05 || this->significance_level == 0.01;

	return false;
}
template <typename T_INPUT, typename T_TIME>
bool TestKS<T_INPUT, T_TIME>::has_safe_power() const noexcept
{
	if (this->distribution_type == distribution_t::EVT_GEV) {
		auto ev_dist = std::dynamic_pointer_cast<GEV_Distribution>(this->ref_distribution);

		return has_power() && ev_dist->get_shape() != 0.0
			 	   && std::abs(ev_dist->get_shape()) < 0.5;
	}
	return false;

}

template <typename T_INPUT, typename T_TIME>
unsigned long TestKS<T_INPUT, T_TIME>::get_minimal_sample_size(unsigned short req_power) const {

// TODO Add citation

	if (! has_power()) {
		throw std::logic_error("Minimal sample size not available without power estimation routine.");
	}

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
