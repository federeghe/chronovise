#ifndef PWCET_ESTIMATE_HPP_
#define PWCET_ESTIMATE_HPP_
#include "aec.hpp"
#include "measures_pool.hpp"
#include "timing.hpp"
#include "input/generator_uniform.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ad.hpp"

#include <iostream>

class PWCET_Estimate : public chronovise::AbstractExecutionContext<unsigned int, double> {

public:
    PWCET_Estimate(const chronovise::MeasuresPool<int, double> &mp) : copy_mp(mp) {
    }

    virtual ~PWCET_Estimate() = default;

    virtual exit_code_t onSetup() noexcept;
    virtual exit_code_t onConfigure() noexcept;
    virtual exit_code_t onRun() noexcept;
    virtual exit_code_t onMonitor() noexcept;
    virtual exit_code_t onRelease() noexcept;

private:

    const chronovise::MeasuresPool<int, double> &copy_mp;

    std::multimap<int, double>::const_iterator copy_mp_it;

    std::shared_ptr<chronovise::StatisticalTest_AfterEVT<unsigned int, double>> ks_test;

};

#endif
