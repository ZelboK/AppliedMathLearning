//
// Created by 12893 on 2023-05-09.
//

#ifndef EXERCISES_PBRT_EXERCISES_SRC_CONSTANTS_H_
#define EXERCISES_PBRT_EXERCISES_SRC_CONSTANTS_H_

namespace constants {
	float eulers = 2.7182;

	float pi = 3.1416;

	std::function<float(float)> standardNormalDistPdf = [](float x)
	{
	  float mean = 0;
	  float standardDeviation = 1;
	  float exp = (-0.5) * std::pow(((x - mean) / standardDeviation), 2);
	  float eulerRightHandSide = std::pow(eulers, exp);
	  float leftHandSide = 1 / (standardDeviation * std::sqrt(2 * pi));
	  return leftHandSide * eulerRightHandSide;
	};

	std::function<float(float)> createNonStandardNormalDistPdf(float mean,
		float standardDeviation) {
		return	[&](float x)
		{
		  float exp = (-0.5) * std::pow(((x - mean) / standardDeviation), 2);
		  float eulerRightHandSide = std::pow(eulers, exp);
		  float leftHandSide = 1 / (standardDeviation * std::sqrt(2 * pi));
		  return leftHandSide * eulerRightHandSide;
		};
	}
}

#endif //EXERCISES_PBRT_EXERCISES_SRC_CONSTANTS_H_
