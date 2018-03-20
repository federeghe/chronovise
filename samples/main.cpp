#include "aec.hpp"
#include "hello_world.hpp"

#include "utility/exporter.hpp"

//
// WARNING: It is strongly suggested to understand simple_main.cpp/simple_hello_world.*
//          application before trying to understand this!
//

int main() {

    // Dynamic allocation is not necessarily here, we used it just to demonstrate
    // a different way to initialize AEC compared to Simple Hello World application
    chronovise::AbstractExecutionContext<unsigned int, double> *aec = new HelloWorld();
    aec->run();

    // Export the timing measurements to a file
    chronovise::Exporter<unsigned int, double> exp(*aec);
    exp.save_time_samples("/tmp/test.bin");

    delete aec;

    return 0;
}
