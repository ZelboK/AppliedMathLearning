//
// Created by Danial javady on 2023-05-29.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINEEQUATIONS_H_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINEEQUATIONS_H_

#include <vector>

// should this be agnostic to dimension?
struct SplineEquations
{
	std::vector<double> pixelIntensities;
	std::vector<double> xGradient;
	std::vector<double> yGradient;
	std::vector<double> xyCrossDerivative;

	SplineEquations(std::vector<double>& pixelIntensities,
		std::vector<double>& xGradient,
		std::vector<double>& yGradient,
		std::vector<double>& xyCrossDerivative)
		: pixelIntensities(std::move(pixelIntensities)),
		  xGradient(std::move(xGradient)),
		  yGradient(std::move(yGradient)),
		  xyCrossDerivative(std::move(xyCrossDerivative))
	{
	}

};

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINEEQUATIONS_H_
