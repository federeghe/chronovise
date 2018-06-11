/*
 *  chronovise - Copyright 2018 Politecnico di Milano
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file estimator_mle.cpp
 * @author Check commit authors
 * @brief File containing the implementation of Estimator_MLE class
 */

#include "statistical/estimator_mle.hpp"

#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include "global.hpp"

#include <cassert>
#include <ceres/ceres.h>
#include <cmath>
#include <iostream>

#define LOCAL_DEBUG 0

namespace chronovise {

/**
 * @private
 */
template <typename T_INPUT, typename T_TIME, bool GMLE=false>
class GEV_Function : public ceres::FirstOrderFunction {

public:

    GEV_Function(const MeasuresPool<T_INPUT, T_TIME> &measures) : x_data(measures) {}

    virtual ~GEV_Function() {}

    virtual bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override;

    virtual int NumParameters() const override {
        return 3;
    }


private:

    static constexpr size_t mu_idx = 0;    // Index of the `location` parameter
    static constexpr size_t sg_idx = 1;    // Index of the `scale` parameter
    static constexpr size_t xi_idx = 2;    // Index of the `shape` parameter

    const MeasuresPool<T_INPUT, T_TIME> &x_data;

    void accumulate_gradient_term(const double* parameters, double *gradient, double z, double u, bool) const;

