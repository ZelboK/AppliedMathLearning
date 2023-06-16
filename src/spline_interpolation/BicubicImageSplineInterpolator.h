//
// Created by Danial javady on 2023-05-22.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_

#include <Eigen/Dense>
#include <utility>
#include <vector>
#include "models/Dimensions.h"
#include "models/ImageMatrixGrayscale.h"
#include <iostream>
#include <cmath>
#include "differentiate/differentiate.h"
#include "SplineEquations.h"

// This code needs to be refactored to be templated
// as such I will likely not be able to separate in a CPP file?
//
class BicubicImageSplineInterpolator {
public:

    BicubicImageSplineInterpolator() {}

    Eigen::Matrix4d fromDifferentials(const SplineEquations &observations) {
        Eigen::Matrix4d A;
        auto intensities = observations.pixelIntensities;
        auto xGradients = observations.xGradient;
        auto yGradients = observations.yGradient;
        auto cross = observations.xyCrossDerivative;

        A <<
          intensities.at(0), intensities.at(1), yGradients.at(0), yGradients.at(1),
                intensities.at(2), intensities.at(3), yGradients.at(2), yGradients.at(3),
                xGradients.at(0), xGradients.at(1), cross.at(0), cross.at(1),
                xGradients.at(2), xGradients.at(3), cross.at(2), cross.at(3);
      //  std::cout << A << std::endl;
        return A;
    }

    double computePixel(const Eigen::Matrix4d &coefficients, double x, double y) {
        Eigen::Matrix<double, 1, 4> rowVector;
        rowVector << 1, x, std::pow(x, 2), std::pow(x, 3);
        Eigen::Matrix<double, 4, 1> colVector;
        colVector << 1,
                y,
                std::pow(y, 2),
                std::pow(y, 3);
        auto sentinel = rowVector * coefficients;
        double pixelValue = rowVector * coefficients * colVector;
        pixelValue = std::clamp(pixelValue, 0.0, 255.0);  // Clamping the pixel value to [0, 255]
        return pixelValue;
    }

    std::vector<unsigned char> bicubic(const ImageMatrixGrayscale &matrix,
                                       Dimensions newDims) {

        Eigen::Matrix4d m;
        m << 1, 0, 0, 0,
                0, 0, 1, 0,
                -3, 3, 2, -1,
                2, -2, 1, 1;
        Eigen::Matrix4d mT = m.transpose();


        std::vector<unsigned char> data(newDims.y * newDims.x);

        data.reserve(newDims.size());

        double scale = 2; // this should come as a parameter or as a calculation from newDims
        // and matrix dims so change later

        for (int i = 1; i < newDims.y; i++) {
            for (int j = 1; j < newDims.x; j++) {
                double old_i = i / scale;
                double old_j = j / scale;

                int int_i = floor(old_i);
                int int_j = floor(old_j);

                // compute fractional part
                double frac_i = old_i - int_i;
                double frac_j = old_j - int_j;

                auto equations = differentiate::attain4x4Neighborhood(matrix,
                                                                      int_i, int_j);
                Eigen::Matrix4d A =
                        fromDifferentials(
                                equations);

                double val = computePixel(A, frac_i, frac_j);
                auto placement = j + i * newDims.x;
                std::cout << placement << ", " << std::endl;
                data[placement] = static_cast<unsigned char>(val);


            }
        }
        return data;
    }

};

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
