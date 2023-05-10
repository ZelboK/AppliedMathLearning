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

	std::vector<float> genRandom(std::normal_distribution<> dist, int n) {
		std::random_device rd;
		std::mt19937 gen(rd());

		std::vector<float> sample(n);
		std::generate(sample.begin(),
			sample.end(),
			[&]() { return dist(gen); });

		return sample;
	}


	template<class T, class A>
	requires std::floating_point<T> &&
		std::floating_point<A>
	float trapezoidalNumericIntegration(std::function<T(A)> fn,
		Bounds bounds)
	{
		float subintervals = 10000;
		float width = (bounds.upper - bounds.lower) / subintervals;
		float sum = 0;

		for (T i = bounds.lower;
			 i < bounds.upper - width;
			 i += width)
		{
			T left = fn(i);
			T right = fn(i += width);
			sum += width * ((left + right) / 2);
		}
		return sum;
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
		std::normal_distribution<> d {3, 3}; // in an ideal world the importancePdf
		// would give both the distribution and respective parameters like mean and SD in this case
		int sampleCount = 10000;
		std::vector<float> sample = genRandom(d, sampleCount);
		float sum = 0;

		for(auto& point : sample) {
			auto x_i = targetPdf(point);
			auto g_i = importancePdf(point);
			auto weight = x_i / g_i;
			auto weighted = fx(point) * weight;

			sum+=weighted;
		}
		return sum/sample.size();

	}
}