//
// Created by devel on 2023-05-27.
//
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "models/ImageMatrixGrayscale.h"
#include "differentiate/Differentiate.h"

TEST_CASE("edge replication strategy iterate over pixels")
{
	std::vector<double> data{ 5, 3, 2,
							  7, 4, 1,
							  9, 20, 33 };

	ImageMatrixGrayscale matrix(3, 3, data);
	SECTION("get below pixel")
	{
		int actual =
			differentiate::getBelowPosition(matrix, 2, 3);
		int expected = 8;

		REQUIRE(actual == expected);
	}

	SECTION("get above pixel")
	{
		int actual =
			differentiate::getAbovePosition(matrix, 2, 3);
		int expected = 2;

		REQUIRE(actual == expected);
	}SECTION("get left pixel")
	{
		int actual =
			differentiate::getLeftPos(matrix, 2, 3);
		int expected = 4;

		REQUIRE(actual == expected);
	}SECTION("get right pixel")
	{
		int actual =
			differentiate::getRightPos(matrix, 2, 3);
		int expected = 5;

		REQUIRE(actual == expected);
	}
}
TEST_CASE("differentiate with edge replication strategy")
{

	std::vector<double> data{ 5, 3, 2,
							  7, 4, 1,
							  9, 20, 33 };

	ImageMatrixGrayscale matrix(3, 3, data);
	SECTION("Grab 4 equations of (1, 1) in above 3x3 matrix")
	{
		std::vector<double> fourEqs =
			differentiate::grabEquationsFromCoordinates(matrix, 1, 1);

		std::vector<double> expected{
			5,
			(3 - 5) / 2.0,
			(7 - 5) / 2.0,
			(((4 - 7) / 2.0 - (3.0 - 5.0) / 2.0) / 2.0)
		};

		for (int i = 0; i < expected.size(); i++)
		{
			REQUIRE(fourEqs.at(i) == expected.at(i));
		}
	}

	SECTION("Grab 4 equations of (2, 2) in above 3x3 matrix")
	{
		std::vector<double> fourEqs =
			differentiate::grabEquationsFromCoordinates(matrix, 2, 2);

		std::vector<double> expected{
			4,
			(1.0 - 7.0) / 2.0,
			(20.0 - 3.0) / 2.0,
			(((33.0 - 9.0) / 2.0 - (2.0 - 5.0) / 2.0) / 2.0)
		};

		for (int i = 0; i < expected.size(); i++)
		{
			REQUIRE(fourEqs.at(i) == expected.at(i));
		}
	}SECTION("Grab 4 equations of (2, 2) in above 4x4 matrix")
	{
		std::vector<double> data16elems{ 5, 3, 2, 7,
										 4, 1, 9, 20,
										 33, 9, 10, 63,
										 9, 2, 13, 4 };

		ImageMatrixGrayscale matrix4x4(4, 4, data16elems);
		std::vector<double> fourEqs =
			differentiate::grabEquationsFromCoordinates
				(matrix4x4, 3, 2);

		std::vector<double> expected{
			9.0,
			(10.0 - 33) / 2.0,
			(2.0 - 1.0) / 2.0,
			(((13.0 - 9.0) / 2.0 - (9.0 - 4.0) / 2.0) / 2.0)
		};

		for (int i = 0; i < expected.size(); i++)
		{
			REQUIRE(fourEqs.at(i) == expected.at(i));
		}
	}

}

