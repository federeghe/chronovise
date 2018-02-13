#include "aec.hpp"
#include "global.hpp"
#include <iostream>
#include <iomanip>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_distributions_summary() const noexcept {

	std::cerr << std::endl;
	std::cerr << "The following EV distributions have been estimated:" << std::endl;

	size_t i=0;
	for (auto it=ev_dist_estimated.cbegin(); it != ev_dist_estimated.cend(); it++, i++) {
		std::cerr << std::setw(4) << '#' << i << ": "
			  << "location=" << std::setw(16) << it->get_location() 
			  << "\tscale=" << std::setw(16) << it->get_scale() 
			  << "\tshape=" << std::setw(16) << it->get_shape() << std::endl; 
	}
	std::cerr << std::endl;

}

TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise

