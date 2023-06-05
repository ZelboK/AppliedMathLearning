#include <catch2/catch.hpp>
#include <random>
#include <iostream>
#include "models/Bounds.h"
#include "Experiment.cpp"
#include "Constants.h"

// awkward name for the file...
// for the PBRT textbook to assure validity of answers.
// Includes trapezoidal, basic monte carlo integration, and importance sampling

TEST_CASE("play with trapezoidal")
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

//	std::function<float(float)> nonNormDist =
	//	constants::createNonStandardNormalDistPdf(3, 3);

	Bounds interval = Bounds(0, 1000);

	float integrated = Experimental::basicMonteCarlo(
		normDist,
		interval,
		100
	);
	float integratedViaTrap =
		Experimental::trapezoidalNumericIntegration(normDist, interval);
	std::cout << integratedViaTrap << "and," << integrated << std::endl;

	REQUIRE_THAT(integrated,
		Catch::Matchers::WithinAbs
			(integratedViaTrap, 0.0001));
}


static auto experiment(int stop,
	const std::function<float(float)>& normDist,
	Bounds interval,
	int sampleCount) {
	std::vector<float> elements(stop);
	float sum = 0.0;
	for (int i = 1; i < stop; i++)
	{
		float integrated = Experimental::basicMonteCarlo(
			normDist,
			interval,
			sampleCount * i
		);
		elements.at(i) = integrated;
		sum += integrated;
	}
	float avg = sum/stop;
	auto variance = utility::computeVariance(avg, elements);
	return variance;
}

TEST_CASE("Several trials Monte Carlo")
{
	std::function<float(float)> normDist = constants::standardNormalDistPdf;

	Bounds interval = Bounds(0, 1000);
	int sampleCount = 100;

	for(int i = 2; i<50; i++) {
		auto cur = experiment(i*12,
			normDist,
			interval,
			sampleCount);
		std::cout << cur << std::endl;
	}
	std::cout << "done";
}






