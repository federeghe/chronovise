cmake_minimum_required(VERSION 3.5)

project(ChronoviseGui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(ChronoviseGui SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(ChronoviseGui
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    images.qrc
    model.cpp
    model.h
    testpremodel.cpp
    testpremodel.h
    testpostmodel.cpp
    testpostmodel.h
    fileimportmodel.cpp
    fileimportmodel.h
    evtapproachmodel.cpp
    evtapproachmodel.h
    evtestimatormodel.cpp
    evtestimatormodel.h
    qcustomplot.cpp
    qcustomplot.h
    plotmodel.cpp
    plotmodel.h
    distributionmodel.cpp
    distributionmodel.h
  )
endif()

target_link_libraries(ChronoviseGui PRIVATE Qt5::Widgets)
target_link_libraries(ChronoviseGui PRIVATE chronovise)
target_include_directories(ChronoviseGui PRIVATE "/usr/local/include/chronovise/")
find_package(Qt5 COMPONENTS PrintSupport REQUIRED)
target_link_libraries(ChronoviseGui PRIVATE Qt5::PrintSupport)
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})
target_link_libraries (ChronoviseGui PRIVATE ${CERES_LIBRARIES})
