#include "aec.hpp"
#include "global.hpp"
#include <iostream>
#include <iomanip>
#include <string>

namespace chronovise {

static void print_title(const std::string &title) {

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

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_distributions_summary() const noexcept {

	std::cerr << std::endl;
	print_title("Distributions summary");

	std::cerr << "| Legend: G - Gumbell, W - Weibull, F - Frechet" << std::endl;

	size_t i=0;
	for (auto it=ev_dist_estimated.cbegin(); it != ev_dist_estimated.cend(); it++, i++) {
		std::cerr << '#'  << std::setw(4) << i << ": "
			  << "location=" << std::setw(12) << it->get_location()
			  << "  scale=" << std::setw(12) << it->get_scale()
			  << "  shape=" << std::setw(12) << it->get_shape() << " ["
			  << (it->is_gumbell() ? 'G' : it->is_frechet() ? 'F' : 'W') << "]";

		std::cerr << std::endl;
	}
	std::cerr << std::endl;

}

TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise

