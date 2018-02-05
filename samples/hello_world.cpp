#include "hello_world.hpp"
#include "statistical/test_ks.hpp"

using exit_code_t = AbstractExecutionContext<unsigned int>::exit_code_t;

static int my_testing_function(int x) {
	volatile int i, a;
	for (i=0; i < x * x * 1000000; i++) {
		a = i;
	}
	return a;
}


exit_code_t HelloWorld::onSetup() noexcept {

	/* ***** PRE-RUN SECTION ***** */
	this->set_input_source(std::move(uniform_input_dist));
//	this->add_input_transformer();		// TODO
//	this->add_representativity_test();	// TODO

	/* ***** POST-RUN SECTION ***** */

	std::shared_ptr<StatisticalTest_AfterEVT<unsigned long>> aft_test(
		new TestKS<unsigned long>(0.05)
	);
	this->add_post_evt_test(aft_test);

	return AEC_OK;
}

exit_code_t HelloWorld::onConfigure() noexcept
{
	return AEC_CONTINUE;
}

exit_code_t HelloWorld::onRun() noexcept {

	// Clear the system state

	// Measure
	timing.start_timing();
	my_testing_function(this->get_current_input_value());
	timing.stop_timing();

	// Publish data
	this->add_sample(timing.get_ns());
	return AEC_OK;
}

exit_code_t HelloWorld::onMonitor() noexcept {

	return AEC_OK;
}

exit_code_t HelloWorld::onRelease() noexcept {


	return AEC_OK;
}

