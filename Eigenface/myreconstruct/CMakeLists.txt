cmake_minimum_required(VERSION 3.6)
project(myreconstruct)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FaceLib.cpp FaceLib.h)
add_executable(myreconstruct ${SOURCE_FILES})

find_package( OpenCV REQUIRED )
target_link_libraries( myreconstruct ${OpenCV_LIBS} )