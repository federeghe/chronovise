#include "evt/evtapproach_bm.hpp"
#include "global.hpp"

#include <limits>
#include <stdexcept>

namespace chronovise {

template <typename T_INPUT, typename T_TIME>
void EVTApproach_BM<T_INPUT, T_TIME>::perform(const MeasuresPoolSet<T_INPUT, T_TIME>& original_pool) {

    this->training_pool.clear();
    this->test_pool.clear();

    // We need at least 2 block ...
    if (original_pool.size_trainset() < 2*block_size) {
        throw std::length_error("Not enough measures to split training set over at least 2 blocks");
    }

    // We need at least 2 block ...
    if (original_pool.size_testset() < 2*block_size) {
        throw std::length_error("Not enough measures to split test set over at least 2 blocks");
    }

    apply_bm(this->training_pool,
         original_pool.cbegin_trainset(),
         original_pool.cend_trainset(),
         original_pool.size_trainset());

    apply_bm(this->test_pool,
         original_pool.cbegin_testset(),
         original_pool.cend_testset(),
         original_pool.size_testset());


}

template <typename T_INPUT, typename T_TIME>
void EVTApproach_BM<T_INPUT, T_TIME>::apply_bm(MeasuresPool<T_INPUT, T_TIME> & output_pool,
                           typename std::multimap<T_INPUT,T_TIME>::const_iterator begin,
                           typename std::multimap<T_INPUT,T_TIME>::const_iterator end,
                           int size) noexcept {

    size_t i=1;
    T_TIME  curr_max = std::numeric_limits<T_TIME>::min();
    T_INPUT curr_max_input;

    for (auto it = begin; it != end; it++, i++) {

        if (curr_max < it->second) {
            curr_max       = it->second;
            curr_max_input = it->first;
        }

        if (i % block_size == 0) {
            output_pool.push(curr_max_input, curr_max);
            curr_max = std::numeric_limits<T_TIME>::min();
        }
    }

    if (size % block_size != 0) {
        // We need to add the last value becuase the last block is not sufficiently
        // large to reach block_size
        output_pool.push(curr_max_input, curr_max);
    }

}

TEMPLATE_CLASS_IMPLEMENTATION(EVTApproach_BM);

} // namespace chronovise

