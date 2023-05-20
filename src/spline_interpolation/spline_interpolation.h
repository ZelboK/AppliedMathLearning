//
// Created by 12893 on 2023-05-19.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_

#include "src/concepts/general.h"
// What will the blueprints of a SplineInterpolation look like for a simple 1 dimensional
// input?

namespace spline_interpolation
{

	bool isEdgeCase(int maxRows, int maxCols, int row, int col)
	{
		if ((row + 1 > maxRows)
			|| (col + 1 > maxCols)
			|| (row - 1 < 0)
			|| (col - 1 < 0))
			return false;
		else
			return true;
	}

	// refactor elsewhere?
	template<class Image>
	auto getPatch(Image image, int row, int col, double scale)
	{
		int maxRows = image.rows, maxCols = image.cols;
	// will this work...?	auto [maxRows, maxCols] = image;

		for()
	}

	// one dimensional
	template<class Data, ContainerOf<Data> Dataset>
	requires std::is_arithmetic_v<Data>
	auto computeSplineInterpolation(Dataset dataset)
	{

		for (auto& point : dataset)
		{

		}
	}

	template<class Image>
	auto resizeImage(Image image, double scale)
	{
	}

	template<class Image>
	auto bicubicInterpolation(Image image)
	{

	}

}

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_
