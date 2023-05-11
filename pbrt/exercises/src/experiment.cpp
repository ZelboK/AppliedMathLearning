//
// Created by Danial javady on 2023-05-08.
//
#include <functional>
#include <random>
#include <iostream>
#include "bounds.h"
#include "utility.h"
// make a header for this stuff
namespace Experimental
{


	// not responsible for validating interval
	template<class T, class A>
	requires std::floating_point<T>
		&& std::floating_point<A>
	float trapezoidalNumericIntegration(
		std::function<T(A)> fn,
		Bounds interval)
	{
		int subintervals = 10000;
		float width = (interval.upper - interval.lower) /
			static_cast<float>(subintervals);
		float sum = 0;

		for (int i = 1; i < subintervals - 1; i++)
		{
			auto xi = interval.lower + i * width;
			auto f_xi = fn(xi);
			sum += 2 * f_xi;
		}

		return (sum + fn(interval.lower) + fn(interval.upper)) * width / 2;
	}

	template<class T, class A>
	requires std::floating_point<T> &&
		std::floating_point<A>
	float basicMonteCarlo(
		std::function<T(A)> fx,
		Bounds interval,
		int sampleCount
	)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(interval.lower, interval.upper);
		float sum = 0;

		for (int i = 0; i < sampleCount; i++)
		{
			auto xi = dist(gen);
			auto f_xi = fx(xi);
			sum += f_xi;
		}

		float avg = sum / static_cast<float>(sampleCount);
		float area = avg * (interval.upper - interval.lower);
		return area;
	}

	// these two distributions don't correspond to one another
//		for (auto& point : sample)
//		{
//			auto f_x = fx(point);
//			auto p_x = randDistribution(point);
//			sum += f_x / p_x;
//		}
	// not responsible for validating that inputs are proper PDFs nor if importancePdf
	// is a suitable proposal distribution
	template<class T, class A>
	requires std::floating_point<T> &&
		std::floating_point<A>
	float importanceSamplingMonteCarlo(
		std::function<T(A)> fx,
		std::function<T(A)> targetPdf,
		std::function<T(A)> importancePdf)
	{
		std::normal_distribution<float> d{ 3, 3 }; // in an ideal world the importancePdf
		// would give both the distribution and respective parameters like mean and SD in this case
		int sampleCount = 10000;
		std::vector<float> sample = utility::distRandGenSequence(d, sampleCount);
		float sum = 0;

		for (auto& point : sample)
		{
			auto x_i = targetPdf(point);
			auto g_i = importancePdf(point);
			auto weight = x_i / g_i;
			auto weighted = fx(point) * weight;

			sum += weighted;
		}
		return sum / sample.size();

	}
}