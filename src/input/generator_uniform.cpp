#include "input/generator_uniform.hpp"


template<>
int UniformInputGenerator<int>::get() noexcept {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

template<>
unsigned int UniformInputGenerator<unsigned int>::get() noexcept {
	std::uniform_int_distribution<unsigned int> dist(min, max);
	return dist(mt);
}


template<>
long UniformInputGenerator<long>::get() noexcept {
	std::uniform_int_distribution<long> dist(min, max);
	return dist(mt);
}

template<>
unsigned long UniformInputGenerator<unsigned long>::get() noexcept {
	std::uniform_int_distribution<unsigned long> dist(min, max);
	return dist(mt);
}

template<>
float UniformInputGenerator<float>::get() noexcept {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}


template<>
double UniformInputGenerator<double>::get() noexcept {
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}

