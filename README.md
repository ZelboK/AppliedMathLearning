## Components:
1) Bicubic Spline Image interpolation for grayscale 2D images. 
2) Numeric integrators like Monte Carlo, and trapezoidal.
Going through the exercises in the book _Physically Based Rendering Theory_
https://pbrt.org/ exists exercises that have you implement programs for applied mathematics.

## Motivations and Goals
1) I want to be able to improve my mathematics. By reading primary literature and actually implementing the algorithms alongside textbooks,  I believe I gain a lot of skill in the process.
2) Eventually utilize CUDA to improve performance of applications(and perhaps alongside OpenMP and/or OpenCL) and get experience with it.

## Bicubic Image Spline Interpolation
1) `Differentiate.cpp` & `Differentiate.h` - responsible for functionality used to calculate the derivatives of pixels alongside other functionality required for traversing a neighborhood.
2) `BicubicImageSplineInterpolator.h` responsible for initiating the sequence of computations to use the algorithm. Has functionality for solving the system of equations related to spline interpolation.
3) `SplineEquations.h` just a data holder for the equations related to above point

## Integration Methods
1) Logic exists in `Utility.h` and is tested against in `ProbabilityDistributionsIntegratorSpec.cpp` (needs a better name...)
2) Trapezoidal, importance sampling and basic monte carlo implemented in `Utility.h`

## TODO
1) Implement a simple CLI app for the bicubic spline interpolation resizing
2) Maybe organize src & test in to their own directory(where functionality exists for other
downstream experiments depend on)
3) Parallelize operations with a GPU.