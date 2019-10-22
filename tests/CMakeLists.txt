set(TEST_SOURCES ${TEST_SOURCES}
    tester.cpp
    test_relations.cpp
    test_generators.cpp
    test_estimator_pwm.cpp
    test_bm.cpp
    test_pot.cpp
    test_gev_distribution.cpp
    test_gpd_distribution.cpp
    test_uniform_distribution.cpp
    test_test_ks.cpp
    test_test_ad.cpp
    test_test_ljung_box.cpp
    test_test_bds.cpp
    test_optional.cpp
    test_exporter.cpp
    test_pwcet.cpp
)

if(CERES_SOLVER)
        set (TEST_SOURCES ${TEST_SOURCES} test_aec_1.cpp test_estimator_mle.cpp)
endif(CERES_SOLVER)

add_executable(run_all_tests EXCLUDE_FROM_ALL
        ${TEST_SOURCES}
)

target_include_directories(run_all_tests PUBLIC ../include)

if (COVERAGE)
    target_compile_options(run_all_tests PRIVATE --coverage)
    target_link_libraries(run_all_tests PRIVATE --coverage -Wl,--whole-archive chronovise -Wl,--no-whole-archive)
else()
    target_link_libraries(run_all_tests PRIVATE chronovise)
endif()


target_link_libraries(run_all_tests PRIVATE gtest gtest_main)

add_custom_target(tests)
add_custom_target(check
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_all_tests)

add_dependencies(tests run_all_tests)
add_dependencies(check tests)


