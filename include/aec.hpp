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
#include "measures_pool.hpp"

#include "evt/evtapproach.hpp"
#include "input/generator.hpp"
#include "statistical/test.hpp"
#include "statistical/estimator.hpp"

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
 * documentation with AEC acronym.
 */
template <typename T_INPUT=unsigned long, typename T_TIME=unsigned long>
class AbstractExecutionContext {

public:

	virtual ~AbstractExecutionContext() = default;

	/**
	 * The list of possible exit status codes. It is used by AEC-implemented methods
	 * and must be used by children classes.
	 */
	typedef enum {

		// Normal statuses
		AEC_OK = 0,
		AEC_CONTINUE,
		AEC_STOP,

		// Error statuses
		AEC_GENERIC_ERROR,

	} exit_code_t;


	virtual exit_code_t onSetup() noexcept = 0;
	virtual exit_code_t onConfigure() noexcept = 0;
	virtual exit_code_t onRun() noexcept = 0;
	virtual exit_code_t onMonitor() noexcept = 0;
	virtual exit_code_t onRelease() noexcept = 0;

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

protected:

	inline void set_input_source(std::unique_ptr<InputGenerator<T_INPUT>> ig) noexcept {
		this->input_gen = std::move(ig);
	}

	inline void set_merging_technique(merger_type_t type) noexcept {
		this->merger_tech = type;
	}

	inline void set_evt_approach(std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach) noexcept {
		this->evt_approach = std::move(evt_approach);
	}

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
		this->representativity_tests.push_back(std::move(st));
	}

	inline void add_post_run_test(test_ptr_t st) noexcept {
		this->post_run_tests.push_back(std::move(st));
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

private:

	unsigned long input_iteration = 0;
	unsigned long iteration = 0;
	T_INPUT current_input;

	merger_type_t merger_tech = merger_type_t::UNKNOWN;

	std::unique_ptr<InputGenerator<T_INPUT>> input_gen;
	std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach;
	std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_estimator;

	MeasuresPool<T_INPUT, T_TIME> measures;

	typedef std::list<test_ptr_t> list_of_test_t;
	typedef std::list<test_aft_ptr_t> list_of_aft_test_t;
	list_of_test_t representativity_tests;
	list_of_test_t post_run_tests;
	list_of_aft_test_t post_evt_tests;

	std::list<EV_Distribution> ev_dist_estimated;

	void print_error(const std::string &s);

	void internal_cycle() noexcept;

	void execute_analysis() noexcept;

	void check_preconditions() const noexcept;

};

} // namespace chronovise
#endif
