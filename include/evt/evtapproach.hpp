#ifndef EVT_EVTAPPROACH_HPP_
#define EVT_EVTAPPROACH_HPP_

#include "../measures_pool.hpp"

namespace chronovise {

/**
 * The abstract class implementing one of the EVT approach (BM or PoT).
 */
template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach {

public:

    /**
     * A default virtual costructor
     */
    virtual ~EVTApproach() = default;

    /**
     * It performs the analysis on the provided pool of data. It also splits the pool
     * according to the iterators of the pool itself 
     * @param original_pool The raw pool from which the sample are drawned
     * @throw std::runtime_error In case of failure.
     */
    virtual void perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) = 0;

    /**
     * It returns the training pool. Calling this method before `perform` returns an
     * empty pool.
     */
    MeasuresPool<T_INPUT, T_TIME>& get_training_pool() noexcept {
        return this->training_pool;
    }

    /**
     * It returns the test pool. Calling this method before `perform` returns an
     * empty pool.
     */
    MeasuresPool<T_INPUT, T_TIME>& get_test_pool() noexcept {
        return this->test_pool;
    }

    /**
     * @brief It returns the minimal sample size to run the estimator. If a sample with lower
     *      size is provided to run() function, it will probably fail.
     */
    virtual unsigned long get_minimal_sample_size() const noexcept = 0;

    /**
     * @brief A method returning a constant character string identifying the
     *        EVT method
     */
    virtual const char* to_string() const noexcept = 0;

protected:
    MeasuresPool<T_INPUT, T_TIME> training_pool;
    MeasuresPool<T_INPUT, T_TIME> test_pool;


};

} // namespace chronovise

#endif
