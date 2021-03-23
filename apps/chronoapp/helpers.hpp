#include <set>
#include "measures_pool.hpp"

template<typename T>
T search_threshold(const chronovise::MeasuresPool<int, T> &mp) {

    std::multiset<T> ordered_nums;

    for (const auto &m : mp) {
        ordered_nums.insert(m.second);
    }
    
    int size  = ordered_nums.size();
    auto split = ordered_nums.begin();
    std::advance(split, static_cast<int>(size * 0.8));
    return *split;

}
