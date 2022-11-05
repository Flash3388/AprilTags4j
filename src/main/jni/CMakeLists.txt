
cmake_minimum_required(VERSION 3.16)
project(apriltags_native C)

set(CMAKE_C_STANDARD 11)

find_package(JNI REQUIRED)

find_package(PkgConfig)
pkg_search_module(apriltag REQUIRED apriltag)
set(apriltag_INCLUDE_DIRS "${apriltag_INCLUDE_DIRS}/apriltag")
link_directories(${apriltag_LIBDIR})


include_directories(${JNI_INCLUDE_DIRS} ${apriltag_INCLUDE_DIRS})

add_library(apriltags_jni SHARED
        apriltags.c
        apriltagsFamilies.c)
target_link_libraries(apriltags_jni ${apriltag_LIBRARIES})
