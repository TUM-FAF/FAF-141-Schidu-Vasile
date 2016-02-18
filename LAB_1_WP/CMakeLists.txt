cmake_minimum_required(VERSION 3.3)
project(LAB_1_WP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ClassButton.cpp ClassButton.h TextEdit.cpp TextEdit.h)
add_executable(LAB_1_WP ${SOURCE_FILES})