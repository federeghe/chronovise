enable_testing()

add_executable(run_tests tester.cpp test_generators.cpp test_estimator_mle.cpp test_bm.cpp)
target_include_directories(run_tests PUBLIC ../include)

target_link_libraries(run_tests gtest gtest_main)
target_link_libraries(run_tests chronovise)

add_test(main_test run_tests)

