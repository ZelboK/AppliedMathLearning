#include <catch2/catch_test_macros.hpp>
#include <string_view>
#include <functional>
#include <random>
#include <iostream>
#include "bounds.h"
#include "experiment.cpp"
#include "constants.h"

TEST_CASE("Hello")
{
	std::function<float(float)> pdf = [](float x)
	{
	  return x * x;
	};
	Bounds bounds = { 0, 1 }; // interval which x^2 is a valid pdf
	auto area = Experimental::trapezoidalNumericIntegration(pdf, bounds);
	std::cout << area << std::endl;
}
TEST_CASE("Normal distribution Importance Sampling")
{
	std::function<float(float)> standardNormalDistPdf =
		constants::standardNormalDistPdf;

	std::function<float(float)> nonStandardNormalDistPdf =
		constants::createNonStandardNormalDistPdf(3, 3);

	std::function<float(float)> fx = [](float x) {
		return x*x;
	};
	// i'd like to word this as expectation
	float computedAverage = Experimental::importanceSamplingMonteCarlo(fx, nonStandardNormalDistPdf, standardNormalDistPdf);
	REQUIRE(1 == computedAverage);
}