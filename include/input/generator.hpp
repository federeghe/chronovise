#ifndef INPUT_GENERATOR_HPP_
#define INPUT_GENERATOR_HPP_

template <typename T>
class InputGenerator {

public:
	virtual T get() noexcept = 0;

};

#endif
