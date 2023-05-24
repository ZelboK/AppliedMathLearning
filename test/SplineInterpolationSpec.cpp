//
// Created by devel on 2023-05-22.
//
#include <catch2/catch_test_macros.hpp>
#include "spline_interpolation/bicubic.h"

TEST_CASE("Spline Interpolation Tests")
{

	SECTION("Derivatives")
	{
		// ∂²f/∂x∂y ≈ (f(x+1, y+1) - f(x+1, y-1) - f(x-1, y+1) + f(x-1, y-1)) / 4
		// (f(x+1, y+1) = f(3, 3) = 10? is 2,2 the centre?
		// -  f(x+1, y-1) = - f(3, 1) = -7
		// f(x-1, y+1) = - f(2, 3) = -10
		// f(x-1, y-1)) = f(1, 1) =5
		// 10 -7 - 10 + 5 = -2
		std::vector<std::vector<double>> matrix =
			{{ 1, 1, 2, 3 },
			 { 4, 5, 6, 7 },
			 { 8, 9, 10, 11 },
			 { 12, 13, 10, 10 }};

		std::vector<double> expectedPixelIntensities{ 5, 6, 9, 10 };
		std::vector<double> expected_f_x{ 1, 1, 1, 1 };
		std::vector<double> expected_f_y{ 4, 4, 4, 2 };
		std::vector<double> expected_f_xy{ 0, 0, 0, 0 };

		SplineNeighborhoodEquations expectedEquations = SplineNeighborhoodEquations(
			expectedPixelIntensities,
			expected_f_x,
			expected_f_y,
			expected_f_xy
		);

		ImageVectorWrapper image = ImageVectorWrapper(matrix);
		Point point = Point(2, 2);
		auto actual = bicubic::extract4x4(image, point);

		REQUIRE(expectedEquations.pixelIntensities_ == actual.pixelIntensities_);
		REQUIRE(expectedEquations.f_x_ == actual.f_x_);
		REQUIRE(expectedEquations.f_y_ == actual.f_y_);
		REQUIRE(expectedEquations.f_xy_ == actual.f_xy_);

	}
}
