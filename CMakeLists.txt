cmake_minimum_required(VERSION 3.25)
project(exercises)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercises main.cpp)
set(
        CMAKE_TOOLCHAIN_FILE "-DCMAKE_TOOLCHAIN_FILE=C:/Users/12893/Desktop/CG resources/AppliedMathLearning/pbrt/exercises/vcpkg/scripts/buildsystems/vcpkg.cmake"
)

find_package(Catch2 REQUIRED)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
