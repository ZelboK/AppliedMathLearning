//
// Created by devel on 2023-05-22.
//
#include <catch2/catch_test_macros.hpp>
#include "spline_interpolation/BicubicImageSplineInterpolator.h"


TEST_CASE("Test against utility functions in interpolator") {
	auto interpolator = BicubicImageSplineInterpolator();
	SECTION("Normalize coordinates of pixel") {
		double fromRow = 5.0;
		double fromCol = 5.0;
		auto [actualXNorm, actualYNorm] = interpolator.normalizePixelCoordinate(5, 5);
		// 4x4 grid
		// first you get the floor
		// floor is gained by ... should be double

		double x0 = 5 - 1;
		double y0 = 5 - 1;

		double expectedXNorm = (fromCol - y0)/4;
		double expectedYNorm = (fromRow - x0)/4;

		REQUIRE(actualXNorm==expectedXNorm);
		REQUIRE(actualYNorm==expectedYNorm);
	}
	SECTION("Compute bicubic polynomial function") {

	}
}