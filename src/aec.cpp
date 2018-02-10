#include "aec.hpp"
#include "global.hpp"
#include "utility/utility.hpp"

#include <iostream>

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_error(const std::string &s) {

	std::cerr << std::endl << "*** ERROR" << std::endl;
	std::cerr << "An error occurred, error description follows:" << std::endl;
	std::cerr << s << std::endl;

	std::cerr << std::endl << "*** STOP" << std::endl;

	std::abort();
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::internal_cycle() noexcept {

	exit_code_t ret;

	input_iteration++;
	iteration = 0;

	bool keep_going;
	do {
		VERB(std::cerr << '.');

		ret = this->onRun();
		if (ret != AEC_OK) {
			print_error("onRun() returns error code " + ret);
		}

		ret = this->onMonitor();
		if (ret == AEC_CONTINUE) {
			keep_going = true;
		} else if (ret == AEC_OK) {
			keep_going = false;
		} else {
			print_error("onMonitor() returns error code " + ret);
		}

		iteration++;
	} while (keep_going);

	VERB(std::cerr << '+');
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::run() noexcept {

	exit_code_t ret;

	ret = this->onSetup();
	if (ret != AEC_OK) {
		print_error("onSetup() returns error code " + ret);
	}

	VERB(utility::print_welcome_message());

	ret = this->onConfigure();
	if (ret != AEC_CONTINUE) {
		print_error("onConfigure() returns error code " + ret);
	}

	do {
		current_input = input_gen->get();
		internal_cycle();

		if (merger_tech == merger_type_t::ENVELOPE) {
			execute_analysis();
			measures.clear();
		}

		ret = this->onConfigure();

		if (ret != AEC_OK && ret != AEC_CONTINUE) {
			print_error("onConfigure() returns error code " + ret);
		}

	} while(ret == AEC_CONTINUE);

	if (merger_tech == merger_type_t::TRACE_MERGE) {
		execute_analysis();
		measures.clear();
	}

	ret = this->onRelease();
	if (ret != AEC_OK) {
		print_error("onRelease() returns error code " + ret);
	}

	VERB(std::cerr << std::endl);
	
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::execute_analysis() noexcept {

	
}

template class AbstractExecutionContext<char, unsigned long>;
template class AbstractExecutionContext<int, unsigned long>;
template class AbstractExecutionContext<long, unsigned long>;
template class AbstractExecutionContext<float, unsigned long>;
template class AbstractExecutionContext<double, unsigned long>;
template class AbstractExecutionContext<unsigned char, unsigned long>;
template class AbstractExecutionContext<unsigned int, unsigned long>;
template class AbstractExecutionContext<unsigned long, unsigned long>;

