//
// Created by Danial javady on 2023-05-11.
//

#ifndef EXERCISES_SRC_UTILITY_H_
#define EXERCISES_SRC_UTILITY_H_
#include <functional>
#include <random>

template<typename Dist, typename Gen = std::mt19937>
concept DistributionWithGenerator =
requires(Dist dist, Gen gen) {
	{ dist(gen) } -> std::convertible_to<float>;
};

namespace utility
{
	template<DistributionWithGenerator Dist, typename Gen = std::mt19937>
	auto distRandGenSequence(Dist distribution, int n)
	{
		std::random_device rd;
		Gen gen(rd());
		using ValueType = decltype(distribution(gen));
		std::vector<ValueType> sample(n);
		std::generate(
			sample.begin(),
			sample.end(),
			[&]()
			{ return distribution(gen); });

		return sample;
	}

	auto squaredMeanDiff(auto a, auto b)
	{
		auto diff = a - b;
		auto squared = diff * diff;
		return squared;
	}

	template<class Input>
	requires std::is_arithmetic_v<typename Input::value_type>
	auto computeVariance(auto sampleMean,
		const Input& sample)
	{
		auto sum = 0.0;
		for (auto& value : sample)
		{
			sum += squaredMeanDiff(value, sampleMean);
		}
		return sum / sample.size();
	}

}

#endif //EXERCISES_SRC_UTILITY_H_
