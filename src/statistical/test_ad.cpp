#include "statistical/test_ad.hpp"
#include "evt/ev_distribution.hpp"
#include "global.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>
#include <random>

namespace chronovise {

/** @private */
namespace local_test_ad {

/*
   *******************************************************************
   ******************** TEST STATISTIC CALCULATION *******************
   *******************************************************************
*/

	template<typename T_TIME>
	static inline double get_ad_statistic_upper(std::shared_ptr<Distribution> evd,
						const std::vector<T_TIME> &measures) noexcept {

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

	template<typename T_TIME>
	static inline double get_ad_statistic_lower(std::shared_ptr<Distribution> evd, 
						const std::vector<T_TIME> &measures) noexcept {

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

	template<typename T_TIME>
	static inline double get_ad_statistic(std::shared_ptr<Distribution> evd, const std::vector<T_TIME> &measures) noexcept {
		double upper = get_ad_statistic_upper(evd, measures);
		double lower = get_ad_statistic_lower(evd, measures);

		return upper + lower;
	}

/*
   *******************************************************************
   ******************** CRITICAL VALUE CALCULATION *******************
   *******************************************************************
*/

	static inline double get_ad_critical_value(std::shared_ptr<Distribution> evd, bool MAD,
				size_t sample_cardinality, double significance_level) noexcept {

		constexpr unsigned int nr_runs = 1000U;

		std::vector<double> crits;
		crits.resize(nr_runs);

		std::vector<double> sample;
		sample.reserve(sample_cardinality);

		std::mt19937 random_gen(std::random_device{}());
		std::uniform_real_distribution<double> distribution(0.0,1.0);

		for (unsigned long i=0; i < nr_runs; i++) {

			for (unsigned int j=0; j < sample_cardinality; j++) {
				// Inverse transform sampling
				sample.push_back(evd->quantile(distribution(random_gen)));
			}

			std::sort(sample.begin(), sample.end());

			if (MAD) {
				crits[i] = get_ad_statistic_upper(evd, sample);
			} else {
				crits[i] = get_ad_statistic(evd, sample);
			}
		}

		std::sort(crits.begin(),crits.end());


		return crits[(int)(significance_level * nr_runs)];
	}	

}

template <typename T_INPUT, typename T_TIME>
void TestAD<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

	const size_t size = measures.size();

	if(size < get_minimal_sample_size()) {
		throw std::invalid_argument("The number of samples is too low for this test.");
	}

	if(! this->ref_distribution) {
		throw std::invalid_argument("You must set a reference distribution for this test.");	
	}

	this->reject = false;

	using namespace local_test_ad;

	// TODO
	double ad_critical_value = (1. + safe_margin) *
					get_ad_critical_value(this->ref_distribution,
								MAD, size, this->significance_level);

	// Using MeasuresPool, the [] operator guarantees ordering.
	double statistics = get_ad_statistic<T_TIME>(this->ref_distribution, measures.get_ordered_vector());

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
