#include "aec.hpp"
#include "hello_world.hpp"

int main() {
	chronovise::AbstractExecutionContext<unsigned int> *aec = new HelloWorld();
	aec->run();

	aec->print_distributions_summary();

	return 0;
}
