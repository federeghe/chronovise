enable_testing()

add_executable(runUnitTests tester.cpp test_generators.cpp test_estimator_mle.cpp test_bm.cpp)
target_include_directories(runUnitTests PUBLIC ../include)

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests eMBPTA)

add_test(main_test runUnitTests)

