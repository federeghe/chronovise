#ifndef UTILITY_OOP_HPP_
#define UTILITY_OOP_HPP_

#include <memory>

namespace chronovise {

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<typename Base, typename T>
inline bool instanceof_ptr(const std::shared_ptr<T> ptr) {
	return std::dynamic_pointer_cast<const Base>(ptr) != nullptr;
}


} // namespace chronovise

#endif // UTILITY_OOP_HPP_
