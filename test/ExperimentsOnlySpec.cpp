//
// Created by Danial javady on 2023-05-24.
//
// This spec is not intended to assure / prove anyhting.
// It simply exists so i can just play around
// Look at it similar to doing math problems in a textbook in a notebook

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "ImageView.hpp"
#include <stdexcept>
#include <vector>
#include "models/VectorMatrix.h"


static std::vector<double> extractColsForXDerivation(const std::vector<double> &row) {
    if (row.size() < 2) {
        throw std::invalid_argument("Input vector must contain at least two elements.");
    }

    std::vector<double> differentials;
    differentials.reserve(row.size());  // This can help performance by avoiding reallocations

    differentials.push_back(row.at(1) - row.at(0));
    for (std::size_t i = 1; i < row.size() - 1; ++i) {
        differentials.push_back(row.at(i + 1) - row.at(i - 1));
    }
    differentials.push_back(row.at(row.size() - 1) - row.at(row.size() - 2));

    return differentials;
}

static std::vector<double> extractColsForXDerivationViaFP(const std::vector<double> &row) {
    if (row.size() < 2) {
        throw std::invalid_argument("Input vector must contain at least two elements.");
    }

    std::vector<double> differentials;
    differentials.reserve(row.size());

    auto calculateDifferential = [](double left, double right) { return right - left; };
    differentials.push_back(calculateDifferential(row[0], row[1]));

    std::transform(
            std::next(row.begin(), 1),
            std::prev(row.end(), 1),
            std::back_inserter(differentials),
            [&](const auto &current) {
                return calculateDifferential(*(std::prev(&current)), *(std::next(&current)));
            });

    differentials.push_back(calculateDifferential(row[row.size() - 2], row[row.size() - 1]));

    return differentials;
}

TEST_CASE("Image View") {
    std::vector<std::vector<double>> matrix = {{1, 3, 6},
                                               {9, 5, 2},
                                               {1, 2, 4}};
    std::vector<double> firstRow = {1, 3, 6};

    ImageView<double, std::vector<double>> image(firstRow, Dimensions(0, 0), Dimensions(2, 2));
}

TEST_CASE("EXPERIMENTS ONLY")
{
    std::vector<std::vector<double>> matrix = {{1, 3, 6},
                                               {9, 5, 2},
                                               {1, 2, 4}};
    auto expected_r0c0 = matrix.at(0).at(1) - matrix.at(0).at(0);
    auto expected_r0c1 = matrix.at(0).at(2) - matrix.at(0).at(0);
    auto expected_r0c2 = matrix.at(0).at(2) - matrix.at(0).at(1);

    auto expected_r1c0 = matrix.at(1).at(1) - matrix.at(1).at(0);
    auto expected_r1c1 = matrix.at(1).at(2) - matrix.at(1).at(0);
    auto expected_r1c2 = matrix.at(1).at(2) - matrix.at(1).at(1);

    auto expected_r2c0 = matrix.at(2).at(1) - matrix.at(2).at(0);
    auto expected_r2c1 = matrix.at(2).at(2) - matrix.at(2).at(0);
    auto expected_r2c2 = matrix.at(2).at(2) - matrix.at(2).at(1);

    std::vector<std::vector<double>> expectedXDeriv =
            {{expected_r0c0, expected_r0c1, expected_r0c2},
             {expected_r1c0, expected_r1c1, expected_r1c2},
             {expected_r2c0, expected_r2c1, expected_r2c2}};



    SECTION("3x3 first derivative of image discrete values, edge replication strategy")
    {
        for (auto &row: expectedXDeriv) {
            for (auto &col: row) {
                std::cout << col << ",";
            }
            std::cout << std::endl;
        }
        std::cout << "next test" << std::endl;
    }

    SECTION("Differentiate against x axis")
    {
        auto first = extractColsForXDerivation(matrix.at(0));
        auto second = extractColsForXDerivation(matrix.at(1));
        auto third = extractColsForXDerivation(matrix.at(2));

        std::vector<std::vector<double>> actual{first, second, third};

        for (int i = 0; i < actual.size(); i++) {
            std::vector<double> row = actual.at(i);
            for (int j = 0; j < row.size(); j++) {
                double expected = expectedXDeriv.at(i).at(j);
                double actualValue = actual.at(i).at(j);
                std::cout << expected << "expected vs actual: " << actualValue << std::endl;
                REQUIRE(actualValue == expected);
            }
        }

    }
}

