#include "input/generator.hpp"

#include <random>

namespace chronovise {

template <typename T>
class UniformInputGenerator : public InputGenerator<T> {

public:

	UniformInputGenerator(T min, T max) : mt(rd())
	{
		this->min = min;
		this->max = max;
	} 

	virtual T get() noexcept override;

private:
	std::random_device rd;
	std::mt19937 mt;
	
	T min;
	T max;

};

} // namespace chronovise

