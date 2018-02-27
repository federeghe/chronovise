#include "aec.hpp"
#include "hello_world.hpp"

int main() {
	chronovise::AbstractExecutionContext<unsigned int, double> *aec = new HelloWorld();
	aec->run();

	return 0;
}
