if (CERES_SOLVER)
	set(HW_SOURCES ${HW_SOURCES} hello_world.cpp main.cpp)
	add_executable(hello_world ${HW_SOURCES})
	target_link_libraries(hello_world PUBLIC chronovise)

	if(COVERAGE)
	        target_link_libraries(hello_world PUBLIC --coverage)
	endif(COVERAGE)
endif(CERES_SOLVER)

set(SHW_SOURCES ${SHW_SOURCES} simple_hello_world.cpp simple_main.cpp)
add_executable(simple_hello_world ${SHW_SOURCES})
target_link_libraries(simple_hello_world PUBLIC chronovise)

if(COVERAGE)
        target_link_libraries(simple_hello_world PUBLIC --coverage)
endif(COVERAGE)

set(SHW_CV_SOURCES ${SHW_CV_SOURCES} simple_hello_world_cv.cpp simple_main_cv.cpp)
add_executable(simple_hello_world_cv ${SHW_CV_SOURCES})
target_link_libraries(simple_hello_world_cv PUBLIC chronovise)

if(COVERAGE)
        target_link_libraries(simple_hello_world_cv PUBLIC --coverage)
endif(COVERAGE)

set(SHW_CV_SOURCES simple_hello_world_cv_2.cpp simple_main_cv.cpp)
add_executable(simple_hello_world_cv_2 ${SHW_CV_SOURCES})
target_link_libraries(simple_hello_world_cv_2 PUBLIC chronovise)

if(COVERAGE)
        target_link_libraries(simple_hello_world_cv_2 PUBLIC --coverage)
endif(COVERAGE)
