//
// Created by devel on 2023-05-26.
//

#ifndef EXERCISES_VECTORMATRIX_H
#define EXERCISES_VECTORMATRIX_H

#include <vector>

struct VectorMatrix {
    int rows;
    int cols;

    std::vector<double> data;

    VectorMatrix(int rows,
                 int cols,
                 std::vector<double> data) :
            rows(rows),
            cols(cols),
            data(std::move(data)) {}

    // f(row, colSize, col) = ((row-1) * colSize) + col - 1;
    [[nodiscard]] int getPos(int row, int col) const {
        return ((row-1)*cols)+col-1;
    }

    // getPos(row, colSize, col)
    //
};
#endif //EXERCISES_VECTORMATRIX_H
