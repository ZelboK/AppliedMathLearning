//
// Created by Danial javady on 2023-05-10.
//

#ifndef EXERCISES_SRC_ANALYTICAL_H_
#define EXERCISES_SRC_ANALYTICAL_H_

#include <functional>
#include "integrator.h"
namespace analytical {

	template <class Distribution, class FnType>
	auto compareIntegrators(
		Integrator<Distribution, FnType> first,
		Integrator<Distribution, FnType> second,
		float marginOfError
		);

	template <class Distribution, class Fn>
	auto computeUnbiasedEstimate(int trials,
		Distribution d,
		Fn pdf) {

	}

	template<typename T>
	void foo(const T& container)
	requires requires(T a) {
		{ a.begin() } -> std::same_as<typename T::iterator>;
		{ a.end() } -> std::same_as<typename T::iterator>;
		requires std::same_as<typename T::value_type, int>;
	}
	{
		// your code here
	}

}

template<class Distribution, class FnType>
auto analytical::compareIntegrators(
	Integrator<Distribution, FnType> first,
	Integrator<Distribution, FnType> second,
	float marginOfError)
{

}

#endif //EXERCISES_SRC_ANALYTICAL_H_