cmake_minimum_required(VERSION 2.6)
project(mul)

include_directories(${CMAKE_SOURCE_DIR}/FastMultiplication)

# Fix for Qt Creator to list the hxx files.
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/FastMultiplication/*.h")
add_custom_target(mul SOURCES ${HEADERS})

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(FastMultiplication)

