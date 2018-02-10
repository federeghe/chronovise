#include "aec.hpp"
#include "hello_world.hpp"

int main() {
	AbstractExecutionContext<unsigned int> *aec = new HelloWorld();
	aec->run();

	aec->print_bm_distributions_summary();

	return 0;
}
