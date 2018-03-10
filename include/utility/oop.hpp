#ifndef UTILITY_OOP_HPP_
#define UTILITY_OOP_HPP_

#include <memory>

namespace chronovise {

/**
 * Implements an instanceof java-like constuct
 * @param ptr The pointer to the object to test
 * @return True if the pointer is a `Base` object 
 */
template<typename Base, typename T>
inline bool instanceof(const T *ptr) noexcept {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

/**
 * Implements an instanceof java-like constuct for `shared_ptr`.
 * @param ptr The smart pointer to the object to test
 * @return True if the pointer is a `Base` object 
 */
template<typename Base, typename T>
inline bool instanceof_ptr(const std::shared_ptr<T> ptr) noexcept {
    return std::dynamic_pointer_cast<const Base>(ptr) != nullptr;
}


} // namespace chronovise

#endif // UTILITY_OOP_HPP_
