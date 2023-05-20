cmake_minimum_required(VERSION 3.25)
project(exercises)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercises main.cpp)
message("${CMAKE_SOURCE_DIR}")
message("Hello!")
set(CMAKE_TOOLCHAIN_FILE
        "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(Catch2 CONFIG REQUIRED)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
