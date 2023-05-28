//
// Created by devel on 2023-05-26.
//

#ifndef EXERCISES_DIFFERENTIATE_H
#define EXERCISES_DIFFERENTIATE_H

#include "models/VectorMatrix.h"
#include "models/Dimensions.h"

namespace differentiate {
    int getLeftPos(const VectorMatrix &matrix,
                   int curPos,
                   int row,
                   int col);

    int getRightPos(const VectorMatrix &matrix,
                    int curPos,
                    int row,
                    int col);

    int getAbovePosition(const VectorMatrix &matrix,
                         int curPos,
                         int row,
                         int col);

    int getBelowPosition(const VectorMatrix &matrix,
                         int curPos,
                         int row,
                         int col);

    double getGradientAbove(const VectorMatrix &matrix,
                            int pos);

    double getXGradient(const VectorMatrix &matrix,
                        int curPos,
                        int row,
                        int col);


    double getYGradient(const VectorMatrix &matrix,
                        int curPos,
                        int row,
                        int col);

    std::vector<double> grabEquationsFromCoordinates(const VectorMatrix &matrix,
                                                     int row,
                                                     int col);


    std::vector<std::vector<double>> attain4x4Neighborhood(const VectorMatrix &matrix,
                                                           int row,
                                                           int col);

    std::vector<double> bicubic(const VectorMatrix &matrix, Dimensions newDims);

}

#endif //EXERCISES_DIFFERENTIATE_H
