if(CERES_SOLVER)
	set(PPI_SOURCES ${PPI_SOURCES} chronoapp.cpp)
	add_executable(chronovise-app ${PPI_SOURCES})
	target_link_libraries(chronovise-app PUBLIC chronovise)

	if(COVERAGE)
	        target_link_libraries(chronovise-app PUBLIC gcov)
	endif(COVERAGE)
endif(CERES_SOLVER)
