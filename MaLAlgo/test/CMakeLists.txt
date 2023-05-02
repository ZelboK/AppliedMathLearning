set(${PROJECT_NAME}_TEST_FRAMEWORK "Catch2::Catch2;Catch2::Catch2WithMain" CACHE STRING "")
set(${PROJECT_NAME}_NEEDS_TEST_MAIN On CACHE BOOL "")
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.3.2  # replace with the desired version or branch
)

FetchContent_MakeAvailable(Catch2)
add_library(test_main STATIC greeting_test.cpp heybro.cpp)
target_link_libraries(test_main PUBLIC Catch2::Catch2)


