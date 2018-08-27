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
#include "evt/evtapproach_cv.hpp"
#include "evt/evtapproach_pot.hpp"
#include "statistical/estimator_cv.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/estimator_pwm.hpp"
#include "statistical/test_ad.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"
#include "utility/fileimporter.hpp"

namespace chronovise {

/**
 * A wrapper for AbstractExecutionContext for non-advanced use, i.e. to use the predefined methods.
 * Do not use this class if you want to provide custom estimator, custom evt approach, and so on.
 */
template <typename T_INPUT=unsigned long, typename T_TIME=unsigned long>
class SimpleExecutionContext : public AbstractExecutionContext<T_INPUT, T_TIME> {

public:

    /**
     * The construction of SEC class does not perform anything special, check the
     * parent class constructor.
     * @see AbstractExecutionContext::AbstractExecutionContext()
     */
    explicit SimpleExecutionContext() : AbstractExecutionContext<T_INPUT, T_TIME>()
    {
    }

    /**
     * A default destructor.
     */
    virtual ~SimpleExecutionContext() = default;

    /**
     * This method add the LjungBox test as sample test with the given parameter.
     * @param significance_level The level of significance (\alpha) of the test
     * @param n_lags The number of lags to use
     * @see TestLjungBox::TestLjungBox()
     */
    void use_LjungBox_as_sample_test(double significance_level, int n_lags) {
        std::shared_ptr<StatisticalTest<T_INPUT, T_TIME>> stat_test(
            new TestLjungBox<T_INPUT, T_TIME>(significance_level, n_lags)
        );
        this->add_sample_test(stat_test);
    }

    /**
     * Initialize the EVT approach as Block-Maxima with the specified
     * block size and the provided ratio trainset/testset.
     * @param block_size The block size to use
     * @param ratio_train_test The ratio of samples
     * @see EVTApproach_BM::EVTApproach_BM()
     * @see AbstractExecutionContext::set_evt_approach()
     */
    void use_evt_approach_BM(int block_size, float ratio_train_test) {
        std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_app(
            new EVTApproach_BM<T_INPUT, T_TIME>(block_size)
        );
        this->set_evt_approach(std::move(evt_app), ratio_train_test);
        is_BM = true;
    }

    /**
     * Initialize the EVT approach as Peak-over-Threshold with the specified
     * block size and the provided ratio trainset/testset.
     * @param threshold The threshold to use
     * @param ratio_train_test The ratio of samples
     * @see EVTApproach_PoT::EVTApproach_PoT()
     * @see AbstractExecutionContext::set_evt_approach()
     */
    void use_evt_approach_PoT(T_TIME threshold, float ratio_train_test) {
        std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_app(
            new EVTApproach_PoT<T_INPUT, T_TIME>(threshold)
        );
        this->set_evt_approach(std::move(evt_app), ratio_train_test);
        is_BM = false;
    }

    /**
     * Initialize the EVT approach as MBPTA-CV method.
     * @param ratio_train_test The ratio of samples
     * @see EVTApproach_CV::EVTApproach_CV()
     * @see AbstractExecutionContext::set_evt_approach()
     */
    void use_evt_approach_CV(float ratio_train_test) {
        std::unique_ptr<EVTApproach<T_INPUT, T_TIME>> evt_app(
            new EVTApproach_CV<T_INPUT, T_TIME>()
        );
        this->set_evt_approach(std::move(evt_app), ratio_train_test);
        is_BM = false;
    }

    /**
     * Set the estimator to be the Maximum-Likelihood-Estimator
     * @see Estimator_MLE::Estimator_MLE()
     */
    void use_estimator_MLE() {
        std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_est(
            new Estimator_MLE<T_INPUT, T_TIME>()
        );
        this->set_evt_estimator(std::move(evt_est));
    }

    /**
     * Set the estimator to be the Generalized Maximum-Likelihood-Estimator
     * @see Estimator_MLE::Estimator_MLE()
     */
    void use_estimator_GMLE() {
        std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_est(
            new Estimator_MLE<T_INPUT, T_TIME, true>()
        );
        this->set_evt_estimator(std::move(evt_est));
    }

    /**
     * Set the estimator to be the Probabilistic-Weighted-Moments
     * @see Estimator_PWM::Estimator_PWM()
     */
    void use_estimator_PWM() {
        std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_est(
            new Estimator_PWM<T_INPUT, T_TIME>()
        );
        this->set_evt_estimator(std::move(evt_est));
    }

    /**
     * Set the estimator to be the CV estimator.
     * @note You should use this estimator only if you previously
     *       set the EVT CV approach via use_evt_approach_CV()
     * @see Estimator_CV::Estimator_CV()
     */
    void use_estimator_CV() {
        std::unique_ptr<Estimator<T_INPUT, T_TIME>> evt_est(
            new Estimator_CV<T_INPUT, T_TIME>()
        );
        this->set_evt_estimator(std::move(evt_est));
    }

    /**
     * Use Kolmogorov-Smirnov as goodness-of-fit test with the given
     * critical level. The distribution is automatically selected based
     * on the EVT approach previously selected.
     * @param crit_level The level of significance of the test
     * @see TestKS::TestKS()
     */
    void use_KS_as_post_evt_test(double crit_level) {
        std::shared_ptr<StatisticalTest_AfterEVT<T_INPUT, T_TIME>> aft_test(
            new TestKS<T_INPUT, T_TIME>(crit_level, is_BM ? distribution_t::EVT_GEV : distribution_t::EVT_GPD)
        );
        this->add_post_evt_test(aft_test);
    }

    /**
     * Use the file specified as argument as a source for input data.
     * @see utility::FileImporter::FileImporter
     */
    void use_file_as_source(const std::string &filename) noexcept {
        fi = std::make_shared<utility::FileImporter<T_TIME>>(filename);
    }
    /**
     * Replacing the standard add_sample when using a file as a source.
     * This automatically loads a sample from the file and add it as
     * measure.
     * @see AbstractExecutionContext::add_sample()
     * @see utility::FileImporter::draw_sample()
     */
    void add_sample_from_file() {
        this->add_sample(this->fi->draw_sample());
    }

private:
    bool is_BM;

    std::shared_ptr<utility::FileImporter<T_TIME>> fi;

};

} // namespace chronovise
#endif
