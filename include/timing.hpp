/*
 * chronovise - Copyright 2018 Politecnico di Milano
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
 * @file measures_pool.hpp
 * @author Check commit authors
 * @brief File containing the Timing class
 */

#ifndef TIMING_HPP_
#define TIMING_HPP_


#include <chrono>

#if __GNUC__
	#define FORCED_INLINE_FUNCTION __attribute__((always_inline))
#else
	#define FORCED_INLINE_FUNCTION inline
#endif

namespace chronovise {

/**
 * The MeasuresPool is in charge of managing the timing of the measured application.
 * It is basically a wrapper of std::chrono function, providing more a programmer-friendly
 * way to start/stop time measurements. 
 * @warning This class is NOT thread safe.
 */
class Timing {

public:

	/**
	 * Starts the timing. It save the current time point internally as the
	 * start point of the measurement.
	 * @note This class is always inline (if the compiler allows it).
	 */
	FORCED_INLINE_FUNCTION void start_timing() noexcept {
		start_tp = std::chrono::high_resolution_clock::now();
	}

	/**
	 * Stops the timing. It save the current time point internally as the
	 * stop point of the measurement. It should be called after start_timing()
	 * otherwise undefined behaviour occurs.
	 * @note This class is always inline (if the compiler allows it).
	 */
	FORCED_INLINE_FUNCTION void stop_timing() noexcept {
		stop_tp  = std::chrono::high_resolution_clock::now();
	}

	/**
	 * Returns the time duration (stop - start) in nanoseconds.
	 */
	inline unsigned long get_ns() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long,std::nano>>(stop_tp - start_tp).count();
	}

	/**
	 * Returns the time duration (stop - start) in microseconds.
	 */
	inline unsigned long get_us() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long,std::micro>>(stop_tp - start_tp).count();
	}

	/**
	 * Returns the time duration (stop - start) in milliseconds.
	 */
	inline unsigned long get_ms() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long,std::milli>>(stop_tp - start_tp).count();
	}

	/**
	 * Returns the time duration (stop - start) in seconds.
	 */
	inline unsigned long get_s() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long>>(stop_tp - start_tp).count();
	}

private:
	std::chrono::high_resolution_clock::time_point start_tp;
	std::chrono::high_resolution_clock::time_point stop_tp;

};

} // namespace chronovise

#endif
