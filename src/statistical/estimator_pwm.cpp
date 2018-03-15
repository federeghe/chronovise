#include "statistical/estimator_pwm.hpp"

#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include "global.hpp"

#include <cmath>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
double Estimator_PWM<T_INPUT, T_TIME>::moment(const MeasuresPool<T_INPUT, T_TIME> &measures, int r) const noexcept {

    double W = 0.;
    size_t n = measures.size();

    for (size_t j=0; j < n; j++) {
        double coeff = 1.;
        for (int m=0; m < r; m++) {
            coeff *= (((double)j)-m)/(n-m);
        }
        W += coeff * measures[j];
    }

    return W / n;
}

template <typename T_INPUT, typename T_TIME>
void Estimator_PWM<T_INPUT, T_TIME>::estimator_gev(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {
    // Reference:
    // Estimation of the Generalized Extreme-Value Distribution by the Method of Probability-Weighted Moments
    // J.R.M.Hosking, J.R.Wallis, E.F.Wood, Technometrics, 1985
    // DOI: 10.1080/00401706.1985.10488049

    double W0 = moment(measures, 0);
    double W1 = moment(measures, 1);
    double W2 = moment(measures, 2);

    double c  = (2. * W1 - W0) / (3. * W2 - W0) - std::log(2.)/std::log(3.);
    double xi = 7.8590 * c + 2.9554 * c * c;
    double sg =  ((2 * W1 - W0) * xi) / ( std::tgamma(1 + xi) * (1-std::pow(2,(-xi)) ));

    assert(sg >= 0);

    double mu = W0 + sg*(std::tgamma(1+xi)-1)/xi;

    result = std::make_shared<GEV_Distribution>(mu, sg, xi);

}

template <typename T_INPUT, typename T_TIME>
void Estimator_PWM<T_INPUT, T_TIME>::estimator_gpd(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {
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

    result = std::make_shared<GPD_Distribution>(measures.min(), sg, -xi);

}

template <typename T_INPUT, typename T_TIME>
bool Estimator_PWM<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    if (this->ti == NULL) {
        throw std::runtime_error("Set_source_evt_approach not called.");
    }
    
    // Now we have to select the function to optimize based on the provided type information
    if(*this->ti == typeid(EVTApproach_BM<T_INPUT, T_TIME>)) {
        this->estimator_gev(measures);
    }
    else if (*this->ti == typeid(EVTApproach_PoT<T_INPUT, T_TIME>)) {
        this->estimator_gpd(measures);
    }
    else {
        throw std::runtime_error("PWM Estimator can currently be used only with BM and PoT.");
    }


    status = estimator_status_t::SUCCESS;

    return true;
}

TEMPLATE_CLASS_IMPLEMENTATION(Estimator_PWM);

} // namespace chronovise
