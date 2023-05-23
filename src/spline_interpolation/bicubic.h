//
// Created by Danial javady on 2023-05-22.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_

#include <Eigen/Dense>
#include <utility>
#include <vector>

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

    void computeBicubic() {
    }

    auto wrapVectorToImage(const std::vector<std::vector<double>> &matrix) {

    }

    template<class Image, class Point>
    SplineNeighborhoodEquations extract4x4(Image image, Point point) {

        std::vector<double> pixelIntensities;
        std::vector<double> f_x;
        std::vector<double> f_y;
        std::vector<double> f_xy;



        for(int r = point.y - 1; r < point.y + 1 ; r++ ) {
            for(int c = point.x - 1; c < point.x + 1; c++) {
                double cur = image.get(r, c);
                pixelIntensities.push_back(cur); // simple type
                double right = image.get(r, c + 1);
                double left = image.get(r, c - 1);
                double above = image.get(r - 1, c);
                double below = image.get(r + 1, c);
                double f_x_Cur = (right - left) / 2;
                f_x.push_back(f_x_Cur);
                double f_y_Cur =
                        (below - above) / 2;
                f_y.push_back(f_y_Cur);

            }
        }

        for (int i = 0; i < 4; i++) {
            double f_xy_Cur =
                    f_x.at(i+1)
                    - f_x.at(i);
            f_xy.push_back(f_xy_Cur);
        }
        return {pixelIntensities, f_x, f_y, f_xy};
    }


    template<class Image>
    Image rescaleGrayscale(Image image, float scale) {

        for (auto &point: image) {
            computeBicubic();
        }
    }

    auto compute() {
        Eigen::Matrix<double, 16, 16> A;
        Eigen::Matrix<double, 16, 1> B;

        // Assume that you have a way of computing the values of f, fx, fy, and fxy at the points (0, 0), (1, 0), (0, 1), and (1, 1).
        // Let's put these values in the vectors f_values, fx_values, fy_values, and fxy_values.
        Eigen::Vector4d f_values, fx_values, fy_values, fxy_values;
        // Fill these vectors...

        // Now we can set up the matrix A and the vector B.
        for (int i = 0; i < 4; ++i) {
            A.row(i) << Eigen::Vector4d::Ones(),
                    Eigen::Vector4d(0, 1, 0, 1),
                    Eigen::Vector4d(0,
                                    0,
                                    1,
                                    1),
                    Eigen::Vector4d(0, 1,
                                    0,
                                    2).array().square();

            A.row(i + 4) << Eigen::Vector4d::Zero(),
                    Eigen::Vector4d::Ones(),
                    Eigen::Vector4d(0,
                                    2,
                                    0,
                                    2),
                    Eigen::Vector4d(0, 3,
                                    0,
                                    6).array().square();

            A.row(i + 8) << Eigen::Vector4d::Zero(),
                    Eigen::Vector4d(0,
                                    0,
                                    1,
                                    1), Eigen::Vector4d::Ones(), Eigen::Vector4d(0, 0,
                                                                                 2,
                                                                                 2).array().square();

            A.row(i + 12) << Eigen::Vector4d::Zero(), Eigen::Vector4d(0, 0, 1, 1), Eigen::Vector4d(0,
                                                                                                   2,
                                                                                                   0,
                                                                                                   2), Eigen::Vector4d(
                    0, 0, 3, 6).array().square();

            B(i) = f_values(i);
            B(i + 4) = fx_values(i);
            B(i + 8) = fy_values(i);
            B(i + 12) = fxy_values(i);
        }

        // Solve the system for the coefficients.
        Eigen::Matrix<double, 16, 1> x = A.fullPivLu().solve(B);
    }
}

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_BICUBIC_HPP_
