set(PPI_SOURCES ${PPI_SOURCES} ppi.cpp)
add_executable(ppi ${PPI_SOURCES})
target_link_libraries(ppi PUBLIC chronovise)
