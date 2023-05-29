//
// Created by Danial javady on 2023-05-10.
//

#ifndef EXERCISES_SRC_ANALYTICAL_H_
#define EXERCISES_SRC_ANALYTICAL_H_

#include <functional>
#include "models/Integrator.h"

// would be used for the PBRT textbook, incomplete
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

}

// i wanted to test out this way of organizing templated header files
// separate definitions and declarations in the same file kind of like
// haskell
template<class Distribution, class FnType>
auto analytical::compareIntegrators(
	Integrator<Distribution, FnType> first,
	Integrator<Distribution, FnType> second,
	float marginOfError)
{

}

#endif //EXERCISES_SRC_ANALYTICAL_H_
