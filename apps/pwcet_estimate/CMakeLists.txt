set(HW_SOURCES ${HW_SOURCES} pwcet_estimate.cpp main.cpp)
add_executable(pwcet_estimate ${HW_SOURCES})
target_link_libraries(pwcet_estimate PUBLIC chronovise)


if(COVERAGE)
        target_link_libraries(pwcet_estimate PUBLIC gcov)
endif(COVERAGE)
