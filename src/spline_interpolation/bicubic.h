//
// Created by Danial javady on 2023-05-22.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_

#include <Eigen/Dense>
#include <utility>
#include <vector>
#include "models/Dimensions.h"
#include "models/VectorMatrix.h"
#include <iostream>
#include <cmath>
#include "differentiate/differentiate.h"

class BicubicImageSplineInterpolator
{
 public:
	Eigen::MatrixXd A;

	BicubicImageSplineInterpolator()
	{
		A = initMatrix(A);
	}

	Eigen::MatrixXd initMatrix(Eigen::MatrixXd A)
	{
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
		return A;
	}

	double evaluateBicubicPolynomial( Eigen::VectorXd& coefficients, double x, double y) {
		double result = 0.0;
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				result += coefficients(4*i + j) * std::pow(x, i) * std::pow(y, j);
			}
		}
		return result;
	}

	std::vector<unsigned char> bicubic(const VectorMatrix& matrix,
		Dimensions newDims)
	{

		std::vector<unsigned char> data(newDims.y * newDims.x);

		data.reserve(newDims.size());
		double scale = 2; // this should come as a parameter or as a calculation from newDims
		// and matrix dims

		for (int i = 1; i < newDims.y; i++)
		{
			for (int j = 1; j < newDims.x; j++)
			{
				int fromRow = i / scale; // we want it to round down here.
				int fromCol = j / scale;

				SplineEquations observations =
					differentiate::attain4x4Neighborhood(matrix,
						fromRow+1, fromCol+1);
				std::vector<double> observationsFlat;

				for (const auto& v : { observations.pixelIntensities,
									   observations.xGradient,
									   observations.yGradient,
									   observations.xyCrossDerivative })
				 {
					observationsFlat.insert(observationsFlat.end(), v.begin(), v.end());
				}

				Eigen::VectorXd x = Eigen::VectorXd::Map(observationsFlat.data(),
					observationsFlat.size());
				Eigen::VectorXd b = A.colPivHouseholderQr().solve(x);
				int x0 = std::floor(fromRow) - 1;
				int y0 = std::floor(fromCol) - 1;

				// The size of the grid is 4 in both dimensions
				int dx = 4, dy = 4;

				// Calculate the normalized coordinates
				double x_norm = static_cast<double>(fromRow - x0) / dx;
				double y_norm = static_cast<double>(fromCol - y0) / dy;

				double pixelValue = evaluateBicubicPolynomial(b, y_norm, x_norm);
				std::cout << pixelValue << std::endl;
				// here we are assuming pixelValue is already in [0, 255], so we convert it to unsigned char directly
				data[i * newDims.x + j] = static_cast<unsigned char>(pixelValue);
			}
		}
		return data;
	}

};

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
