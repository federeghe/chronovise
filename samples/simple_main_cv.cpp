#include "sec.hpp"
#include "simple_hello_world_cv.hpp"

#include <iostream>

int main() {

    // Print a banner at the top
    std::cout << "Simple Hello World application" << std::endl;
    std::cout << "Welcome!" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << std::endl;

    // Just create and run our object: we don't need to do anything
    // else in the main.
    SimpleHelloWorld shw;
    shw.run();

    return 0;
}
