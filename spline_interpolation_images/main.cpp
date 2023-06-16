#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "src/spline_interpolation/BicubicImageSplineInterpolator.h"
#include "src/models/ImageMatrixGrayscale.h"
#include "external/stb_image.h"
#include "external/stb_image_write.h"

ImageMatrixGrayscale attainImageMatrixFromPath(const std::string &filePath) {
    int width, height, channels;
    unsigned char *img = stbi_load(
            filePath.c_str(),
            &width,
            &height,
            &channels, 0);
    if (img == nullptr) {
        throw std::runtime_error("Failed to load image.");
    }

// Convert image data to double and store it in a ImageMatrixGrayscale
    std::vector<double> data(width * height);
    for (int i = 0; i < width * height; ++i) {
        data.at(i) = static_cast<double>(img[i]);
    }
    ImageMatrixGrayscale matrix(height, width, std::move(data));

    stbi_image_free(img);
    return matrix;
}

int main() {
    int width = 270 * 2;
    int height = 197 * 2; // for now just leave scale to 2 for brevity
    int channels;
    std::string path = R"(C:\Users\devel\ksm\AppliedMathLearning\resources\ya.png)";
    BicubicImageSplineInterpolator interpolator =
            BicubicImageSplineInterpolator();

    auto imgMatrix = attainImageMatrixFromPath(path);
    auto test  = stbi_load(
            path.c_str(),
            &width,
            &height,
            &channels, 0);
    for(int i = 0; i < imgMatrix.data.size(); i++) {
        assert(imgMatrix.data.at(i)==test[i]);
    }

    std::vector<unsigned char> data =
            interpolator
                    .bicubic(attainImageMatrixFromPath(path),
                             Dimensions(width, height));

    if (!stbi_write_png("output.png",
                        width,
                        height,
                        1, data.data(), width)) {
        throw std::runtime_error("Failed to write image.");
    }
}
