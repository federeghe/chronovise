/*
 *  chronovise - Copyright 2018 Politecnico di Milano
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file aec.hpp
 * @author Check commit authors
 * @brief File containing the AbstractExecutionContext class
 */

#ifndef AEC_HPP_
#define AEC_HPP_

#include "evt/evtapproach.hpp"
#include "evt/pwcet.hpp"
#include "fixer.hpp"
#include "global.hpp"
#include "input/generator.hpp"
#include "measures_pool.hpp"
#include "safety.hpp"
#include "statistical/test.hpp"
#include "statistical/estimator.hpp"
#include "utility/utility.hpp"

#include <list>
#include <memory>
#include <string>

namespace chronovise {

/**
 * Represents the list of available merger type of the EVT process. It is basically
 * composed of two possible strategies: trace-merging or envelope-merging. The
 * former merge all the measurements from different input dataset into one single
 * dataset to be analyzed. The latter computes pWCET for each input and provides
 * a merge of pWCET at the end. 
 */
typedef enum class merger_type_e {
	UNKNOWN,	/** Internal representation, should not be used */
	TRACE_MERGE,	/** Trace-merging technique */
	ENVELOPE	/** Envelope-merging technique */
} merger_type_t;


/**
 * The abstract class to be extended by the application. It is often shorten in the
 * documentation with AEC acronym (AbstractExecutionContext).
 */
template <typename T_INPUT=unsigned long, typename T_TIME=unsigned long>
class AbstractExecutionContext {

public:

	explicit AbstractExecutionContext() {
		VERB(utility::print_welcome_message());
	}

	virtual ~AbstractExecutionContext() = default;

	/**
	 * The list of possible exit status codes. It is used by AEC-implemented methods
	 * and must be used by children classes.
	 */
	typedef enum {

		// Normal statuses
		AEC_OK = 0,	/** `Successful` or `completed` meaning */
		AEC_CONTINUE,	/** Instructs the framework to continue an action */
		AEC_SLOTH,	/** Instructs the framework to decide itself something*/

		// Error statuses
		AEC_GENERIC_ERROR,	/** Generic error code */ 

	} exit_code_t;


	virtual exit_code_t onSetup() = 0;
	virtual exit_code_t onConfigure() = 0;
	virtual exit_code_t onRun() = 0;
	virtual exit_code_t onMonitor() = 0;
	virtual exit_code_t onRelease() = 0;

	/**
	 * The list of possible exit status codes. It is used by AEC-implemented methods
	 * and must be used by children classes. If something fails it may throw exception
	 * or abort the program.
	 * @throws std::runtime_error in case of some failures or abort the program
	 * immediately
	 */
	void run();

	/**
	 * Print the distribution summary. It must be called at the end of execution,
	 * otherwise no output is provided.
	 * @note For some merging technique like trace-merge, it provides only a single
	 * value. 
	 */
	void print_distributions_summary() const noexcept;

	/**
	 * Print the configuration information of AEC such as tests, evt approach, etc.
	 */	
	void print_configuration_info() const noexcept;

	void print_wcots() const noexcept;

	T_TIME get_pwcet_wcet(double probability) const noexcept {
		std::list<pWCET<T_TIME>> pwcets;
		for (const auto & evd : ev_dist_estimated) {	
			pwcets.push_back(evd);
		}
		return pWCET<T_TIME>::get_cumulative_wcet(pwcets, probability);
	}

	double get_pwcet_probability(T_TIME wcet) const noexcept {
		std::list<pWCET<T_TIME>> pwcets;
		for (const auto & evd : ev_dist_estimated) {	
			pwcets.push_back(evd);
		}
		return pWCET<T_TIME>::get_cumulative_probability(pwcets, wcet);
	}

	inline const Safety& get_safety_info() const noexcept {
		return this->safety;
	}


protected:

	inline void set_input_source(std::unique_ptr<InputGenerator<T_INPUT>> ig) noexcept {
		this->input_gen = std::move(ig);
	}

