#include "statistical/estimator_pwm.hpp"

#include "evt/gpd_distribution.hpp"
#include "global.hpp"

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
bool Estimator_PWM<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    // Reference:
    // Parameter and Quantile Estimation for the Generalized Pareto Distribution
    // J.R.M.Hosking and J.R.Wallis, Technometrics, 1987
    // DOI: 10.1080/00401706.1987.10488243

    const size_t n = measures.size();
    const auto mu = measures.min();

    T_TIME W0 = 0;
    T_TIME W1 = 0;


    for (size_t i=0; i < n; i++) {
        auto curr = measures[i] - mu;
        W0 += curr;
        W1 += (1. - (static_cast<double>(i) - 0.35) / n) * curr;
    }

    W0 /= n;
    W1 /= n;

    T_TIME xi = W0 / (W0 - 2. * W1) - 2.; 
    T_TIME sg = 2. * W0 * W1 / (W0 - 2. * W1);

    result = std::make_shared<GPD_Distribution>(measures.min(), sg, xi);

    status = estimator_status_t::SUCCESS;

    return true;
}

TEMPLATE_CLASS_IMPLEMENTATION(Estimator_PWM);

} // namespace chronovise
