add_executable(run_all_tests EXCLUDE_FROM_ALL
	tester.cpp
	test_generators.cpp
	test_estimator_mle.cpp
        test_estimator_pwm.cpp
	test_bm.cpp
	test_pot.cpp
	test_gev_distribution.cpp
	test_gpd_distribution.cpp
	test_test_ks.cpp
	test_test_ad.cpp
	test_aec_1.cpp
	test_test_ljung_box.cpp
	test_optional.cpp
	test_exporter.cpp
)
target_include_directories(run_all_tests PUBLIC ../include)

SET(COVERAGE OFF CACHE BOOL "Coverage")
if (COVERAGE)
    target_compile_options(run_all_tests PRIVATE --coverage)
    target_link_libraries(run_all_tests PRIVATE --coverage)
endif()


target_link_libraries(run_all_tests PRIVATE gtest gtest_main)
target_link_libraries(run_all_tests PRIVATE chronovise)

add_custom_target(tests)
add_custom_target(check
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_all_tests)

add_dependencies(tests run_all_tests)
add_dependencies(check tests)


