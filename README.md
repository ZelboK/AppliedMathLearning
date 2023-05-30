## Components:
1) Bicubic Spline Image interpolation for grayscale 2D images. 
2) Numeric integrators like Monte Carlo, and trapezoidal.
Going through the exercises in the book _Physically Based Rendering Theory_
https://pbrt.org/ exists exercises that have you implement programs for applied mathematics.

## Motivations and Goals
1) I want to be able to improve my mathematics. By reading primary literature and actually implementing the algorithms alongside textbooks,  I believe I gain a lot of skill in the process.
2) Eventually utilize CUDA to improve performance of applications(and perhaps alongside OpenMP and/or OpenCL) and get experience with it.

## TODO
1) Implement a simple CLI app for the bicubic spline interpolation resizing
2) Maybe organize src & test in to their own directory(where functionality exists for other
downstream experiments depend on)
3) Parallelize operations with a GPU.