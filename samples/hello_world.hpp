#ifndef SAMPLES_HELLO_WORLD_HPP_
#define SAMPLES_HELLO_WORLD_HPP_
#include "aec.hpp"
#include "measures_pool.hpp"
#include "timing.hpp"
#include "input/generator_uniform.hpp"

#include <iostream>

class HelloWorld : public chronovise::AbstractExecutionContext<unsigned int> {

public:
	HelloWorld() : uniform_input_dist(
		new chronovise::UniformInputGenerator<unsigned int>(0,100000)
	) {

	}

	virtual exit_code_t onSetup() noexcept;
	virtual exit_code_t onConfigure() noexcept;
	virtual exit_code_t onRun() noexcept;
	virtual exit_code_t onMonitor() noexcept;
	virtual exit_code_t onRelease() noexcept;

private:
	std::unique_ptr<chronovise::UniformInputGenerator<unsigned int>> uniform_input_dist;
	chronovise::Timing timing;


};

#endif
