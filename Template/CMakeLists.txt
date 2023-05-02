cmake_minimum_required(VERSION 3.13)
project(Template)

set(CMAKE_CXX_STANDARD 20)

add_executable(Template source/main.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

# dependencies here
find_package(Catch2 CONFIG REQUIRED)

target_include_directories(Template PUBLIC ${CMAKE_CURRENT_BINARY_DIR} source)


enable_testing()
add_subdirectory(source) # clarify this is being done properly
add_subdirectory(test)