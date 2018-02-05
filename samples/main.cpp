#include "aec.hpp"
#include "hello_world.hpp"

int main() {
	AbstractExecutionContext<unsigned int> *aec = new HelloWorld();
	aec->run();

	return 0;
}
