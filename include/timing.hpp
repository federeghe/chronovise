#ifndef TIMING_HPP_
#define TIMING_HPP_


#include <chrono>

#if __GNUC__
	#define FORCED_INLINE_FUNCTION __attribute__((always_inline))
#else
	#define FORCED_INLINE_FUNCTION inline
#endif

class Timing {

public:
	FORCED_INLINE_FUNCTION void start_timing() noexcept {
		start_tp = std::chrono::high_resolution_clock::now();
	}

	FORCED_INLINE_FUNCTION void stop_timing() noexcept {
		stop_tp  = std::chrono::high_resolution_clock::now();
	}

	inline unsigned long get_ns() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long,std::nano>>(stop_tp - start_tp).count();
	}

	inline unsigned long get_us() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long,std::micro>>(stop_tp - start_tp).count();
	}

	inline unsigned long get_ms() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long,std::milli>>(stop_tp - start_tp).count();
	}

	inline unsigned long get_s() const noexcept {
		return std::chrono::duration_cast<std::chrono::duration<unsigned long>>(stop_tp - start_tp).count();
	}

private:
	std::chrono::high_resolution_clock::time_point start_tp;
	std::chrono::high_resolution_clock::time_point stop_tp;

};

#endif
