set(APP_SOURCES ${APP_SOURCES} hello_world.cpp)
add_executable(hello_world main.cpp ${APP_SOURCES})
target_link_libraries(hello_world chronovise) 
