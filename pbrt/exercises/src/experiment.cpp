//
// Created by Danial javady on 2023-05-08.
//
#include <functional>
#include <random>
#include <iostream>
#include "bounds.h"
// make a header for this stuff
namespace Experimental
{

	// TODO add concept of bounds
	std::vector<float> normalDistGenSequence(std::normal_distribution<> dist,
		int n)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::vector<float> sample(n);

		std::generate(
			sample.begin(),
			sample.end(),
			[&]()
			{ return dist(gen); });

		return sample;
	}

	template<class T, class A>
	requires std::floating_point<T>
		&& std::floating_point<A>
	float trapezoidalNumericIntegration(
		std::function<T(A)> fn,
		Bounds interval)
	{
		float subintervals = 10000;
		float height = interval.upper - interval.lower;
		float width = height / subintervals;
		float sum = 0;

		for (float i = interval.lower;
			 i < interval.upper - width;
			 i += width)
		{
			auto leftBase = fn(i);
			auto rightBase = fn(i + width);
			auto area = (height * ((leftBase + rightBase) / 2));
			sum += area;
		}

		return sum;

	}

	template<class T, class A>
	requires std::floating_point<T> &&
		std::floating_point<A>
	float basicMonteCarlo(
		std::function<T(A)> fx,
		std::function<T(A)> randDistribution,
		Bounds interval
	)
	{
		std::normal_distribution<> d{ 3, 3 }; // in an ideal world the importancePdf
		int sampleCount = 10000;
		std::vector<float> sample = normalDistGenSequence(d, sampleCount);
		float sum = 0;
		float height = interval.upper - interval.lower;

		// these two distributions don't correspond to one another
		for (auto& point : sample)
		{
			auto f_x = fx(point);
			auto p_x = randDistribution(point);
			sum += f_x / p_x;
		}
		float avg = sum / sample.size();

		return avg * height;

	}

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
		std::normal_distribution<> d{ 3, 3 }; // in an ideal world the importancePdf
		// would give both the distribution and respective parameters like mean and SD in this case
		int sampleCount = 10000;
		std::vector<float> sample = normalDistGenSequence(d, sampleCount);
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