    static bool cmp_0(double x) {
        const double epsilon = 1e-6;
        return std::abs(x) <= epsilon * std::abs(x);
        // see Knuth section 4.2.2 pages 217-218
    }

};

/**
 * @private
 */
template<bool B=false> struct LIKELIHOOD {
    double operator()(double u, double sg, double xi) {
        return -std::log(sg) - u + (xi+1.) * std::log(u);
    }
};

/**
 * @private
 */
template<> struct LIKELIHOOD<true> {
    static constexpr double p = 6; // See the paper
    static constexpr double q = 9; // See the paper

    double operator()(double u, double sg, double xi) {
        // Generalized maximum-likelihood generalized extreme-value quantile
        // estimators for hydrologic data, Eduardo S. Martins, Jery R. Stedinger
        // Water Resources Research, vol. 36, n. 3, pages 737-744, 2000

        const double beta_value = std::tgamma(p) * std::tgamma(q) / std::tgamma(p + q);

        struct LIKELIHOOD<false> l_f;
        const double mle_f = l_f(u, sg, xi);

        return mle_f
            + std::pow(0.5 + xi, p-1) * std::pow(0.5 - xi, q-1) / beta_value;
}
};


template <typename T_INPUT, typename T_TIME, bool GMLE>
bool GEV_Function<T_INPUT, T_TIME, GMLE>::Evaluate(const double* parameters, double* cost, double* gradient) const {

    const double mu = parameters[mu_idx];
    const double sg = parameters[sg_idx];
    const double xi = parameters[xi_idx];

#if LOCAL_DEBUG
    std::cout << "mu=" << mu;
    std::cout << " sg=" << sg;
    std::cout << " xi=" << xi << std::endl;
#endif

    // Ref: Bücher, Axel, and Johan Segers. "On the maximum likelihood estimator for the
    // Generalized Extreme-Value distribution." Extremes 20.4 (2017): 839-872. Appendix B

    if (xi  <= -1) return false;
    if (sg  <=  0) return false;

    gradient[mu_idx] = gradient[sg_idx] = gradient[xi_idx] = 0;

    double cost_function=0;

    for (const auto &x : x_data) {

        // Compute the normalization of the sample
        const double z = (x.second - mu) / sg;
        if (1. + xi*z <= 0) {
            // This is the EVT condition. We have to skip this value because outside
            // the support of EV distributions.
            return false;
        }

        // Let's not compute some auxiliary variables
        double u     =     ! cmp_0(xi)
                ? std::pow( (1. + xi*z), -1./xi)
                : std::exp(-z);

        // An high number for z (e.g. z=300) will transform u in 0.
        if (u == 0.0) return false;

        assert(u > 0.);

        struct LIKELIHOOD<GMLE> l_func;

        // Ceres will minimize this function, so we have to invert the sign
        cost_function += - l_func(u, sg, xi);

        if (gradient != NULL) {
            accumulate_gradient_term(parameters, gradient, z, u, GMLE);
        }
    }

    cost[0] = cost_function;
    assert(std::isfinite(cost[0]));

    if (gradient != NULL) {
        gradient[mu_idx] *= -1;
        gradient[sg_idx] *= -1;
        gradient[xi_idx] *= -1;
        assert(std::isfinite(gradient[mu_idx]));
        assert(std::isfinite(gradient[sg_idx]));
        assert(std::isfinite(gradient[xi_idx]));
    }


    return true;
}

template <typename T_INPUT, typename T_TIME, bool GMLE>
void GEV_Function<T_INPUT, T_TIME, GMLE>::accumulate_gradient_term(const double* parameters, double *gradient, double z, double u, bool generalized) const {
    const double sg = parameters[sg_idx];
    const double xi = parameters[xi_idx];

    const double one_plus_xiz = 1.+xi*z;

    const double dlogu =     ! cmp_0(xi)
                ? (1./xi) * ((1./xi) * std::log(one_plus_xiz) - (z / one_plus_xiz))
                : z*z/2.;
    //assert(dlogu >= 0.);
    //assert(z*z/one_plus_xiz >= dlogu);

    gradient[mu_idx] += (xi + 1. - u) / (sg * one_plus_xiz);
    gradient[sg_idx] += ((1.-u)*z - 1.) / (sg * one_plus_xiz);

    gradient[xi_idx] += (1.-u) * dlogu - z / one_plus_xiz;
    if (generalized) {

        typedef struct LIKELIHOOD<true> llt;
        constexpr double p = llt::p;
        constexpr double q = llt::q;
        const double beta_value = std::tgamma(p) * std::tgamma(q) / std::tgamma(p + q);

        gradient[xi_idx] += 1./beta_value * ((p-1) * std::pow(0.5 + xi, p-2) * std::pow(0.5 - xi, q-1)
                         -  (q-1) * std::pow(0.5 + xi, p-1) * std::pow(0.5 - xi, q-2) ) ;
    }
}

template <typename T_INPUT, typename T_TIME, bool GMLE>
bool Estimator_MLE<T_INPUT, T_TIME, GMLE>::run(const MeasuresPool<T_INPUT, T_TIME> &measures)  {

    ceres::GradientProblemSolver::Options options;

    // TODO reliability considerations
    options.function_tolerance=1e-9;
    options.max_num_iterations = 500;
    options.minimizer_progress_to_stdout = false;
    options.logging_type = ceres::SILENT;
    options.line_search_direction_type = ceres::BFGS;

    ceres::GradientProblemSolver::Summary summary;

    if (this->ti == nullptr) {
        throw std::runtime_error("Set_source_evt_approach not called.");
    }

    // Now we have to select the function to optimize based on the provided type information
    if (*this->ti == typeid(EVTApproach_BM<T_INPUT, T_TIME>)) {

        // Block-Maxima case -> GEV Distribution

        double parameters[3] =  {    (double)measures.avg(),
                        measures.max()/100 > 1 ? measures.max()/100 : 1.,
                        0.
                    };

        ceres::GradientProblem problem(new GEV_Function<T_INPUT, T_TIME, GMLE>(measures));
        ceres::Solve(options, problem, parameters, &summary);
        result = std::make_shared<GEV_Distribution>(parameters[0], parameters[1], parameters[2]);
    }
    else {
        throw std::runtime_error("MLE estimator is not able to estimate this distribution.");
    }



#if LOCAL_DEBUG
    std::cout << summary.FullReport() << std::endl;
#endif

    switch(summary.termination_type) {
        case ceres::NO_CONVERGENCE:
            this->status = estimator_status_t::NON_PRECISE;
        break;
        case ceres::FAILURE:
        case ceres::USER_FAILURE:
            this->status = estimator_status_t::FAILED;
        break;
        case ceres::CONVERGENCE:
        case ceres::USER_SUCCESS:
            this->status = estimator_status_t::SUCCESS;
        break;

        default:
            this->status = estimator_status_t::UNKNOWN;
        break;
    }

    return summary.IsSolutionUsable();
}

TEMPLATE_CLASS_IMPLEMENTATION_3(Estimator_MLE, true);
TEMPLATE_CLASS_IMPLEMENTATION_3(Estimator_MLE, false);
} // namespace chronovise
