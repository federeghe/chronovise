#include <iostream>

#include "utility/utility.hpp"
#include "global.hpp"

namespace chronovise {

namespace utility {

void print_title(const std::string &title) noexcept {

	std::cerr.width(80);
	std::cerr.fill('-');
	std::cerr << std::left << "+" << std::right << "+" << std::endl;

	std::cerr << std::left << "| ";
	std::cerr.width(80-2);
	std::cerr.fill(' ');
	std::cerr << std::left << title << std::right << "|" << std::endl;

	std::cerr.width(80);
	std::cerr.fill('-');
	std::cerr << std::left << "+" << std::right << "+" << std::endl;

	std::cerr.fill(' ');
}


void print_welcome_message() noexcept {

	std::cerr << std::endl;
	print_title(CFG_FRAMEWORK_NAME);

	std::cerr <<
	"Version: " CFG_FRAMEWORK_VERSION << std::endl <<
	"GIT rev: " CFG_FRAMEWORK_GIT_VERSION << std::endl <<
	std::endl;

}

} // namespace utility

} //namespace chronovise
