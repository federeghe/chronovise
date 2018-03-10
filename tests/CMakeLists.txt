add_executable(run_all_tests EXCLUDE_FROM_ALL
	tester.cpp
	test_generators.cpp
	test_estimator_mle.cpp
	test_bm.cpp
	test_gev_distribution.cpp
	test_gpd_distribution.cpp
	test_test_ks.cpp
	test_test_ad.cpp
	test_aec_1.cpp
	test_test_ljung_box.cpp
)
target_include_directories(run_all_tests PUBLIC ../include)

target_link_libraries(run_all_tests gtest gtest_main)
target_link_libraries(run_all_tests chronovise)

add_custom_target(tests)
add_custom_target(check
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_all_tests)

add_dependencies(tests run_all_tests)
add_dependencies(check tests)


