#include <functional>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "src/spline_interpolation/bicubic.h"
#include "src/models/VectorMatrix.h"
#include "external/stb_image.h"
#include "external/stb_image_write.h"

auto convert()
{
	int width, height, channels;
	unsigned char* img = stbi_load(
		"/Users/danialjavady/Desktop/RealKSM/AppliedMathLearning/shiki2.png",
		&width,
		&height,
		&channels, 0);
	if (img == nullptr)
	{
		throw std::runtime_error("Failed to load image.");
	}

// Convert image data to double and store it in a VectorMatrix
	std::vector<double> data(width * height);
	for (int i = 0; i < width * height; ++i)
	{
		data[i] = static_cast<double>(img[i]);
	}
	VectorMatrix matrix(height, width, std::move(data));

	stbi_image_free(img);
	return matrix;
}

int main()
{
	int width = 400 * 2;
	int height = 400 * 2;
	BicubicImageSplineInterpolator interpolator = BicubicImageSplineInterpolator();
	std::vector<unsigned char> data = interpolator
		.bicubic(convert(),
			Dimensions(width, height));
	if (!stbi_write_png("output.png",
		width, height, 1, data.data(), width))
	{
		throw std::runtime_error("Failed to write image.");
	}
}
