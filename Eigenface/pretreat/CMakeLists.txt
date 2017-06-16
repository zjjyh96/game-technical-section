cmake_minimum_required(VERSION 3.6)
project(pretreat)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(pretreat ${SOURCE_FILES})

find_package( OpenCV REQUIRED )
target_link_libraries( pretreat ${OpenCV_LIBS} )