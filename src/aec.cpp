#include "aec.hpp"
#include "global.hpp"
#include "utility/utility.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>

namespace chronovise {

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

	// Configure the minimal number of iterations given by tests.
	this->set_min_iterations();

	// This is the core of the estimation routine and represent the external cycle.
	// Please refer to diagram AD#1
	external_cycle();

	// If the user requeste the trace-merging technique, it means that we didn't perform
	// the estimation inside the cycle but we need to do that here.
	if (merger_tech == merger_type_t::TRACE_MERGE) {
		execute_analysis();
	}

	ret = this->onRelease();
	if (ret != AEC_OK) {
		print_error("onRelease() returns error code " + ret);
	}

	VERB(std::cerr << std::endl);
	
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::external_cycle() {

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
				print_error("onConfigure() returns error code " + std::to_string(ret));
			break;
		}
	}
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::internal_cycle() {

	exit_code_t ret;

	iteration = 0;

	bool keep_going = true;

	while(keep_going) {

		ret = this->onRun();
		if (ret != AEC_OK) {
			print_error("onRun() returns error code " + std::to_string(ret));
		}

		ret = this->onMonitor();

		switch(ret) {
			case AEC_CONTINUE:
			break;
			case AEC_OK:
				keep_going = false;
			break;
			case AEC_SLOTH:

				assert(min_nr_iterations_train > 0 &&
						"Selected EVT approach does not allow AEC_SLOTH.");
				assert(min_nr_iterations_tests > 0 &&
						"You cannot use AEC_SLOTH without at least one test.");

				keep_going = iteration < min_nr_iterations_total;
			break;
			default:
				print_error("onMonitor() returns error code " + std::to_string(ret));
			break;
		}

		if (! keep_going) {
			// We may be here in two cases:
			// 1 - the onMonitor() returned AEC_OK
			// 2 - the onMonitor() returned AEC_SLOTH and sufficient number of iteration reached
			// Now, we have to continue to get sample only if we are not in AEC_OK case
			// and execute_analysis() failed.
			auto ret_analysis = execute_analysis();
			keep_going = !(ret_analysis == internal_status_t::OK) && (ret != AEC_OK);

			switch(ret_analysis) {
				case internal_status_t::REJECT_SAMPLE_TEST:
					VERB(std::cerr << '$');
				return;
				case internal_status_t::FAIL_EVT_ESTIMATOR:
					VERB(std::cerr << '#');
				return;
				case internal_status_t::REJECT_POST_EVT_TEST:
					VERB(std::cerr << 'X');
				break;
				default:
				break;
			}
		}
		
		VERB(std::cerr << '.');
		iteration++;
	}

	VERB(std::cerr << '+');
}

