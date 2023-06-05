cmake_minimum_required(VERSION 3.25)

project(exercises LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercises main.cpp)

find_package(Catch2 CONFIG REQUIRED)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)
include(CheckLanguage)
check_language(CUDA)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(spline_interpolation_images)
target_link_libraries(exercises Eigen3::Eigen Source)


target_include_directories(exercises PRIVATE
        "${CMAKE_SOURCE_DIR}/internal_libraries"
        )

set_target_properties(exercises PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
