#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "src/spline_interpolation/BicubicImageSplineInterpolator.h"
#include "src/models/ImageMatrixGrayscale.h"
#include "external/stb_image.h"
#include "external/stb_image_write.h"


ImageMatrixGrayscale attainImageMatrixFromPath(const std::string& filePath)
{
	int width, height, channels;
	unsigned char* img = stbi_load(
		filePath.c_str(),
		&width,
		&height,
		&channels, 0);
	if (img == nullptr)
	{
		throw std::runtime_error("Failed to load image.");
	}

// Convert image data to double and store it in a ImageMatrixGrayscale
	std::vector<double> data(width * height);
	for (int i = 0; i < width * height; ++i)
	{
		data.at(i) = static_cast<double>(img[i]);
	}
	ImageMatrixGrayscale matrix(height, width, std::move(data));

	stbi_image_free(img);
	return matrix;
}

int main()
{
	int width = 400 * 2;
	int height = 400 * 2; // for now just leave scale to 2 for brevity
	std::string filePath = "/Users/danialjavady/Desktop/RealKSM/AppliedMathLearning/shiki2.png";
	BicubicImageSplineInterpolator interpolator = BicubicImageSplineInterpolator();
	std::vector<unsigned char> data =
		interpolator
			.bicubic(attainImageMatrixFromPath(filePath), Dimensions(width, height));

	if (!stbi_write_png("output.png",
		width, height, 1, data.data(), width))
	{
		throw std::runtime_error("Failed to write image.");
	}
}
