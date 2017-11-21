#ifndef SAMPLES_HELLO_WORLD_HPP_
#define SAMPLES_HELLO_WORLD_HPP_
#include "aec.hpp"
#include "measures_pool.hpp"
#include "timing.hpp"
#include "input/generator_uniform.hpp"

#include <iostream>

class HelloWorld : public AbstractExecutionContext {

public:
	int my_testing_function(int x) {
		volatile int i, a;
		for (i=0; i < x * x * 1000000; i++) {
			a = i;
		}
		return a;
	}

	HelloWorld() : input_gen(0,10) {

	}

	virtual exit_code_t onSetup() noexcept {
		return AEC_OK;
	}

	virtual exit_code_t onConfigure() noexcept
	{
		current_input = input_gen.get();
		return AEC_OK;
	}

	virtual exit_code_t onRun() noexcept {

		timing.start_timing();
		my_testing_function(current_input);
		timing.stop_timing();

		measures.push(timing.get_ns());
		return AEC_OK;
	}

	virtual exit_code_t onMonitor() noexcept {

		if (this->get_iteration() < 10) {
			return AEC_CONTINUE;
		} else {
			return AEC_OK;
		}
	}

	virtual exit_code_t onRelease() noexcept {

		std::cout << "Max value: " << measures.max() << std::endl;

		return AEC_OK;
	}


private:
	UniformInputGenerator<int> input_gen;
	MeasuresPool<> measures;
	Timing timing;

	int current_input=0;

};

#endif
