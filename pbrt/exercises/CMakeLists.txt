cmake_minimum_required(VERSION 3.25)
project(exercises)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercises main.cpp)

find_package(Catch2 REQUIRED)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
