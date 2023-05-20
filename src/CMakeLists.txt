set(source_files
        experiment.cpp)
set(headers
        bounds.h
        constants.h
        analytical.h
        integrator.h
        distribution.h
        utility.h
        concepts/general.h)

set(spline_interpolation_files
        spline_interpolation/spline_interpolation.h)

add_library(Source
        ${source_files}
        ${headers}
        ${spline_interpolation_files})
message("${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Source
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )