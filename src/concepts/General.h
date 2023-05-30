//
// Created by 12893 on 2023-05-19.
//

#ifndef EXERCISES_SRC_CONCEPTS_GENERAL_H_
#define EXERCISES_SRC_CONCEPTS_GENERAL_H_

#include <functional>
#include <concepts>
// idk how i feel about the naming of this


template <class T>
concept Container = requires(T a) {
	{ a.begin() } -> std::same_as<typename T::iterator>;
	{ a.end() } -> std::same_as<typename T::iterator>;
};

template <class T, class A>
concept ContainerOf = Container<T> && std::same_as<typename T::value_type, A>;

#endif //EXERCISES_SRC_CONCEPTS_GENERAL_H_
