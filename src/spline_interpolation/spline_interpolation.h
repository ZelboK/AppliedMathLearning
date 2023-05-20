//
// Created by 12893 on 2023-05-19.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_

#include "src/concepts/general.h"
// What will the blueprints of a SplineInterpolation look like for a simple 1 dimensional
// input?

namespace spline_interpolation {

	// one dimensional
	template <class Data, ContainerOf<Data> Dataset>
	requires std::is_arithmetic_v<Data>
	auto computeSplineInterpolation(Dataset dataset) {

		for(auto&point : dataset) {

		}
	}
}


#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_