template <typename T_INPUT, typename T_TIME>
typename AbstractExecutionContext<T_INPUT,T_TIME>::internal_status_t
AbstractExecutionContext<T_INPUT,T_TIME>::execute_analysis() noexcept {

	// Create a pool set to manage training e test
	MeasuresPoolSet<T_INPUT, T_TIME> mps(this->measures, 1.-samples_test_reserve);


	for (auto &test : sample_tests) {
		test->run(measures);
		if (test->is_reject()) {
			return internal_status_t::REJECT_SAMPLE_TEST;
		}
	}

	// Perform BM or POT based on what the user provided
	this->evt_approach->perform(mps);

	// Now measures represents the old pool of values. We now want to
	// get the new BM or POT pool.
	const auto &measures_to_estimate = this->evt_approach->get_training_pool();
	const auto &measures_test = this->evt_approach->get_test_pool();

	if (measures_to_estimate.size() < this->evt_estimator->get_minimal_sample_size()) {
		min_nr_iterations_total *= 2;
		return internal_status_t::FAIL_EVT_APP_MIN_SAMPLE_SIZE;
	}

	auto lambda_check = [&measures_test](const auto &test) {
		return measures_test.size() < test->get_minimal_sample_size();
	};

	if (std::any_of(post_run_tests.cbegin(), post_run_tests.cend(), lambda_check)) {
		min_nr_iterations_total *= 2;
		return internal_status_t::FAIL_POST_RUN_TEST_SAMPLE_SIZE;
	}

	if (std::any_of(post_evt_tests.cbegin(), post_evt_tests.cend(), lambda_check)) {
		min_nr_iterations_total *= 2;
		return internal_status_t::FAIL_POST_EVT_TEST_SAMPLE_SIZE;
	}

	// We can now estimated the EVT distribution...
	this->evt_estimator->run(measures_to_estimate);

	if (this->evt_estimator->get_status() != estimator_status_t::SUCCESS) {
		// TODO: Handle other result values
		return internal_status_t::FAIL_EVT_ESTIMATOR;
	}

	EV_Distribution evd = this->evt_estimator->get_result();

	auto ev_ref_shared = std::shared_ptr<Distribution>(&evd,[](auto* p){UNUSED(p);});

	// And then test it...
	for (auto &test : post_evt_tests) {
		test->set_ref_distribution(ev_ref_shared);
		test->run(measures_test);
		if (test->is_reject()) {
			min_nr_iterations_total *= 2;	// Maybe a smart thing?
			return internal_status_t::REJECT_POST_EVT_TEST;
		}
	}

	ev_dist_estimated.push_back(evd);
	measures.clear();

	return internal_status_t::OK;
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::set_min_iterations() noexcept {

	// Calculate the minimum number of iterations is a bit tricky.

	// First of all, the number of samples for the training set is defined by the EVT approach
	// used. E.g. BM method must guarantee at least 2 blocks.
	this->min_nr_iterations_train = this->evt_approach->get_minimal_sample_size();

	this->min_nr_iterations_tests = 0;

	// The minimal number of tests depends obviously on used tests and if a reliability requirement
	// is provided or not.
	if (this->reliability_req > 0) {

		// Check if the tests have all of them the power estimation routine.
		auto lambda_power = [](const auto &x){return !x->has_power();};
		bool any_without_power =
		std::any_of(	sample_tests.cbegin(),
				sample_tests.cend(),
				lambda_power
		)
		||
		std::any_of(	post_run_tests.cbegin(),
				post_run_tests.cend(),
				lambda_power
		)
		||
		std::any_of(	post_evt_tests.cbegin(),
				post_evt_tests.cend(),
				lambda_power
		);

		//  If the power estimation routine is not present for at least one test we have to
		// consider the estimation unsafe
		if (any_without_power) {
			this->estimation_safe = false;
		} else {
			// Otherwise we can calculate the minimal number of samples from the maximum
			// of them
			unsigned long min_iter = 0;
			float rel_req = this->reliability_req;
			auto lambda_max = [&min_iter, rel_req](const auto &test) {
				min_iter = std::max(min_iter, test->get_minimal_sample_size(rel_req));
			};

			std::for_each(sample_tests.cbegin(), sample_tests.cend(), lambda_max); 
			std::for_each(post_run_tests.cbegin(), post_run_tests.cend(), lambda_max); 
			std::for_each(post_evt_tests.cbegin(), post_evt_tests.cend(), lambda_max); 

			this->min_nr_iterations_tests = min_iter;
		}

	}

	// If the reliability is not enable or not all the tests has the power estimation routine,
	// let's use the minimal value to run tests
	if (this->min_nr_iterations_tests == 0) {
		unsigned long min_iter = 0;
		auto lambda_max = [&min_iter](const auto &test) {
			min_iter = std::max(min_iter, test->get_minimal_sample_size());
		};
		std::for_each(sample_tests.cbegin(), sample_tests.cend(), lambda_max); 
		std::for_each(post_run_tests.cbegin(), post_run_tests.cend(), lambda_max); 
		std::for_each(post_evt_tests.cbegin(), post_evt_tests.cend(), lambda_max); 

		this->min_nr_iterations_tests = min_iter;
	}

	// Now: since the minimal number of samples per test may be less than the required for BM
	// (or any other EVT approach), we have to compute it considering the size of the BM output
	this->min_nr_iterations_tests = std::max(this->min_nr_iterations_tests, this->min_nr_iterations_train);

	// At last, the training set and test set is divided by the ratio samples_test_reserve, so
	// let's compute the total number.
	this->min_nr_iterations_total = std::ceil(
					std::max(this->min_nr_iterations_tests / samples_test_reserve, 
					this->min_nr_iterations_train / (1 - samples_test_reserve))
					);

}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::set_evt_approach(std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach,
				float samples_test_reserve) noexcept {
	assert(samples_test_reserve >= 0. && samples_test_reserve <= 1.);
	this->evt_approach = std::move(evt_approach);
	this->samples_test_reserve = samples_test_reserve;
}


TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise

