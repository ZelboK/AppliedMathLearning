set(CMAKE_CXX_STANDARD 20)
message("${CMAKE_SOURCE_DIR}")
message("${CMAKE_PROJECT_DIR}")

set(source main.cpp)

add_executable(MainInterpolation
        ${source})

target_link_libraries(MainInterpolation Source)
target_include_directories(MainInterpolation PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/"
        "${CMAKE_PROJECT_DIR}/external"
        ${CMAKE_PROJECT_DIR})


