//
// Created by devel on 2023-05-27.
//

#ifndef EXERCISES_DIMENSIONS_H
#define EXERCISES_DIMENSIONS_H

struct Dimensions
{
    int x;
    int y;

    Dimensions(int x, int y) : x(x), y(y)
    {
    }

    [[nodiscard]] size_t size() const {
        return x*y;
    }
};

#endif //EXERCISES_DIMENSIONS_H
