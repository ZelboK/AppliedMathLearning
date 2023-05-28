set(source_files
        Experiment.cpp
        differentiate/Differentiate.cpp)

set(headers
        models/Bounds.h
        Constants.h
        Analytical.h
        Utility.h
        concepts/General.h
        models/Integrator.h
        models/Distribution.h
        models/VectorMatrix.h
        models/Dimensions.h
        differentiate/Differentiate.h)

set(spline_interpolation_files
        spline_interpolation/spline_interpolation.h
        spline_interpolation/bicubic.h)

add_library(Source
        ${source_files}
        ${headers}
        ${spline_interpolation_files})

target_include_directories(Source
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

target_link_libraries(Source PUBLIC Eigen3::Eigen)