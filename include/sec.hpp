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
 * @file sec.hpp
 * @author Check commit authors
 * @brief File containing the SimpleExecutionContext class
 */

#ifndef SEC_HPP_
#define SEC_HPP_

#include "aec.hpp"

#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/estimator_pwm.hpp"
#include "statistical/test_ad.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"

namespace chronovise {

/**
 * A wrapper for AbstractExecutionContext for non-advanced use, i.e. to use the predefined methods.
 * Do not use this class if you want to provide custom estimator, custom evt approach, and so on.
 */
template <typename T_INPUT=unsigned long, typename T_TIME=unsigned long>
class SimpleExecutionContext : public AbstractExecutionContext<T_INPUT, T_TIME> {

public:

    explicit SimpleExecutionContext() : AbstractExecutionContext<T_INPUT, T_TIME>()
    {
    }

    virtual ~SimpleExecutionContext() = default;

    void use_LjungBox_as_sample_test(double significance_level, int n_lags) {
        std::shared_ptr<StatisticalTest<T_INPUT, T_TIME>> stat_test(
            new TestLjungBox<T_INPUT, T_TIME>(significance_level, n_lags)
        );
        this->add_sample_test(stat_test);
    }

    void use_evt_approach_BM(int block_size, float ratio_train_test) {
        std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_app(
            new EVTApproach_BM<T_INPUT, T_TIME>(block_size)
        );
        this->set_evt_approach(std::move(evt_app), ratio_train_test);
        is_BM = true;
    }

    void use_evt_approach_PoT(T_TIME threshold, float ratio_train_test) {
        std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_app(
            new EVTApproach_PoT<T_INPUT, T_TIME>(threshold)
        );
        this->set_evt_approach(std::move(evt_app), ratio_train_test);
        is_BM = false;
    }

    void use_estimator_MLE() {
        std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_est(
            new Estimator_MLE<T_INPUT, T_TIME>()
        );
        this->set_evt_estimator(std::move(evt_est));
    }

    void use_estimator_PWM() {
        std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_est(
            new Estimator_PWM<T_INPUT, T_TIME>()
        );
        this->set_evt_estimator(std::move(evt_est));
    }

    void use_KS_as_post_evt_test(double crit_level) {
        std::shared_ptr<StatisticalTest_AfterEVT<T_INPUT, T_TIME>> aft_test(
            new TestKS<T_INPUT, T_TIME>(crit_level, is_BM ? distribution_t::EVT_GEV : distribution_t::EVT_GPD)
        );
        this->add_post_evt_test(aft_test);
    }

private:
    bool is_BM;

};

} // namespace chronovise
#endif
