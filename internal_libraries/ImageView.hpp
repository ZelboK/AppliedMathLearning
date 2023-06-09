//
// Created by Danial javady on 2023-05-24.
//

#ifndef EXERCISES_INTERNAL_LIBRARIES_IMAGEVIEW_HPP_
#define EXERCISES_INTERNAL_LIBRARIES_IMAGEVIEW_HPP_

#include <functional>
#include <concepts>

// TODO
// Implement abstraction / view over images and their data
// Ideally no dependencies

template<class T>
concept Container =
requires(T a) {
	{ a.begin() } -> std::same_as<typename T::iterator>;
	{ a.end() } -> std::same_as<typename T::iterator>;
};

template<class T, class A>
concept ContainerOf = Container<T> && std::same_as<typename T::value_type, A>;

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

template<class Pixels, ContainerOf<Pixels> Image>
requires(std::is_arithmetic_v<Pixels>) class ImageView
{
 private:
	const Image& referenceToOwner;
 public:
	std::vector<Pixels> view;
	Dimensions dimensions;

	ImageView(Image image, Dimensions from, Dimensions to)
	{
		// (1, 1)
		// (10, 10)
		Dimensions dims = Dimensions(to.x - from.x, to.y - from.y);
		view.reserve(dims.size()); // is this what we want to do? yes right?
		int iter = 0;

		for(int i = from.x; i < to.x; i++) {
			for(int j = from.y; j < to.y; j++) {
				view.at(iter++) = &referenceToOwner.get(i, j);
			}
		}

	}

};

#endif //EXERCISES_INTERNAL_LIBRARIES_IMAGEVIEW_HPP_
