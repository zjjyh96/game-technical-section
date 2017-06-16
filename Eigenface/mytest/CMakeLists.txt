cmake_minimum_required(VERSION 3.6)
project(mytest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FaceLib.cpp FaceLib.h)
add_executable(mytest ${SOURCE_FILES})

find_package( OpenCV REQUIRED )
target_link_libraries( mytest ${OpenCV_LIBS} )