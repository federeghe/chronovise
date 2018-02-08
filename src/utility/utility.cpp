#include <iostream>

#include "utility/utility.hpp"
#include "global.hpp"

namespace utility {

void print_welcome_message() noexcept {

	std::cerr <<
	"+-------------------------------------------------------------------+" << std::endl <<
	"| " CFG_FRAMEWORK_NAME  << std::endl <<
	"| Version: " CFG_FRAMEWORK_VERSION << std::endl <<
	"| GIT rev: " CFG_FRAMEWORK_GIT_VERSION << std::endl <<
	"+-------------------------------------------------------------------+" << std::endl << std::endl;


}

}	// namespace utility