	inline void set_merging_technique(merger_type_t type) noexcept {
		this->merger_tech = type;
	}

	/**
	 * Configure the approach to use to split and/or select samples.
	 * @param evt_approach The pointer to the class performing the splitting/selecting approach
	 * @param samples_test_reserve The percentage of samples to be reserved for testing expressed
	 *	  as a number from 0 to 1. Values near 0 reduces the test power. Values near 1 reduces
	 * 	  the estimation precision (and it may consequently lead to a test failure).
	 */
	void set_evt_approach(std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach,
					float samples_test_reserve=0.) noexcept;

	inline void set_evt_estimator(std::unique_ptr<Estimator<T_INPUT, T_TIME>> est) noexcept {
		this->evt_estimator = std::move(est);
	}

	inline void add_sample(T_TIME value) noexcept {
		this->measures.push(current_input, value);
	}

	inline void add_input_transformer() noexcept;

	typedef std::shared_ptr<StatisticalTest<T_INPUT,T_TIME>> test_ptr_t;
	typedef std::shared_ptr<StatisticalTest_AfterEVT<T_INPUT, T_TIME>> test_aft_ptr_t;

	inline void add_input_representativity_test(test_ptr_t st) noexcept {
		this->representativity_tests.push_back(st);
	}

	/**
	 * Tests executed on post EVT-approach samples (e.g. on the output samples of BM)
	 */
	inline void add_post_approach_test(test_ptr_t st) noexcept {
		this->post_run_tests.push_back(std::move(st));
	}

	/**
	 * Tests executed on pre EVT-approach samples (e.g. on the output samples of BM)
	 */
	inline void add_sample_test(test_ptr_t st) noexcept {
		this->sample_tests.push_back(std::move(st));
	}

	inline void add_post_evt_test(test_aft_ptr_t st) noexcept {
		this->post_evt_tests.push_back(std::move(st));
	}

	inline T_INPUT get_current_input_value() const noexcept {
		return this->current_input;
	}

	inline unsigned long get_input_iteration() const noexcept {
		return input_iteration;
	}

	inline unsigned long get_iteration() const noexcept {
		return iteration;
	}

	inline void set_reliability_requirement(double req) noexcept {
		safety.set_reliability_requirement(req);
	}

private:

	/* *** PRIVATE TYPES *** */
	typedef std::list<test_ptr_t> list_of_test_t;
	typedef std::list<test_aft_ptr_t> list_of_aft_test_t;


	/* *** ATTRIBUTES - CONFIGURATION *** */
	float samples_test_reserve = 0; /** 0-1: ratio of samples reserved for testing */

	merger_type_t merger_tech = merger_type_t::UNKNOWN;

	std::unique_ptr<InputGenerator<T_INPUT>> input_gen;
	std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach;
	std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_estimator;

	list_of_test_t representativity_tests;
	list_of_test_t sample_tests;
	list_of_test_t post_run_tests;
	list_of_aft_test_t post_evt_tests;

	/* *** ATTRIBUTES - RUNTIME *** */

	unsigned long input_iteration  = 0;
	unsigned long iteration        = 0;
	unsigned long min_nr_iterations_train = 0;
	unsigned long min_nr_iterations_tests = 0;
	unsigned long min_nr_iterations_total = 0;

	T_INPUT current_input;

	MeasuresPool<T_INPUT, T_TIME> measures;
	MeasuresPool<T_INPUT, T_TIME> wcots;
	std::list<EV_Distribution> ev_dist_estimated;

	Safety safety;

	/* *** METHODS *** */

	[[noreturn]] inline void print_error(const std::string &s) const {
		throw std::runtime_error("An error occurred, error description follows: "+s);
	}

	void external_cycle();

	void internal_cycle();

	aec_status_t execute_analysis() noexcept;

	void check_preconditions() const noexcept;

	void set_min_iterations() noexcept;

};

} // namespace chronovise
#endif
