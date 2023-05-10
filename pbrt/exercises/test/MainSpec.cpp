#include <catch2/catch_test_macros.hpp>
#include <string_view>
#include <functional>
#include <random>
#include <iostream>
#include "bounds.h"
#include "experiment.cpp"


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
	std::function<float(float)> standardNormalDistPdf = [](float x)
	{
	  float mean = 0;
	  float sd = 1;
	  float exp = (-0.5) * std::pow(((x - mean) / sd), 2);
	  float eulerRightHandSide = std::pow(2.7182, exp);
	  float leftHandSide = 1 / (sd * std::sqrt(2 * 3.14));
	  return leftHandSide * eulerRightHandSide;
	};
	std::function<float(float)> nonStandardNormalDistPdf = [](float x)
	{
	  float mean = 3;
	  float sd = 3;
	  float exp = (-0.5) * std::pow(((x - mean) / sd), 2);
	  float eulerRightHandSide = std::pow(2.7182, exp);
	  float leftHandSide = 1 / (sd * std::sqrt(2 * 3.14));
	  return leftHandSide * eulerRightHandSide;
	};

	std::random_device rd {};
	std::mt19937 gen {rd()};
	std::normal_distribution<> d {3, 3};
	d(gen);
	REQUIRE(1 == 3);
}