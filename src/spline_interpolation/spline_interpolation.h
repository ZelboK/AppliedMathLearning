//
// Created by 12893 on 2023-05-19.
//

#ifndef EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_
#define EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_

// What will the blueprints of a SplineInterpolation look like for a simple 1 dimensional
// input?

namespace spline_interpolation {

    bool isEdgeCase(int maxRows, int maxCols, int row, int col) {
        if ((row + 2 > maxRows)
            || (col + 2 > maxCols)
            || (row - 2 < 0)
            || (col - 2 < 0))
            return false;
        else
            return true;
    }

    template<class Image>
    auto getNeighboring(Image image, int row, int col) {

        for (int r = row - 2; r < row + 2; r++) {
            auto pixel = image.get(r, col); // i don't like how they are int's here. easy to mix up

        }
        for (int c = col - 2; c < row + 2; c++) {
            auto pixel = image.get(row, c); // i don't like how they are int's here. easy to mix up

        }
    }


    // refactor elsewhere?
    template<class Image>
    auto getPatch(Image image, int row, int col, double scale) {
        int maxRows = image.rows, maxCols = image.cols;

        for (int r = 0; r < maxRows; r++) {
            for (int c = 0; c < maxCols; c++) {
                if (isEdgeCase(maxRows, maxCols, r, c)) {

                } else {

                }
            }
        }

    }

    template <class ImageRegion>
    ImageRegion validateImageRegion(const ImageRegion& region) {
        // account for a strategy later on, that isn't edge pixel replication

    }

    template<class Point, class ImageRegion>
    // introduce requires clause on patch to ensure it's 4x4 & validated maybe?
    auto computeBicubic(const Point& centre, ImageRegion patch) {
        // not responsible for assuring that the image region is validated.
        // delegate that to another function
        for(int row = 0; row<patch.rows; row++) {
           for(int col = 0; col<patch.cols; col++) {
               auto below = patch.get(row+1, col);
               auto above = patch.get(row-1, col); // bad design, get not guarded
               auto right = patch.get(row, col+1);
               auto left = patch.get(row, col-1);

               auto fd_x = (right - left) / 2;
               auto fd_y = (below - above) / 2;


           }
        }
    }

    template<class Image>
    auto resize(Image image) {


        for (auto &point: image) {

            computeBicubic(point);
        }
    }
}

#endif //EXERCISES_SRC_SPLINE_INTERPOLATION_SPLINE_INTERPOLATION_H_