// I need an algorithm that will grab the neighborhood of the current row, col you give it.
// but the problem is how to assure you do not go out of bounds.
// to go above, you need to ensure that it is a valid position.
// getPos should not be responsible for anything outside of its role imo.
// so validation should occur elsewhere.
// before getPos even gets called, you need to check if it's valid. If not? Rely on a strategy.
//

static int getLeftPos(const VectorMatrix &matrix,
                      int curPos,
                      int row,
                      int col) {
    return (col - 1 >= 0) ? matrix.getPos(row, col - 1) : curPos;
}

static int getRightPos(const VectorMatrix &matrix,
                       int curPos,
                       int row,
                       int col) {
    return (col + 1 <= matrix.cols) ? matrix.getPos(row, col + 1) : curPos;
}

static int getBelowPos(const VectorMatrix &matrix,
                       int curPos,
                       int row,
                       int col) {
    return (row - 1 >= 0) ? matrix.getPos(row - 1, col) : curPos;
}


static int getAbovePos(const VectorMatrix &matrix,
                       int curPos,
                       int row,
                       int col) {
    return (row + 1 <= matrix.rows) ? matrix.getPos(row + 1, col) : curPos;
}

static double getGradientAbove(const VectorMatrix &matrix,
                               int pos) {

}

static double getXGradient(const VectorMatrix &matrix,
                           int curPos,
                           int row,
                           int col) {
    int leftPos = getLeftPos(matrix, curPos, row, col);
    int rightPos = getRightPos(matrix, curPos, row, col);
    return (matrix.data.at(rightPos) - matrix.data.at(leftPos))
           / 2;
}

static double getYGradient(const VectorMatrix &matrix,
                           int curPos,
                           int row,
                           int col) {
    int belowPos = getBelowPos(matrix, curPos, row, col);
    int abovePos = getAbovePos(matrix, curPos, row, col);
    return (matrix.data.at(belowPos) - matrix.data.at(abovePos))
           / 2;
}

static std::vector<double> grabEquationsFromCoordinates(const VectorMatrix &matrix,
                                                        int row,
                                                        int col) {
    int curPos = matrix.getPos(row, col); // not responsible for validating row&col

    int leftPos = getLeftPos(matrix, curPos, row, col);
    int rightPos = getRightPos(matrix, curPos, row, col);
    int belowPos = getBelowPos(matrix, curPos, row, col);
    int abovePos = getAbovePos(matrix, curPos, row, col);

    int abovePosForCrossDerivative = getAbovePos(matrix, curPos, row - 1, col);
    int belowPosForCrossDerivative = getBelowPos(matrix, curPos, row + 1, col);

    double yGradient = getYGradient(matrix, curPos, row, col);
    double xGradient = getXGradient(matrix, curPos, row, col);

    double crossDerivative =
            (getXGradient(matrix, curPos, row + 1, col) -
             getXGradient(matrix, curPos, row - 1, col))
            / 2;

    return { matrix.data.at(curPos), xGradient, yGradient, crossDerivative};
}

static std::vector<double> attain4x4Neighborhood(const VectorMatrix& matrix,
                                                 int row,
                                                 int col) {
    std::vector<std::vector<double>> equations; // 4 vectors of 4 equations
    // 1 per coordinate in the 2x2
    equations.reserve(row*col);


    for(int i = col - 1; i < col; i++) {
        for(int j = row - 1; j < row; j++) {
            equations.push_back(grabEquationsFromCoordinates(matrix, i, j));
        }
    }
}

static std::vector<double> bicubic(const VectorMatrix &matrix, Dimensions newDims) {
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
}


static std::vector<std::vector<double>> getFirstDerivVector(const std::vector<std::vector<double>> &matrix) {

    for (int i = 0; i < matrix.size(); i++) {
        auto curRow = matrix.at(i);
        for (int j = 0; j < curRow.size(); j++) {

        }
    }
}