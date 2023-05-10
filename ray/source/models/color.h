//
// Created by Danial javady on 2023-05-04.
//

#ifndef RAY_SOURCE_COLOR_H_
#define RAY_SOURCE_COLOR_H_

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color) {
	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}


#endif //RAY_SOURCE_COLOR_H_
