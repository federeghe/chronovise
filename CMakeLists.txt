cmake_minimum_required(VERSION 3.0)
project(chronovise)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_OPENMP "USE_OPENMP" OFF)
option(CERES_SOLVER "CERES_SOLVER" ON)
option(COVERAGE "COVERAGE" OFF)


if (USE_OPENMP)
	find_package(OpenMP)
	if (OPENMP_FOUND)
		set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	endif(OPENMP_FOUND)
endif(USE_OPENMP)


set(SOURCES ${SOURCES}
        src/input/generator_uniform.cpp
        src/aec.cpp
        src/aec_hmi.cpp
        src/evt/gev_distribution.cpp
        src/evt/gpd_distribution.cpp
        src/evt/evtapproach_bm.cpp
        src/evt/evtapproach_pot.cpp
        src/evt/pwcet.cpp
        src/safety.cpp
        src/statistical/test_ad.cpp
        src/statistical/test_ks.cpp
        src/statistical/estimator_pwm.cpp
        src/statistical/estimator_cv.cpp
        src/statistical/test_ljung_box.cpp
        src/utility/relation_node.cpp
        src/utility/utility_hmi.cpp
        src/utility/exporter.cpp
)

if(CERES_SOLVER)
	set(SOURCES ${SOURCES} src/statistical/estimator_mle.cpp)
endif(CERES_SOLVER)

execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_library(chronovise ${SOURCES})


if(CERES_SOLVER)
	find_package(Ceres REQUIRED)
	include_directories(${CERES_INCLUDE_DIRS})
	target_link_libraries (chronovise ${CERES_LIBRARIES})
endif(CERES_SOLVER)

target_compile_options(chronovise PUBLIC -Wall -Wextra -pedantic -DGIT_VERSION=\"${GIT_COMMIT_HASH}\")

if(COVERAGE)
        target_compile_options(chronovise PUBLIC --coverage)
endif(COVERAGE)

target_include_directories(chronovise PUBLIC include)

add_subdirectory(samples)
add_subdirectory(docs)
add_subdirectory(tests)

