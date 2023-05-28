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
#include "differentiate/differentiate.h"

using namespace differentiate;

struct Coordinates {
    int x_;
    int y_;

    Coordinates(int x, int y) : x_(x), y_(y) {

    }
};

struct SplineNeighborhoodEquations {
    std::vector<double> pixelIntensities_;
    std::vector<double> f_x_;
    std::vector<double> f_y_;
    std::vector<double> f_xy_;

    SplineNeighborhoodEquations(std::vector<double> pixelIntensities,
                                std::vector<double> f_x,
                                std::vector<double> f_y,
                                std::vector<double> f_xy)
            : pixelIntensities_(std::move(pixelIntensities)),
              f_x_(std::move(f_x)),
              f_y_(std::move(f_y)),
              f_xy_(std::move(f_xy)) {}

    bool operator==(const SplineNeighborhoodEquations &other) const {
        return compareVectors(pixelIntensities_, other.pixelIntensities_) &&
               compareVectors(f_x_, other.f_x_) &&
               compareVectors(f_y_, other.f_y_) &&
               compareVectors(f_xy_, other.f_xy_);
    }

private:
    static bool compareVectors(const std::vector<double> &v1, const std::vector<double> &v2) {
        if (v1.size() != v2.size()) {
            return false;
        }

        for (size_t i = 0; i < v1.size(); ++i) {
            if (!almost_equal(v1[i], v2[i], 1e-12)) {
                return false;
            }
        }

        return true;
    }

    static bool almost_equal(double a, double b, double epsilon) {
        return std::abs(a - b) <= epsilon * std::abs(a + b);
    }
};


struct ImageVectorWrapper {
    std::vector<std::vector<double>> matrix_;

    explicit ImageVectorWrapper(std::vector<std::vector<double>> matrix) :
            matrix_(std::move(matrix)) {}

    double get(int row, int col) {
        size_t safeRow = row, safeCol = col;

        // Check row bounds
        if (row < 0) {
            safeRow = 0;
        } else if (row >= matrix_.size()) {
            safeRow = matrix_.size() - 1;
        }

        // Check column bounds
        if (col < 0) {
            safeCol = 0;
        } else if (!matrix_.empty() && col >= matrix_[0].size()) {
            safeCol = matrix_[0].size() - 1;
        }

        return matrix_.at(safeRow).at(safeCol);
    }

};

struct Point {
    int x;
    int y;

    explicit Point(int x, int y) : x(x), y(y) {}
};

namespace bicubic {



	std::vector<double> bicubic(const VectorMatrix& matrix,
		Dimensions newDims)
	{
		std::vector<double> resized;
		resized.reserve(newDims.size());
		double scale = 0; // this should come as a parameter or as a calculation from newDims
		// and matrix dims

		for (int i = 0; i < newDims.y; i++)
		{
			for (int j = 0; j < newDims.x; j++)
			{
				int fromRow = i / scale; // we want it to round down here.
				int fromCol = j / scale;
				differentiate::attain4x4Neighborhood(matrix, fromRow, fromCol);

			}
		}
		return resized; // implement
	}
}

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
