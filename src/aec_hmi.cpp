#include "aec.hpp"
#include "global.hpp"
#include "utility/oop.hpp"
#include "utility/utility_hmi.hpp"

#include "evt/evtapproach_cv.hpp"
#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"

#include <iostream>
#include <iomanip>
#include <string>

namespace chronovise {


template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_distributions_summary() const noexcept {

    std::cerr << std::endl;
    utility::print_title("Distributions summary");

    std::cerr << "| Legend: " << std::endl;
    std::cerr << "|         for GEV: G - Gumbell, W - Weibull, F - Frechet" << std::endl;
    std::cerr << "|         for GPD: / - Generic, E - Exponential, P - Pareto" << std::endl;

    utility::print_closing_line();

    size_t i=0;
    for (auto it_raw=ev_dist_estimated.cbegin(); it_raw != ev_dist_estimated.cend(); it_raw++, i++) {
        auto it_generic = *it_raw;

        if (instanceof_ptr<const GEV_Distribution>(it_generic)) {
            auto it = std::dynamic_pointer_cast<const GEV_Distribution> (it_generic);
            std::cerr << '#'  << std::setw(4) << i << ": "
                  << "location=" << std::setw(12) << it->get_location()
                  << "  scale=" << std::setw(12) << it->get_scale()
                  << "  shape=" << std::setw(12) << it->get_shape() << " ["
                  << (it->is_gumbell() ? 'G' : it->is_frechet() ? 'F' : 'W') << "]";
        }

        if (instanceof_ptr<const GPD_Distribution>(it_generic)) {
            auto it = std::dynamic_pointer_cast<const GPD_Distribution> (it_generic);
            std::cerr << '#'  << std::setw(4) << i << ": "
                  << "location=" << std::setw(12) << it->get_location()
                  << "  scale=" << std::setw(12) << it->get_scale()
                  << "  shape=" << std::setw(12) << it->get_shape() << " ["
                  << (it->is_pareto() ? 'P' : it->is_exponential() ? 'E' : '/') << "]";
        }

        if(typeid(*this->evt_approach) == typeid(EVTApproach_CV<T_INPUT, T_TIME>)) {
            auto cv =  ((EVTApproach_CV<T_INPUT, T_TIME>*)(this->evt_approach.get()))->get_best_cv();

            std::cerr << std::endl << "       [CV=" << cv << "]";

        }

        std::cerr << std::endl;
    }

    if (ev_dist_estimated.size() == 0) {
        std::cerr << "No distribution found." << std::endl;
    }

    std::cerr << std::endl;

}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_configuration_info() const noexcept {

    utility::print_title("Configuration info");

    if (safety.has_reliability_requirement()) {
        std::cerr << "Reliability requirement: " << safety.get_reliability_requirement()  << std::endl;
    } else {
        std::cerr << "Reliability requirement: NOT SET" << std::endl;

    }
    std::cerr << "Ratio size test set / total samples: " << samples_test_reserve << std::endl;
    std::cerr << "Merging technique: " << (merger_tech == merger_type_t::TRACE_MERGE ? "Trace merging"
                         : merger_tech == merger_type_t::ENVELOPE ? "Envelope"
                         : "UNKNOWN") << std::endl;

    std::cerr << "Input generator: " <<
                 (input_gen == nullptr ? "NOT SET" : input_gen->to_string())
                 << std::endl;
    std::cerr << "EVT approach: " <<
                 (evt_approach == nullptr ? "NOT SET" : evt_approach->to_string())
                 << std::endl;
    std::cerr << "EVT estimator: " <<
                (evt_estimator == nullptr ? "NOT SET" : evt_estimator->to_string())
                << std::endl;

    std::cerr << "Nr. Representativity tests: " << representativity_tests.size() << std::endl;
    std::cerr << "Nr. post-run tests: " << post_run_tests.size() << std::endl;
    std::cerr << "Nr. post-evt tests (goodnes-of-fit): " << post_evt_tests.size() << std::endl;

}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_wcots() const noexcept {

    utility::print_title("Worst-Case Observed Time");

    unsigned int i=0;

    for (auto it=wcots.cbegin(); it != wcots.cend(); it++, i++) {
        std::cerr << '#'  << std::setw(4) << i << ": ";
        std::cerr << it->second << std::endl;
    }
}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_evt_info() const noexcept {

    std::cerr << std::endl;
    utility::print_title("EVT Information");

    size_t train_nr = evt_approach->get_training_pool().size();
    size_t test_nr  = evt_approach->get_test_pool().size();

    std::cerr << "Number of samples" << std::endl;
    std::cerr << "                Before EVT: " << measures.size() << std::endl;
    std::cerr << "                  Training: " << train_nr << std::endl;
    std::cerr << "                   Testing: " << test_nr  << std::endl;
    std::cerr << "           Total after EVT: " << train_nr + test_nr << std::endl;

}

template <typename T_INPUT, typename T_TIME>
void AbstractExecutionContext<T_INPUT,T_TIME>::print_legend() const noexcept {

    std::cerr << std::endl;
    utility::print_title("Legend");
    std::cerr << " " << hmi_10_iteration      << " : 10 values have been collected" << std::endl;
    std::cerr << " " << hmi_more_sample       << " : the required sample size has been increased" << std::endl;
    std::cerr << " " << hmi_reject_sample     << " : the sample has been rejected by a sample test" << std::endl;
    std::cerr << " " << hmi_fail_estimator    << " : the EVT estimator has failed" << std::endl;
    std::cerr << " " << hmi_reject_evt        << " : the EVT distribution has been rejected by post-run tests" << std::endl;
    std::cerr << " " << hmi_no_enough_samples << " : onMonitor() returned OK but no enough samples have been acquired" << std::endl;
    std::cerr << " " << hmi_success   << " : one EVT distribution has been successfully estimated" << std::endl;

}


TEMPLATE_CLASS_IMPLEMENTATION(AbstractExecutionContext);

} // chronovise
