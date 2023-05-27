//
// Created by Danial javady on 2023-05-10.
//

#ifndef EXERCISES_SRC_INTEGRATOR_H_
#define EXERCISES_SRC_INTEGRATOR_H_
#include <functional>
#include "models/bounds.h"



// i do not like duck typing : (
template <class Distribution, class FnType>
struct Integrator {
	Distribution dist;
	std::function<FnType> pdf;
	int samples;
	Bounds bounds;

	auto integrate() {

	}
};

#endif //EXERCISES_SRC_INTEGRATOR_H_
