set(HW_SOURCES ${HW_SOURCES} hello_world.cpp main.cpp)
add_executable(hello_world ${HW_SOURCES})
target_link_libraries(hello_world PUBLIC chronovise)

if(COVERAGE)
        target_link_libraries(hello_world PUBLIC --coverage)
endif(COVERAGE)


set(SHW_SOURCES ${SHW_SOURCES} simple_hello_world.cpp simple_main.cpp)
add_executable(simple_hello_world ${SHW_SOURCES})
target_link_libraries(simple_hello_world PUBLIC chronovise)

if(COVERAGE)
        target_link_libraries(simple_hello_world PUBLIC --coverage)
endif(COVERAGE)
