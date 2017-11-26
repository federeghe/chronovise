cmake_minimum_required(VERSION 3.0)
project(eMBPTA)

set(SOURCES ${SOURCES} src/input/generator_uniform.cpp src/aec.cpp)



add_library(eMBPTA ${SOURCES})

target_compile_options(eMBPTA PUBLIC -std=c++11 -Wall -Wextra -pedantic)

target_include_directories(eMBPTA PUBLIC include)

set(APP_SOURCES ${APP_SOURCES} src/samples/hello_world.cpp)
add_executable(eMBPTA_exec src/main.cpp ${APP_SOURCES})
target_link_libraries(eMBPTA_exec eMBPTA) 

add_subdirectory(tests)

