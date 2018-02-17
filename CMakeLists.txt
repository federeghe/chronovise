cmake_minimum_required(VERSION 3.0)
project(chronovise)

set(SOURCES ${SOURCES}	src/input/generator_uniform.cpp
			src/aec.cpp
			src/aec_hmi.cpp
			src/evt/evtapproach_bm.cpp
			src/evt/pwcet.cpp
			src/statistical/test_ks.cpp
			src/statistical/estimator_mle.cpp
			src/utility/utility.cpp
)


execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_library(chronovise ${SOURCES})

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})
target_link_libraries (chronovise ${CERES_LIBRARIES})


target_compile_options(chronovise PUBLIC -std=c++14 -Wall -Wextra -pedantic -DGIT_VERSION=\"${GIT_COMMIT_HASH}\")

target_include_directories(chronovise PUBLIC include)

set(APP_SOURCES ${APP_SOURCES} samples/hello_world.cpp)
add_executable(chronovise_exec samples/main.cpp ${APP_SOURCES})
target_link_libraries(chronovise_exec chronovise) 

add_subdirectory(docs)
add_subdirectory(tests)

