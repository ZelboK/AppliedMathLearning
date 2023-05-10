#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
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
	Bounds bounds = Bounds(0, 10); // interval which x^2 is a valid pdf
	auto area = Experimental::trapezoidalNumericIntegration(pdf, bounds);
	std::cout << area << std::endl;
}
TEST_CASE("Normal distribution Importance Sampling")
{
	std::function<float(float)> standardNormalDistPdf =
		constants::standardNormalDistPdf;

	std::function<float(float)> nonStandardNormalDistPdf =
		constants::createNonStandardNormalDistPdf(3, 3);

	std::function<float(float)> fx = [](float x)
	{
	  return x * x;
	};
	// i'd like to word this as expectation
	float computedAverage = Experimental::importanceSamplingMonteCarlo
		(fx,
			nonStandardNormalDistPdf,
			standardNormalDistPdf);
	REQUIRE(1 == computedAverage);
}

TEST_CASE("Compare Monte Carlo with Trapezoid")
{
	std::function<float(float)> normDist = constants::standardNormalDistPdf;

	std::function<float(float)> nonNormDist =
		constants::createNonStandardNormalDistPdf(3, 3);

	Bounds interval = Bounds(0, 10000);

	float integrated = Experimental::basicMonteCarlo(
		nonNormDist,
		normDist,
		interval
	);
	float integratedViaTrap =
		Experimental::trapezoidalNumericIntegration(nonNormDist, interval);
	std::cout << integratedViaTrap << "and," << integrated << std::endl;

	REQUIRE_THAT(integrated,
		Catch::Matchers::WithinAbs
			(integratedViaTrap, 0.0001));
}