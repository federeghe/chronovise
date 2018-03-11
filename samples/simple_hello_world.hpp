#ifndef SAMPLES_SIMPLE_HELLO_WORLD_HPP_
#define SAMPLES_SIMPLE_HELLO_WORLD_HPP_

#include "sec.hpp"

class SimpleHelloWorld : public chronovise::SimpleExecutionContext<unsigned int, double> {

public:
    SimpleHelloWorld() {

    }

    virtual exit_code_t onSetup() noexcept override;
    virtual exit_code_t onConfigure() noexcept override;
    virtual exit_code_t onRun() noexcept override;
    virtual exit_code_t onMonitor() noexcept override;
    virtual exit_code_t onRelease() noexcept override;


};

#endif
