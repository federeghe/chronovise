#include "hello_world.hpp"

#include "evt/evtapproach_bm.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"

#include <iostream>

using namespace chronovise;

using exit_code_t = AbstractExecutionContext<unsigned int, double>::exit_code_t;

static int my_testing_function(int x) {
	volatile int i, a;
	for (i=0; i < x * 10; i++) {
		a = i;
	}
	return a;
}

std::random_device random_dev;
std::mt19937 mt(random_dev());
std::normal_distribution<double> distribution(12.0,1.0);


exit_code_t HelloWorld::onSetup() noexcept {

	/* ********** PRE-RUN SECTION  ********** */
	this->set_input_source(std::move(uniform_input_dist));
//	this->add_input_transformer();		// TODO
//	this->add_representativity_test();	// TODO

	/* ********** POST-RUN SECTION ********** */
	std::shared_ptr<StatisticalTest<unsigned int, double>> stat_test(
		new TestLjungBox<unsigned int, double>(0.01, 10)
	);
	this->add_sample_test(stat_test);


	this->set_merging_technique(merger_type_e::ENVELOPE);

	std::unique_ptr<EVTApproach<unsigned int, double>> evt_app(
		new EVTApproach_BM<unsigned int, double>(25)
	);
	this->set_evt_approach(std::move(evt_app), 0.1);
	


	std::unique_ptr<Estimator<unsigned int, double>> evt_est(
		new Estimator_MLE<unsigned int, double>()
	);
	this->set_evt_estimator(std::move(evt_est));


	std::shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> aft_test(
		new TestKS<unsigned int, double>(0.01, distribution_t::EVT_GEV)
	);
	this->add_post_evt_test(aft_test);

	this->print_configuration_info();

	return AEC_OK;
}

exit_code_t HelloWorld::onConfigure() noexcept
{
	if (get_input_iteration() > 10)
		return AEC_OK;

	return AEC_CONTINUE;
}

exit_code_t HelloWorld::onRun() noexcept {

	// Clear the system state

	// Measure
//	timing.start_timing();
//	my_testing_function(this->get_current_input_value());
//	timing.stop_timing();

	// Publish data
//	this->add_sample(timing.get_ms());

	this->add_sample(distribution(mt) );
	return AEC_OK;
}

exit_code_t HelloWorld::onMonitor() noexcept {

//	if (get_iteration() > 10000)
//		return AEC_OK;
	return AEC_SLOTH;
}

exit_code_t HelloWorld::onRelease() noexcept {

	this->print_distributions_summary();

	this->print_wcots();

	std::cout << "pWCET(p=0.9999) is: " << this->get_pwcet_wcet(0.9999) << std::endl;
	std::cout << "pWCET(WCET=20) is: " << this->get_pwcet_probability(20) << std::endl;
	//this->print_pwcet_probability(1000);

	return AEC_OK;
}

