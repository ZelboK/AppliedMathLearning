//
// Created by Danial javady on 2023-05-22.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_

#include <Eigen/Dense>
#include <utility>
#include <vector>
#include "src/models/Dimensions.h"
#include "src/models/VectorMatrix.h"
#include "src/differentiate/differentiate.h"

class MyInterpolationClass {
public:
    Eigen::MatrixXd A;

    MyInterpolationClass() {
        initMatrix();
    }

    void initMatrix() {
        A.resize(16, 16);
        A.row(0) << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        A.row(1) << 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        A.row(2) << -3, 3, 0, 0, -2, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        A.row(3) << 2, -2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        A.row(4) << 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0;
        A.row(5) << 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0;
        A.row(6) << 0, 0, 0, 0, 0, 0, 0, 0, -3, 3, 0, 0, -2, -1, 0, 0;
        A.row(7) << 0, 0, 0, 0, 0, 0, 0, 0, 2, -2, 0, 0, 1, 1, 0, 0;
        A.row(8) << -3, 0, 3, 0, 0, 0, 0, 0, -2, 0, -1, 0, 0, 0, 0, 0;
        A.row(9) << 0, 0, 0, 0, -3, 0, 3, 0, 0, 0, 0, 0, -2, 0, -1, 0;
        A.row(10) << 9, -9, -9, 9, 6, 3, -6, -3, 6, -6, 3, -3, 4, 2, 2, 1;
        A.row(11) << -6, 6, 6, -6, -3, -3, 3, 3, -4, 4, -2, 2, -2, -2, -1, -1;
        A.row(12) << 2, 0, -2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0;
        A.row(13) << 0, 0, 0, 0, 2, 0, -2, 0, 0, 0, 0, 0, 1, 0, 1, 0;
        A.row(14) << -6, 6, 6, -6, -4, -2, 4, 2, -3, 3, -1, 1, -2, -1, -2, -1;
        A.row(15) << 4, -4, -4, 4, 2, 2, -2, -2, 2, -2, 2, -2, 1, 1, 1, 1;
    }

    double evaluateBicubicPolynomial(Eigen::VectorXd &b, double x, double y) {
        double x2 = x * x, y2 = y * y, x3 = x2 * x, y3 = y2 * y;
        double xy = x * y, x2y = x2 * y, xy2 = x * y2, x3y = x3 * y, xy3 = x * y3;

        double result = b(0) +
                        b(1) * x + b(2) * y + b(3) * x2 +
                        b(4) * xy + b(5) * y2 + b(6) * x3 +
                        b(7) * x2y + b(8) * xy2 + b(9) * y3 +
                        b(10) * x3y + b(11) * x2 * y2 + b(12) * xy3 +
                        b(13) * x3 * y2 + b(14) * x2 * y3 + b(15) * x3 * y3;
        return result;
    }


    std::vector<unsigned char> bicubic(const VectorMatrix &matrix,
                                       Dimensions newDims) {

        std::vector<unsigned char> data(newDims.y * newDims.x);

        data.reserve(newDims.size());
        double scale = 2; // this should come as a parameter or as a calculation from newDims
        // and matrix dims

        for (int i = 1; i < newDims.y; i++) {
            for (int j = 1; j < newDims.x; j++) {
                double scaled_i = i / scale; // we want it to round down here.
                double scaled_j = j / scale;

                int fromRow = static_cast<int>(scaled_i);
                int fromCol = static_cast<int>(scaled_j);

                double fractionalRow = scaled_i - fromRow;
                double fractionalCol = scaled_j - fromCol;

                auto observations =
                        differentiate::attain4x4Neighborhood(matrix,
                                                             fromRow, fromCol);
                std::vector<double> observationsFlat;
                for (const auto &r: observations) {
                    for (const auto &val: r) {
                        observationsFlat.push_back(val);
                    }
                }
                Eigen::VectorXd x = Eigen::VectorXd::Map(observationsFlat.data(), observationsFlat.size());
                Eigen::VectorXd b = A.colPivHouseholderQr().solve(x);

                double pixelValue = evaluateBicubicPolynomial(b, fractionalCol, fractionalRow);

                // here we are assuming pixelValue is already in [0, 255], so we convert it to unsigned char directly
                data[i * newDims.x + j] = static_cast<unsigned char>(pixelValue);
            }
        }
        return data;
    }

};

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
