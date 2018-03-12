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

#define LOCAL_DEBUG 1

namespace chronovise {

/**
 * @private
 */
template <typename T_INPUT, typename T_TIME>
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

    void accumulate_gradient_term(const double* parameters, double *gradient, double z, double u) const;

    static bool cmp_0(double x) {
        const double epsilon = 1e-6;
        return std::abs(x) <= epsilon * std::abs(x);
        // see Knuth section 4.2.2 pages 217-218
    }

};

template <typename T_INPUT, typename T_TIME>
bool GEV_Function<T_INPUT, T_TIME>::Evaluate(const double* parameters, double* cost, double* gradient) const {

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


        // Ceres will minimize this function, so we have to invert the sign
        cost_function += - ( -std::log(sg) - u + (xi+1.) * std::log(u) );

        if (gradient != NULL) {
	    accumulate_gradient_term(parameters, gradient, z, u);
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

template <typename T_INPUT, typename T_TIME>
void GEV_Function<T_INPUT, T_TIME>::accumulate_gradient_term(const double* parameters, double *gradient, double z, double u) const {
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
}

/**
 * @private
 */
template <typename T_INPUT, typename T_TIME>
class GPD_Function : public ceres::FirstOrderFunction {

public:

    GPD_Function(const MeasuresPool<T_INPUT, T_TIME> &measures) : x_data(measures) {}

    virtual ~GPD_Function() {}

    virtual bool Evaluate(const double* parameters,
                double* cost,
                double* gradient) const override;

    virtual int NumParameters() const override {
        return 3;
    }


private:


    static constexpr size_t sg_idx = 0;    // Index of the `scale` parameter
    static constexpr size_t xi_idx = 1;    // Index of the `shape` parameter

    const MeasuresPool<T_INPUT, T_TIME> &x_data;

    void accumulate_gradient_term(const double* parameters, double *gradient, double x) const;

    static bool cmp_0(double x) {
        const double epsilon = 1e-6;
        return std::abs(x) <= epsilon * std::abs(x);
        // see Knuth section 4.2.2 pages 217-218
    }

};

template <typename T_INPUT, typename T_TIME>
bool GPD_Function<T_INPUT, T_TIME>::Evaluate(const double* parameters, double* cost, double* gradient) const {

	const double mu = x_data.min();
    const double sg = parameters[sg_idx];
    const double xi = parameters[xi_idx];

#if LOCAL_DEBUG
    std::cout << "mu=" << mu;
    std::cout << " sg=" << sg;
    std::cout << " xi=" << xi << std::endl;
#endif

    // Ref: Parameter estimation for 3-parameter generalized pareto distribution by the principle of maximum
    // entropy (POME), V. P. SINGH & H. GUO, Hydrological Sciences Journal

    if (sg  <=  0) return false;
    

    gradient[sg_idx] = gradient[xi_idx] = 0;

    double cost_function=0;

    for (const auto &x : x_data) {

        // Compute the normalization of the sample
        const double z = (x.second - mu) / sg;
        if (1. + xi*z <= 0) {
            // This is the EVT condition. We have to skip this value because outside
            // the support of EV distributions.
            return false;
        }

        if (z < 0. && xi >= 0.) {
            return false;
        }
        if ((z < 0 || z > -1/xi) && xi < 0) {
            return false;
        }

        // Ceres will minimize this function, so we have to invert the sign
        cost_function += -(std::log(1 + xi * z));

        if (gradient != NULL) {
            accumulate_gradient_term(parameters, gradient, x.second - mu);
        }
    }

    cost[0] = cost_function;
    assert(std::isfinite(cost[0]));

    if (gradient != NULL) {
        gradient[sg_idx] *= +1;
        gradient[xi_idx] *= +1;
        assert(std::isfinite(gradient[sg_idx]));
        assert(std::isfinite(gradient[xi_idx]));
    }

    std::cout << "dSG: " << gradient[sg_idx] << " dXI: " <<  gradient[xi_idx] << std::endl;
    
    
    return true;
}


template <typename T_INPUT, typename T_TIME>
void GPD_Function<T_INPUT, T_TIME>::accumulate_gradient_term(const double* parameters, double *gradient, double x) const {
    const double sg = parameters[sg_idx];
    const double xi = parameters[xi_idx];

    gradient[sg_idx] += - xi * x / (sg * (xi * x + sg));
    gradient[xi_idx] += x / (xi * x + sg) ;
}

  
template <typename T_INPUT, typename T_TIME>
bool Estimator_MLE<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures)  {

    ceres::GradientProblemSolver::Options options;

    // TODO reliability considerations
    options.function_tolerance=1e-9;
    options.max_num_iterations = 500;
    options.minimizer_progress_to_stdout = false;
    options.logging_type = ceres::SILENT;
    options.line_search_direction_type = ceres::BFGS;

    ceres::GradientProblemSolver::Summary summary;

    if (this->ti == NULL) {
        throw std::runtime_error("Set_source_evt_approach not called.");
    }
    
    // Now we have to select the function to optimize based on the provided type information
    if (*this->ti == typeid(EVTApproach_BM<T_INPUT, T_TIME>)) {

        // Block-Maxima case -> GEV Distribution

        double parameters[3] =  {    (double)measures.avg(),
                        measures.max()/100 > 1 ? measures.max()/100 : 1.,
                        0.
                    };
 
        ceres::GradientProblem problem(new GEV_Function<T_INPUT, T_TIME>(measures));
        ceres::Solve(options, problem, parameters, &summary);
        result = std::make_shared<GEV_Distribution>(parameters[0], parameters[1], parameters[2]);
    }
    else if (*this->ti == typeid(EVTApproach_PoT<T_INPUT, T_TIME>)) {
        
        // Peak-over-Threshold case -> GPD Distribution

        double parameters[2] =  {
                        measures.max()/100 > 1 ? measures.max()/100 : 1.,
                        1.
                    };
        ceres::GradientProblem problem(new GPD_Function<T_INPUT, T_TIME>(measures));
        ceres::Solve(options, problem, parameters, &summary);
        result = std::make_shared<GPD_Distribution>(measures.min(), parameters[0], parameters[1]);
    }
    else {
        throw std::runtime_error("Invalid type_info provided.");
        return false;
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

TEMPLATE_CLASS_IMPLEMENTATION(Estimator_MLE);

} // namespace chronovise
