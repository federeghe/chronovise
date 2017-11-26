#include "samples/hello_world.hpp"

using exit_code_t = AbstractExecutionContext::exit_code_t;

static int my_testing_function(int x) {
	volatile int i, a;
	for (i=0; i < x * x * 1000000; i++) {
		a = i;
	}
	return a;
}


exit_code_t HelloWorld::onSetup() noexcept {
	return AEC_OK;
}

exit_code_t HelloWorld::onConfigure() noexcept
{
	current_input = input_gen.get();
	if (this->get_input_iteration() < 30) {
		return AEC_CONTINUE;
	}
	return AEC_OK;
}

exit_code_t HelloWorld::onRun() noexcept {

	// Clear the system state

	// Measure
	timing.start_timing();
	my_testing_function(current_input);
	timing.stop_timing();

	// Publish data
	measures.push(current_input, timing.get_ns());
	return AEC_OK;
}

exit_code_t HelloWorld::onMonitor() noexcept {

	if (this->get_iteration() < 10) {
		return AEC_CONTINUE;
	} else {
		return AEC_OK;
	}
}

exit_code_t HelloWorld::onRelease() noexcept {

	std::cout << "Max value: " << measures.max() << std::endl;

	return AEC_OK;
}

