#include "aec.hpp"
#include "global.hpp"
#include <iostream>
#include <iomanip>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_distributions_summary() const noexcept {

	size_t i=0;
	for (auto it=ev_dist_estimated.cbegin(); it != ev_dist_estimated.cend(); it++, i++) {
		std::cerr << '#' << i << ": "
			  << "location=" << std::setw(10) << it->get_location() 
			  << "\tscale=" << std::setw(10) << it->get_scale() 
			  << "\tshape=" << std::setw(10) << it->get_shape() << std::endl; 
	}

}

TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise

