#include "statistical/test_ad.hpp"
#include "evt/ev_distribution.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

namespace chronovise {

/** @private */
namespace local_test_ad {

	template<typename T_INPUT, typename T_TIME>
	static inline double get_ad_statistic_upper(std::shared_ptr<Distribution> evd, const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

		size_t cardinality = measures.size();
		double S1=0.0, S2=0.0;

		for (unsigned int i=0; i < cardinality; i++) {
			double coeff1 = (2. - ((2.*((int)i+1.) - 1.) / ((double)cardinality)) );
			double Fi = evd->cdf(measures[i]);

			// This is an extreme case, the distribution is completely
			// wrong probably. This may be too pessimistic, but safe.
			if (Fi == 1.) return std::numeric_limits<double>::infinity();

			S1 += Fi;
			S2 += coeff1 * std::log(1. - Fi);
		}

		S1 *= 2.0;

		return (double)cardinality / 2 - S1 - S2;
	}

	template<typename T_INPUT, typename T_TIME>
	static inline double get_ad_statistic_lower(std::shared_ptr<Distribution> evd, const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

		size_t cardinality = measures.size();
		double S1=0.0, S2=0.0;

		for (unsigned int i=0; i < cardinality; i++) {
			double coeff2 = (((2.*((int)i+1) - 1.) / ((double)cardinality)) );
			double Fi = evd->cdf(measures[i]);

			// This is an extreme case, the distribution is completely
			// wrong probably. This may be too pessimistic, but safe.
			if (Fi == 0.) return std::numeric_limits<double>::infinity();

			S1 += Fi;
			S2 += coeff2 * std::log(Fi);

		}

		S1 *= 2.0;

		return - 3 * (double)cardinality / 2 + S1 - S2;
	}

	template<typename T_INPUT, typename T_TIME>
	static inline double get_ad_statistic(std::shared_ptr<Distribution> evd, const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {
		double upper = get_ad_statistic_upper(evd, measures);
		double lower = get_ad_statistic_lower(evd, measures);

		return upper + lower;
	}


}

template <typename T_INPUT, typename T_TIME>
void TestAD<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

	if(measures.size() < get_minimal_sample_size()) {
		throw std::invalid_argument("The number of samples is too low for this test.");
	}

	if(! this->ref_distribution) {
		throw std::invalid_argument("You must set a reference distribution for this test.");	
	}

	this->reject = false;

	using namespace local_test_ad;

	// TODO
	double ad_critical_value = (1. + safe_margin); // * AndersonDarlingCV::get_critical_value(config::sample_cardinality, evt_param);

	// Using MeasuresPool, the [] operator guarantees ordering.
	double statistics = get_ad_statistic(this->ref_distribution, measures);

	if (statistics > ad_critical_value) {
		this->reject = true;
	}
}

template <typename T_INPUT, typename T_TIME>
bool TestAD<T_INPUT, T_TIME>::has_power() const noexcept
{
	// TODO
	return false;
}
template <typename T_INPUT, typename T_TIME>
bool TestAD<T_INPUT, T_TIME>::has_safe_power() const noexcept
{
	// TODO
	return false;
}

template <typename T_INPUT, typename T_TIME>
unsigned long TestAD<T_INPUT, T_TIME>::get_minimal_sample_size(unsigned short req_power) const {

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

	}


#ifdef __GNUG__
	__builtin_unreachable();
#endif
	return 0;
}

TEMPLATE_CLASS_IMPLEMENTATION(TestAD);

} // namespace chronovise
