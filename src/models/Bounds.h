//
// Created by Danial javady on 2023-05-08.
//

#ifndef EXERCISES_SRC_BOUNDS_H_
#define EXERCISES_SRC_BOUNDS_H_

// used for PBRT textbook
struct Bounds {
	float lower;
	float upper;

	Bounds(float lower, float upper): lower(lower), upper(upper) {

	}
};

#endif //EXERCISES_SRC_BOUNDS_H_
