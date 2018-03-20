#ifndef EVT_EVTAPPROACH_BM_HPP_
#define EVT_EVTAPPROACH_BM_HPP_

#include "evtapproach.hpp"

namespace chronovise {

template <typename T_INPUT, typename T_TIME=unsigned long>
class EVTApproach_BM : public EVTApproach<T_INPUT, T_TIME> {

public:

    EVTApproach_BM(size_t block_size) : block_size(block_size) { }

    virtual ~EVTApproach_BM() { }

    virtual void perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) override;

    /**
     * @brief It returns the minimal sample size to run the estimator. If a sample with lower
     *      size is provided to run() function, it will probably fail.
     */
    virtual unsigned long get_minimal_sample_size() const noexcept override {
        return this->block_size * 2;
    }

    virtual const char* to_string() const noexcept override {
        return "Block-Maxima";
    }

private:
    size_t block_size;

    void apply_bm(MeasuresPool<T_INPUT, T_TIME> & output_pool,
            typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
            typename std::multimap<T_INPUT,T_TIME>::const_iterator end,
            int size) noexcept;


};

} // namespace chronovise

#endif