TEST_CASE("Attain 16 equations from 2x2 matrix using 4x4 neighborhood")
{
	std::vector<double> data16elems{ 5, 3, 2, 7,
									 4, 1, 9, 20,
									 33, 9, 10, 63,
									 9, 2, 13, 4 };
	// check against 9, 10
	// 				 2, 13
	ImageMatrixGrayscale matrix4x4(4, 4, data16elems);
	std::vector<double> fourEqs_row3col2 =
		differentiate::grabEquationsFromCoordinates
			(matrix4x4, 3, 2);

	std::vector<double> expected_row3col2{
		9.0,
		(10.0 - 33) / 2.0,
		(2.0 - 1.0) / 2.0,
		(((13.0 - 9.0) / 2.0 - (9.0 - 4.0) / 2.0) / 2.0)
	};
	std::vector<double> fourEqs_row3col3 =
		differentiate::grabEquationsFromCoordinates
			(matrix4x4, 3, 3);
	/*
	 * 								{5, 3, 2, 7,
									4, 1, 9, 20,
									33, 9, 10, 63,
									9, 2, 13, 4};
	 */
	std::vector<double> expected_row3col3{
		10.0,
		(63.0 - 9.0) / 2.0,
		(13.0 - 9.0) / 2.0,
		(((4.0 - 2.0) / 2.0 - (20.0 - 1.0) / 2.0) / 2.0)
	};
	std::vector<double> fourEqs_row4col2 =
		differentiate::grabEquationsFromCoordinates
			(matrix4x4, 4, 2);
	/*
	 * 								{5, 3, 2, 7,
									4, 1, 9, 20,
									33, 9, 10, 63,
									9, 2, 13, 4};
	 */
	std::vector<double> expected_row4col2{
		2.0,
		(13.0 - 9.0) / 2.0,
		(2.0 - 9.0) / 2.0,
		(((13.0 - 9.0) / 2.0 - (10.0 - 33.0) / 2.0) / 2.0)
	};

	std::vector<double> fourEqs_row4col3 =
		differentiate::grabEquationsFromCoordinates
			(matrix4x4, 4, 3);
	/*
	 * 								{5, 3, 2, 7,
									4, 1, 9, 20,
									33, 9, 10, 63,
									9, 2, 13, 4};
	 */
	std::vector<double> expected_row4col3{
		13.0,
		(4.0 - 2.0) / 2.0,
		(13.0 - 10.0) / 2.0,
		(((4.0 - 2.0) / 2.0 - (63.0 - 9.0) / 2.0) / 2.0)
	};

	std::vector<std::vector<double>> equationsFrom4x4;
	std::vector<std::vector<double>> expectedEquations;

	equationsFrom4x4.push_back(fourEqs_row3col2);
	equationsFrom4x4.push_back(fourEqs_row3col3);
	equationsFrom4x4.push_back(fourEqs_row4col2);
	equationsFrom4x4.push_back(fourEqs_row4col3);

	expectedEquations.push_back(expected_row3col2);
	expectedEquations.push_back(expected_row3col3);
	expectedEquations.push_back(expected_row4col2);
	expectedEquations.push_back(expected_row4col3);

	for (int i = 0; i < equationsFrom4x4.size(); i++)
	{
		auto actualRow = equationsFrom4x4.at(i);
		auto expectedRow = expectedEquations.at(i);

		for (int j = 0; j < actualRow.size(); j++)
		{
			auto actual = actualRow.at(j);
			auto expected = expectedRow.at(j);
			REQUIRE(actual == expected);
		}
	}

}

TEST_CASE("Attain 16 equations from 2x2 matrix using 4x4 neighborhood via attain")
{
	std::vector<double> data16elems{ 5, 3, 2, 7,
									 4, 1, 9, 20,
									 33, 9, 10, 63,
									 9, 2, 13, 4 };
	// check against 9, 10
	// 				 2, 13
	ImageMatrixGrayscale matrix4x4(4, 4, data16elems);


	std::vector<double> expected_row3col2{
		9.0,
		(10.0 - 33) / 2.0,
		(2.0 - 1.0) / 2.0,
		(((13.0 - 9.0) / 2.0 - (9.0 - 4.0) / 2.0) / 2.0)
	};

	std::vector<double> expected_row3col3{
		10.0,
		(63.0 - 9.0) / 2.0,
		(13.0 - 9.0) / 2.0,
		(((4.0 - 2.0) / 2.0 - (20.0 - 1.0) / 2.0) / 2.0)
	};

	std::vector<double> expected_row4col2{
		2.0,
		(13.0 - 9.0) / 2.0,
		(2.0 - 9.0) / 2.0,
		(((13.0 - 9.0) / 2.0 - (10.0 - 33.0) / 2.0) / 2.0)
	};

	std::vector<double> expected_row4col3{
		13.0,
		(4.0 - 2.0) / 2.0,
		(13.0 - 10.0) / 2.0,
		(((4.0 - 2.0) / 2.0 - (63.0 - 9.0) / 2.0) / 2.0)
	};

	SplineEquations equationsFrom4x4 = differentiate::attain4x4Neighborhood(
		matrix4x4, 4, 3
	);
	SplineEquations expectedEquations = SplineEquations(expected_row3col2, expected_row3col3, expected_row4col2,
		expected_row4col3);

	REQUIRE(equationsFrom4x4.pixelIntensities==expectedEquations.pixelIntensities);
	REQUIRE(equationsFrom4x4.xGradient==expectedEquations.xGradient);
	REQUIRE(equationsFrom4x4.yGradient==expectedEquations.yGradient);
	REQUIRE(equationsFrom4x4.xyCrossDerivative==expectedEquations.xyCrossDerivative);


}