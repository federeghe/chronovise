#ifndef SAMPLES_HELLO_WORLD_HPP_
#define SAMPLES_HELLO_WORLD_HPP_
#include "aec.hpp"
#include "measures_pool.hpp"
#include "timing.hpp"
#include "input/generator_uniform.hpp"

#include <iostream>

class HelloWorld : public AbstractExecutionContext {

public:
	HelloWorld() : input_gen(0,10) {

	}

	virtual exit_code_t onSetup() noexcept;
	virtual exit_code_t onConfigure() noexcept;
	virtual exit_code_t onRun() noexcept;
	virtual exit_code_t onMonitor() noexcept ;
	virtual exit_code_t onRelease() noexcept;

private:
	UniformInputGenerator<int> input_gen;
	MeasuresPool<int> measures;
	Timing timing;

	int current_input=0;

};

#endif
