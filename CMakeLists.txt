cmake_minimum_required(VERSION 3.0)
project(eMBPTA)

set(SOURCES ${SOURCES}	src/input/generator_uniform.cpp
			src/aec.cpp
			src/evt/evtapproach_bm.cpp
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

add_library(eMBPTA ${SOURCES})

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})
target_link_libraries (eMBPTA ${CERES_LIBRARIES})


target_compile_options(eMBPTA PUBLIC -std=c++11 -Wall -Wextra -pedantic -DGIT_VERSION=\"${GIT_COMMIT_HASH}\")

target_include_directories(eMBPTA PUBLIC include)

set(APP_SOURCES ${APP_SOURCES} samples/hello_world.cpp)
add_executable(eMBPTA_exec samples/main.cpp ${APP_SOURCES})
target_link_libraries(eMBPTA_exec eMBPTA) 

add_subdirectory(tests)

