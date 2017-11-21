#include "aec.hpp"
#include "samples/hello_world.hpp"

int main() {
	AbstractExecutionContext *aec = new HelloWorld();
	aec->run();

	return 0;
}
