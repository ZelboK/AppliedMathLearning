//
// Created by devel on 2023-05-27.
//
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "models/VectorMatrix.h"
#include "differentiate/Differentiate.h"

TEST_CASE("edge replication strategy iterate over pixels") {
    std::vector<double> data{5, 3, 2,
                             7, 4, 1,
                             9, 20, 33};

    VectorMatrix matrix(3, 3, data);
    SECTION("get below pixel") {
        int curPos = 5;
        int actual =
                differentiate::getBelowPosition(matrix, curPos,  2, 3);
        int expected = 8;

        REQUIRE(actual==expected);
    }

    SECTION("get above pixel") {
        int curPos = 5;
        int actual =
                differentiate::getAbovePosition(matrix, curPos,  2, 3);
        int expected = 2;

        REQUIRE(actual==expected);
    }
    SECTION("get left pixel") {
        int curPos = 5;
        int actual =
                differentiate::getLeftPos(matrix, curPos,  2, 3);
        int expected = 4;

        REQUIRE(actual==expected);
    }
    SECTION("get right pixel") {
        int curPos = 5;
        int actual =
                differentiate::getRightPos(matrix, curPos,  2, 3);
        int expected = 5;

        REQUIRE(actual==expected);
    }
}
TEST_CASE("differentiate with edge replication strategy") {

    std::vector<double> data{5, 3, 2,
                             7, 4, 1,
                             9, 20, 33};

    VectorMatrix matrix(3, 3, data);
    SECTION("Grab 4 equations of (1, 1) in above 3x3 matrix") {
        std::vector<double> fourEqs =
                differentiate::grabEquationsFromCoordinates(matrix, 1, 1);

        std::vector<double> expected{
                5,
                (3 - 5) / 2.0,
                (7 - 5) / 2.0,
                (((4 - 7) / 2.0 - (3.0 - 5.0) / 2.0) / 2.0)
        };

        for (int i = 0; i < expected.size(); i++) {
            REQUIRE(fourEqs.at(i) == expected.at(i));
        }
    }


    SECTION("Grab 4 equations of (2, 2) in above 3x3 matrix") {
        std::vector<double> fourEqs =
                differentiate::grabEquationsFromCoordinates(matrix, 2, 2);

        std::vector<double> expected{
                4,
                (1.0 - 7.0) / 2.0,
                (20.0 - 3.0) / 2.0,
                (((33.0 - 9.0) / 2.0 - (2.0 - 5.0) / 2.0) / 2.0)
        };

        for (int i = 0; i < expected.size(); i++) {
            REQUIRE(fourEqs.at(i) == expected.at(i));
        }
    }
    SECTION("Grab 4 equations of (2, 2) in above 4x4 matrix") {
        std::vector<double> data16elems{5, 3, 2, 7,
                                        4, 1, 9, 20,
                                        33, 9, 10, 63,
                                        9, 2, 13, 4};

        VectorMatrix matrix4x4(4, 4, data16elems);
        std::vector<double> fourEqs =
                differentiate::grabEquationsFromCoordinates
                        (matrix4x4, 3, 2);

        std::vector<double> expected{
                9.0,
                (10.0 - 33) / 2.0,
                (2.0 - 1.0) / 2.0,
                (((13.0 - 9.0) / 2.0 - (9.0 - 4.0) / 2.0) / 2.0)
        };

        for (int i = 0; i < expected.size(); i++) {
            REQUIRE(fourEqs.at(i) == expected.at(i));
        }
    }

}