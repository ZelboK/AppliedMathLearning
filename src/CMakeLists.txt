set(source_files
        experiment.cpp
        differentiate/differentiate.cpp)
set(headers
        models/bounds.h
        constants.h
        analytical.h
        models/integrator.h
        models/distribution.h
        utility.h
        concepts/general.h
        models/VectorMatrix.h
        differentiate/differentiate.h)

set(spline_interpolation_files
        spline_interpolation/spline_interpolation.h
        spline_interpolation/bicubic.h)

add_library(Source
        ${source_files}
        ${headers}
        ${spline_interpolation_files})

message("${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Source
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

target_link_libraries(Source PUBLIC Eigen3::Eigen)