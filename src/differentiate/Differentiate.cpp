//
// Created by devel on 2023-05-26.
//


#include <iostream>
#include "models/VectorMatrix.h"
#include "models/Dimensions.h"


namespace differentiate {

    int getLeftPos(const VectorMatrix &matrix,
                   int curPos,
                   int row,
                   int col) {
        return (col - 1 > 0) ?
               matrix.getPos(row, col - 1) : curPos;
    }

    int getRightPos(const VectorMatrix &matrix,
                    int curPos,
                    int row,
                    int col) {
        return (col + 1 <= matrix.cols) ? matrix.getPos(row, col + 1) : curPos;
    }

    int getAbovePosition(const VectorMatrix &matrix,
                         int curPos,
                         int row,
                         int col) {
        return
                (row - 1 > 0) ?
                matrix.getPos(row - 1, col)
                              : curPos;
    }


    int getBelowPosition(const VectorMatrix &matrix,
                         int curPos,
                         int row,
                         int col) {
        return
                (row + 1 <= matrix.rows) ?
                matrix.getPos(row + 1, col)
                                         : curPos;
    }

    double getGradientAbove(const VectorMatrix &matrix,
                            int pos) {
        return 0.0; // implement later if need
    }

    double getXGradient(const VectorMatrix &matrix,
                        int curPos,
                        int row,
                        int col) {
        if (row < 1) {
            int leftPos = getLeftPos(matrix, curPos, 1, col);
            int rightPos = getRightPos(matrix, curPos, 1, col);
            return (matrix.data.at(rightPos) - matrix.data.at(leftPos))
                   / 2.0;
        }
        int leftPos = getLeftPos(matrix, curPos, row, col);
        int rightPos = getRightPos(matrix, curPos, row, col);
        return (matrix.data.at(rightPos) - matrix.data.at(leftPos))
               / 2.0;
    }

    double getYGradient(const VectorMatrix &matrix,
                        int curPos,
                        int row,
                        int col) {
        int abovePos = getAbovePosition(matrix, curPos, row, col);
        int belowPos = getBelowPosition(matrix, curPos, row, col);
        return (matrix.data.at(belowPos) - matrix.data.at(abovePos))
               / 2;
    }


    std::vector<double> grabEquationsFromCoordinates(const VectorMatrix &matrix,
                                                     int row,
                                                     int col) {
        int curPos = matrix.getPos(row, col); // not responsible for validating row&col

        double yGradient = getYGradient(matrix, curPos, row, col);
        double xGradient = getXGradient(matrix, curPos, row, col);

        double xGradientYDirectionAbove = getXGradient(matrix,
                                                       getAbovePosition(matrix, curPos, row, col),
                                                       row - 1, col);
        double xGradientYDirectionBelow = getXGradient(matrix,
                                                       getBelowPosition(matrix, curPos, row, col),
                                                       row + 1, col);
        double crossDerivative =
                (xGradientYDirectionBelow - xGradientYDirectionAbove)
                / 2;

        return {matrix.data.at(curPos), xGradient, yGradient, crossDerivative};
    }

    std::vector<std::vector<double>> attain4x4Neighborhood(const VectorMatrix &matrix,
                                                           int row,
                                                           int col) {
        std::vector<std::vector<double>> equations; // 4 vectors of 4 equations
        // 1 per coordinate in the 2x2
        equations.reserve(row * col);


        for (int i = col - 1; i < col + 1; i++) {
            for (int j = row - 1; j < row + 1; j++) {
                equations.push_back(grabEquationsFromCoordinates(matrix, i, j));
            }
        }
        return equations;
    }

    std::vector<double> bicubic(const VectorMatrix &matrix,
                                Dimensions newDims) {
        std::vector<double> resized;
        resized.reserve(newDims.size());
        double scale = 0; // this should come as a parameter or as a calculation from newDims
        // and matrix dims

        for (int i = 0; i < newDims.y; i++) {
            for (int j = 0; j < newDims.x; j++) {
                int fromRow = i / scale; // we want it to round down here.
                int fromCol = j / scale;
                attain4x4Neighborhood(matrix, fromRow, fromCol);


            }
        }
        return resized; // implement
    }


}

/*
 *
        int leftPos = getLeftPos(matrix, curPos, row, col);
        int rightPos = getRightPos(matrix, curPos, row, col);
        int belowPos = getBelowPos(matrix, curPos, row, col);
        int abovePos = getAbovePos(matrix, curPos, row, col);

        int abovePosForCrossDerivative = getBelowPosition(matrix, curPos, row - 1, col);
        int belowPosForCrossDerivative = getAbovePosition(matrix, curPos, row + 1, col);

 */