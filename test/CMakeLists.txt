set(test_files
        ProbabilityDistributionsIntegratorSpec.cpp
        SplineInterpolationSpec.cpp
        ExperimentsOnlySpec.cpp
        DifferentiateSpec.cpp)

add_executable(ExpTests ${test_files})
find_package(Catch2 REQUIRED)
target_link_libraries(ExpTests
        Catch2::Catch2
        Catch2::Catch2WithMain
        Source)

target_include_directories(ExpTests PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/internal_libraries"
        )

add_test(NAME Experiment COMMAND Experiment)
