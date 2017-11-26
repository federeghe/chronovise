#include "aec.hpp"

#include <iostream>

void AbstractExecutionContext::print_error(const std::string &s) {

	std::cerr << std::endl << "*** ERROR" << std::endl;
	std::cerr << "An error occurred, error description follows:" << std::endl;
	std::cerr << s << std::endl;

	std::cerr << std::endl << "*** STOP" << std::endl;

	std::abort();
}

void AbstractExecutionContext::internal_cycle() noexcept {

	exit_code_t ret;

	input_iteration++;
	iteration = 0;

	bool keep_going;
	do {
		std::cerr << '.';

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

	std::cerr << std::endl;
}

void AbstractExecutionContext::run() noexcept {

	exit_code_t ret;

	ret = this->onSetup();
	if (ret != AEC_OK) {
		print_error("onSetup() returns error code " + ret);
	}

	std::cerr << "Running";

	ret = this->onConfigure();
	if (ret != AEC_CONTINUE) {
		print_error("onConfigure() returns error code " + ret);
	}

	do {	
		internal_cycle();

		ret = this->onConfigure();

		if (ret != AEC_OK && ret != AEC_CONTINUE) {
			print_error("onConfigure() returns error code " + ret);
		}

	} while(ret == AEC_CONTINUE);

	ret = this->onRelease();
	if (ret != AEC_OK) {
		print_error("onRelease() returns error code " + ret);
	}
	
}
