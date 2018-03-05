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
 * @file fixer.hpp
 * @author Check commit authors
 * @brief File containing the Fixer class
 */

#ifndef FIXER_HPP_
#define FIXER_HPP_
#include "measures_pool.hpp"


namespace chronovise {

typedef enum class aec_status_e {
	OK = 0,
	REJECT_SAMPLE_TEST,
	FAIL_EVT_APP_MIN_SAMPLE_SIZE,
	FAIL_POST_RUN_TEST_SAMPLE_SIZE,
	FAIL_POST_EVT_TEST_SAMPLE_SIZE,
	FAIL_EVT_ESTIMATOR,
	REJECT_POST_RUN_TEST,
	REJECT_POST_EVT_TEST
} aec_status_t;

template<typename T_INPUT, typename T_TIME>
class Fixer {

public:

	typedef enum class result_e {
		CANNOT_HANDLE,		/** The fixer cannot handle this status */
		UNABLE_TO_CORRECT,	/** Fixer failed to fix the problem */
		REDO_SAMPLING,		/** The fixer asks to redo the sampling. */
		REDO_EVT_APPROACH,	/** The fixer asks to redo BM/PoT */
		REDO_EVT_ESTIMATION,	/** The fixer asks to redo the estimation phase */
		REDO_EVT_TESTS		/** The fixer asks to redo the tests */
	} result_t;


	inline void set_measures_pool(MeasuresPool<T_INPUT, T_TIME>& measures) {
		this->measures = measures;
	}

	virtual result_t process_result(aec_status_t status) final {
		return result_t::CANNOT_HANDLE;
	}

private:
	MeasuresPool<T_INPUT, T_TIME>& measures;
};

} // namespace chronowise

#endif
