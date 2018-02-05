#ifndef AEC_HPP_
#define AEC_HPP_
#include "measures_pool.hpp"

#include "evt/evtapproach.hpp"
#include "input/generator.hpp"
#include "mergers/merger.hpp"
#include "statistical/test.hpp"

#include <list>
#include <memory>
#include <string>

template <typename T_INPUT=unsigned long, typename T_TIME=unsigned long>
class AbstractExecutionContext {

public:

	virtual ~AbstractExecutionContext() = default;

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

	void run() noexcept;

protected:

	inline void set_input_source(std::unique_ptr<InputGenerator<T_INPUT>> ig) noexcept {
		this->input_gen = std::move(ig);
	}

	inline void set_merging_technique(std::unique_ptr<Merger<T_INPUT, T_TIME>> merger) noexcept {
		this->merger = std::move(merger);
	}

	inline void set_evt_approach(std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach) noexcept {
		this->evt_approach = std::move(evt_approach);
	}


	inline void add_sample(T_TIME value) noexcept {
		this->measures.push(current_input, value);
	}

	inline void add_input_transformer() noexcept;

	typedef std::unique_ptr<StatisticalTest<T_TIME>> test_ptr_t;

	inline void add_input_representativity_test(test_ptr_t st) noexcept {
		this->representativity_tests.push_back(std::move(st));
	}

	inline void add_post_run_test(test_ptr_t st) noexcept {
		this->post_run_tests.push_back(std::move(st));
	}

	inline void add_post_evt_test(test_ptr_t st) noexcept {
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


	std::unique_ptr<InputGenerator<T_INPUT>> input_gen;
	std::unique_ptr<Merger<T_INPUT, T_TIME>> merger;
	std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_approach;

	MeasuresPool<T_INPUT, T_TIME> measures;

	typedef std::list<std::unique_ptr<StatisticalTest<T_TIME>>> list_of_test_t;
	list_of_test_t representativity_tests;
	list_of_test_t post_run_tests;
	list_of_test_t post_evt_tests;

	void print_error(const std::string &s);

	void internal_cycle() noexcept;

};

#endif
