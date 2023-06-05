//
// Created by devel on 2023-05-26.
//


#include "models/ImageMatrixGrayscale.h"
#include "spline_interpolation/SplineEquations.h"

namespace differentiate {

    int getLeftPos(const ImageMatrixGrayscale &matrix,
                   int row,
                   int col) {
        return (col - 1 > 0) ? matrix.getPos(row, col - 1)
                             : matrix.getPos(row, col);
    }

    int getRightPos(const ImageMatrixGrayscale &matrix,
                    int row,
                    int col) {
        return
                (col + 1 <= matrix.cols) ? matrix.getPos(row, col + 1)
                                         : matrix.getPos(row, col)
                ;
    }

    int getAbovePosition(const ImageMatrixGrayscale &matrix,
                         int row,
                         int col) {
        return
                (row - 1 > 0) ? matrix.getPos(row - 1, col)
                              : matrix.getPos(row, col);
    }

    int getBelowPosition(const ImageMatrixGrayscale &matrix,
                         int row,
                         int col) {
        return
                (row + 1 <= matrix.rows) ? matrix.getPos(row + 1, col)
                                         : matrix.getPos(row, col);
    }

    double getXGradient(const ImageMatrixGrayscale &matrix,
                        int row,
                        int col) {
        int matchedRow = (row < 1) ? 1 :
                         (row > matrix.rows) ? matrix.rows :
                         row;
        int leftPos = getLeftPos(matrix, matchedRow, col);
        int rightPos = getRightPos(matrix, matchedRow, col);
        return (matrix.data.at(rightPos) - matrix.data.at(leftPos))
               / 2.0;
    }

    double getYGradient(const ImageMatrixGrayscale &matrix,
                        int row,
                        int col) {
        int abovePos = getAbovePosition(matrix, row, col);
        int belowPos = getBelowPosition(matrix, row, col);
        return (matrix.data.at(belowPos) - matrix.data.at(abovePos))
               / 2;
    }

    std::vector<double> grabEquationsFromCoordinates(const ImageMatrixGrayscale &matrix,
                                                     int row,
                                                     int col) {
        int curPos = matrix.getPos(row, col); // not responsible for validating row&col

        double yGradient = getYGradient(matrix, row, col);
        double xGradient = getXGradient(matrix, row, col);

        double xGradientYDirectionAbove = getXGradient(matrix,
                                                       row - 1, col);
        double xGradientYDirectionBelow = getXGradient(matrix,
                                                       row + 1, col);
        double crossDerivative =
                (xGradientYDirectionBelow - xGradientYDirectionAbove)
                / 2;

        return {matrix.data.at(curPos), xGradient, yGradient, crossDerivative};
    }

    SplineEquations attain4x4Neighborhood(const ImageMatrixGrayscale &matrix,
                                          int row,
                                          int col) {
        std::vector<std::vector<double>> equations; // 4 vectors of 4 equations
        // 1 per coordinate in the 2x2

        for (int i = row - 1; i < row + 1; i++) {
            for (int j = col - 1; j < col + 1; j++) {
                // does it ever exceed the original image? it shouldn't, right? since it is
                // scaled already at this point.
                int rowToPass = (i > 0) ? i
                                        : 1;
                int colToPass = (j > 0) ? j
                                        : 1;
                equations
                        .push_back(grabEquationsFromCoordinates(matrix,
                                                                rowToPass,
                                                                colToPass));
            }
        }
        return {equations.at(0),
                equations.at(1),
                equations.at(2),
                equations.at(3)};
    }

}

