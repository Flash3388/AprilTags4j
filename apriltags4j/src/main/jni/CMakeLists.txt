cmake_minimum_required(VERSION 3.16)
project(apriltags_native CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(jnikit)

find_package(OpenCV REQUIRED)

find_package(PkgConfig)
pkg_search_module(apriltag REQUIRED apriltag)
set(apriltag_INCLUDE_DIRS "${apriltag_INCLUDE_DIRS}/apriltag")

include_directories(${JNI_INCLUDE_DIRS} ${apriltag_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
link_directories(${apriltag_LIBDIR})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(apriltags_jni SHARED
        apriltag_detector.cpp
        apriltag_family.cpp except.h apriltag_detections.cpp)
target_link_libraries(apriltags_jni ${apriltag_LIBRARIES} ${OpenCV_LIBS} jnikit)
