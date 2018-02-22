#include "aec.hpp"
#include "global.hpp"
#include "utility/utility.hpp"
#include <iostream>
#include <iomanip>
#include <string>

namespace chronovise {


template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_distributions_summary() const noexcept {

	std::cerr << std::endl;
	utility::print_title("Distributions summary");

	std::cerr << "| Legend: G - Gumbell, W - Weibull, F - Frechet" << std::endl;

	size_t i=0;
	for (auto it=ev_dist_estimated.cbegin(); it != ev_dist_estimated.cend(); it++, i++) {
		std::cerr << '#'  << std::setw(4) << i << ": "
			  << "location=" << std::setw(12) << it->get_location()
			  << "  scale=" << std::setw(12) << it->get_scale()
			  << "  shape=" << std::setw(12) << it->get_shape() << " ["
			  << (it->is_gumbell() ? 'G' : it->is_frechet() ? 'F' : 'W') << "]";

		std::cerr << std::endl;
	}
	std::cerr << std::endl;

}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_configuration_info() const noexcept {

	utility::print_title("Configuration info");

	if (reliability_req) {
		std::cerr << "Reliability requirement: " << reliability_req  << std::endl;
	} else {
		std::cerr << "Reliability requirement: NOT SET" << std::endl;

	}
	std::cerr << "Ratio size test set / total samples: " << samples_test_reserve << std::endl;
	std::cerr << "Merging technique: " << (merger_tech == merger_type_t::TRACE_MERGE ? "TRACE_MERGE" 
					     : merger_tech == merger_type_t::ENVELOPE ? "ENVELOPE"
					     : "UNKNOWN") << std::endl;

	std::cerr << "Input generator: " << (input_gen == nullptr ? "NOT SET" : "SET") << std::endl;
	std::cerr << "EVT approach: " << (evt_approach == nullptr ? "NOT SET" : "SET") << std::endl;
	std::cerr << "EVT estimator: " << (evt_estimator == nullptr ? "NOT SET" : "SET") << std::endl;

	std::cerr << "Nr. Representativity tests: " << representativity_tests.size() << std::endl;
	std::cerr << "Nr. post-run tests: " << post_run_tests.size() << std::endl;
	std::cerr << "Nr. post-evt tests (goodnes-of-fit): " << post_evt_tests.size() << std::endl;

}


TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise

