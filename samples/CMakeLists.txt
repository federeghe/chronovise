set(HW_SOURCES ${HW_SOURCES} hello_world.cpp main.cpp)
add_executable(hello_world ${HW_SOURCES})
target_link_libraries(hello_world chronovise)

set(SHW_SOURCES ${SHW_SOURCES} simple_hello_world.cpp simple_main.cpp)
add_executable(simple_hello_world ${SHW_SOURCES})
target_link_libraries(simple_hello_world chronovise)

