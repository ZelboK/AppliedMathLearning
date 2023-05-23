cmake_minimum_required(VERSION 3.25)

project(exercises)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercises main.cpp)

find_package(Catch2 CONFIG REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
target_link_libraries(exercises Eigen3::Eigen)