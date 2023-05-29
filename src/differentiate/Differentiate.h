//
// Created by devel on 2023-05-26.
//

#ifndef EXERCISES_DIFFERENTIATE_H
#define EXERCISES_DIFFERENTIATE_H

#include "models/ImageMatrixGrayscale.h"
#include "models/Dimensions.h"
#include "spline_interpolation/SplineEquations.h"

namespace differentiate {
    int getLeftPos(const ImageMatrixGrayscale &matrix,
                   int row,
                   int col);

    int getRightPos(const ImageMatrixGrayscale &matrix,
                    int row,
                    int col);

    int getAbovePosition(const ImageMatrixGrayscale &matrix,
                         int row,
                         int col);

    int getBelowPosition(const ImageMatrixGrayscale &matrix,
                         int row,
                         int col);

    double getXGradient(const ImageMatrixGrayscale &matrix,
                        int row,
                        int col);


    double getYGradient(const ImageMatrixGrayscale &matrix,
                        int row,
                        int col);

    std::vector<double> grabEquationsFromCoordinates(const ImageMatrixGrayscale &matrix,
                                                     int row,
                                                     int col);


    SplineEquations attain4x4Neighborhood(const ImageMatrixGrayscale &matrix,
                                                           int row,
                                                           int col);


}

#endif //EXERCISES_DIFFERENTIATE_H
