#include "aec.hpp"
#include "global.hpp"
#include "utility/utility.hpp"

#include <cassert>
#include <iostream>
#include <iomanip>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_error(const std::string &s) {

	std::cerr << std::endl << "*** ERROR" << std::endl;
	std::cerr << "An error occurred, error description follows:" << std::endl;
	std::cerr << s << std::endl;

	std::cerr << std::endl << "*** STOP" << std::endl;

	std::abort();
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::check_preconditions() const noexcept {

	assert( input_gen     != nullptr && "You must call set_input_source() before run.");
	assert( evt_approach  != nullptr && "You must call set_evt_approach() before run.");
	assert( evt_estimator != nullptr && "You must call set_evt_estimator() before run.");
	assert( merger_tech   != merger_type_t::UNKNOWN && "You must call set_merging_technique() before run.");

}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::run() {

	exit_code_t ret;

	ret = this->onSetup();
	if (ret != AEC_OK) {
		print_error("onSetup() returns error code " + ret);
	}

	// Performs some checks that the user correctly set all member of the AEC class
	// It will fail with a assert-failure in case preconditions not respected.
	this->check_preconditions();

	VERB(utility::print_welcome_message());

	// This is the core of the estimation routine and represent the external cycle.
	// Please refer to diagram AD#1
	external_cycle();

	// If the user requeste the trace-merging technique, it means that we didn't perform
	// the estimation inside the cycle but we need to do that here.
	if (merger_tech == merger_type_t::TRACE_MERGE) {
		execute_analysis();
		measures.clear();
	}

	ret = this->onRelease();
	if (ret != AEC_OK) {
		print_error("onRelease() returns error code " + ret);
	}

	VERB(std::cerr << std::endl);
	
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::external_cycle() noexcept {

	bool require_more_samples = true;

	while (require_more_samples) {
		current_input = input_gen->get();

		exit_code_t ret = this->onConfigure();

		switch (ret) {
			case AEC_OK:
				// The use requested to stop the capture
				require_more_samples = false;
				// The safety of the estimation is not guaranteed in this case,
				// since we didn't perform any safety check
				estimation_safe_input = false;
			break;
			case AEC_CONTINUE:
				input_iteration++;
				internal_cycle();
			break;	
			case AEC_SLOTH:
				// TODO run representative tests
				// and accordingly set require_more_samples
				assert(false);	// Not currently implemented.
			default:
				print_error("onConfigure() returns error code " + ret);
			break;
		}
	}
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::internal_cycle() noexcept {

	exit_code_t ret;

	iteration = 0;

	bool keep_going = true;

	while(keep_going) {

		ret = this->onRun();
		if (ret != AEC_OK) {
			print_error("onRun() returns error code " + ret);
		}

		ret = this->onMonitor();

		switch(ret) {
			case AEC_CONTINUE:
			break;
			case AEC_OK:
				keep_going = false;
			break;
			case AEC_SLOTH:
				assert(min_nr_iteration > 0 && "You cannot use AEC_SLOTH without at least one test.");
				keep_going = iteration < min_nr_iteration;
			break;
			default:
				print_error("onMonitor() returns error code " + ret);
			break;
		}

		if (! keep_going) {
			// We may be here in two cases:
			// 1 - the onMonitor() returned AEC_OK
			// 2 - the onMonitor() returned AEC_SLOTH and sufficient number of iteration reached
			// Now, we have to continue to get sample only if we are not in AEC_OK case
			// and execute_analysis() failed.
			keep_going = execute_analysis() && (ret != AEC_OK); 
		}
		
		VERB(std::cerr << '.');
		iteration++;
	}

	// TODO Print X if a test failed
	VERB(std::cerr << '+');
}

template <typename T_INPUT, typename T_TIME>
bool AbstractExecutionContext<T_INPUT,T_TIME>::execute_analysis() noexcept {

	// Perform BM or POT based on what the user provided
	this->evt_approach->perform(measures);

	// Now measures represents the old pool of values. We now want to
	// get the new BM or POT pool.
	auto &measures_to_estimate = this->evt_approach->get_pool();

	// We can now estimated the EVT distribution...
	this->evt_estimator->run(measures_to_estimate);
	EV_Distribution evd = this->evt_estimator->get_result();

	// And then test it...
	for (auto &test : post_evt_tests) {
		test->set_ref_distribution(evd);
		// TODO

	}

	ev_dist_estimated.push_back(evd);

	return true;
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::set_min_iterations(test_ptr_t test) noexcept {
	if (this->reliability_req > 0) {
		if (test->has_power()) {
			this->min_nr_iteration = std::max(min_nr_iteration, test->get_minimal_sample_size(this->reliability_req));
			return;
		} else {
			this->estimation_safe = false;
		}
	}

	this->min_nr_iteration = std::max(min_nr_iteration, test->get_minimal_sample_size());
}

TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise

