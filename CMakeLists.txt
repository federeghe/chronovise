cmake_minimum_required(VERSION 3.0)
project(eMBPTA)

set(SOURCES ${SOURCES}	src/input/generator_uniform.cpp
			src/mergers/trace_merger.cpp
			src/aec.cpp
			src/statistical/test_ks.cpp
)



add_library(eMBPTA ${SOURCES})

target_compile_options(eMBPTA PUBLIC -std=c++17 -Wall -Wextra -pedantic)

target_include_directories(eMBPTA PUBLIC include)

set(APP_SOURCES ${APP_SOURCES} samples/hello_world.cpp)
add_executable(eMBPTA_exec samples/main.cpp ${APP_SOURCES})
target_link_libraries(eMBPTA_exec eMBPTA) 

#add_subdirectory(tests)

