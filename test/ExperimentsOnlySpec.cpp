//
// Created by Danial Javady on 2023-05-24.
//
// This spec is not intended to assure / prove anything.
// It simply exists, so I can just play around
// Look at it similar to doing math problems in a textbook in a notebook

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

static std::vector<double> extractColsForXDerivation(const std::vector<double>& row)
{
	if (row.size() < 2)
	{
		throw std::invalid_argument("Input vector must contain at least two elements.");
	}

	std::vector<double> differentials;
	differentials.reserve(row.size());  // This can help performance by avoiding reallocations

	differentials.push_back(
		(row.at(1) - row.at(0)) / 2
	);
	for (std::size_t i = 1; i < row.size() - 1; i++)
	{

		double diff = row.at(i + 1) - row.at(i - 1);
		std::cout << diff / 2 << " on i: " << i << ", " << std::endl;
		differentials.push_back(diff / 2);
	}
	auto last = (row.at(row.size() - 1) - row.at(row.size() - 2))/2;
	differentials.push_back(last);
	std::cout << std::endl << "last: " << last << std::endl;
	return differentials;
}
static std::vector<double> extractColsForXDerivationViaFP(const std::vector<double>& row)
{
	if (row.size() < 2)
	{
		throw std::invalid_argument("Input vector must contain at least two elements.");
	}

	std::vector<double> differentials;
	differentials.reserve(row.size());

	auto calculateDifferential = [](double left, double right)
	{ return right - left; };
	differentials.push_back(calculateDifferential(row[0], row[1]));

	std::transform(
		std::next(row.begin(), 1),
		std::prev(row.end(), 1),
		std::back_inserter(differentials),
		[&](const auto& current)
		{
		  return calculateDifferential(*(std::prev(&current)), *(std::next(&current)));
		});

	differentials.push_back(calculateDifferential(row[row.size() - 2], row[row.size() - 1]));

	return differentials;
}

// matrices are going to be organized in row-order if they're 2 dimensional vectors.
// the alternative is to just have a 1 dimensional std::vector, which could be easier to reason about
static std::vector<std::vector<double>> extractRowsForYDerivation(
	const std::vector<std::vector<double>>& matrix)
{
	// okay. So i need to formulate some kind of algorithm that will allow me to access things by column.
	// this will likely be inefficient due to how hardware works. Figure that out later.


	// There exists as many columns as there are in each row. There exists no validation to check if the
	// columns are the same across all rows, but don't bother with that.
	// You want to get the Y derivative. You don't even need to like, ... I think you can just iterate
	// over the neighborhood and calculate the derivatives. You just have to check boundaries.

	for (int i = 0; i < matrix.size(); i++)
	{
		auto curRow = matrix.at(i);
		for (int j = 0; j < curRow.size(); j++)
		{
			auto above = curRow[j - 1];
			auto below = curRow[j + 1];
			auto diff = (below - above) / 2;
		}
	}

}

TEST_CASE("EXPERIMENTS ONLY")
{
	std::vector<std::vector<double>> matrix = {{ 1, 3, 6 },
											   { 9, 5, 2 },
											   { 1, 2, 4 }};
	double expected_r0c0 = (matrix.at(0).at(1) - matrix.at(0).at(0)) / 2;
	double expected_r0c1 = (matrix.at(0).at(2) - matrix.at(0).at(0)) / 2;
	double expected_r0c2 = (matrix.at(0).at(2) - matrix.at(0).at(1)) / 2;

	double expected_r1c0 = (matrix.at(1).at(1) - matrix.at(1).at(0)) / 2;
	double expected_r1c1 = (matrix.at(1).at(2) - matrix.at(1).at(0)) / 2;
	double expected_r1c2 = (matrix.at(1).at(2) - matrix.at(1).at(1)) / 2;

	double expected_r2c0 = (matrix.at(2).at(1) - matrix.at(2).at(0)) / 2;
	double expected_r2c1 = (matrix.at(2).at(2) - matrix.at(2).at(0)) / 2;
	double expected_r2c2 = (matrix.at(2).at(2) - matrix.at(2).at(1)) / 2;

	std::vector<std::vector<double>> expectedXDeriv =
		{{ expected_r0c0, expected_r0c1, expected_r0c2 },
		 { expected_r1c0, expected_r1c1, expected_r1c2 },
		 { expected_r2c0, expected_r2c1, expected_r2c2 }};


//
//	SECTION("3x3 first derivative of image discrete values, edge replication strategy")
//	{
//		for (auto& row : expectedXDeriv)
//		{
//			for (auto& col : row)
//			{
//				std::cout << col << ", ";
//			}
//			std::cout << std::endl;
//		}
//		std::cout << "next test" << std::endl << std::endl;
//	}

	SECTION("Differentiate against x axis")
	{

		std::vector<std::vector<double>> actual;

		for(int i = 0; i<matrix.size(); i++) {
			actual.push_back(extractColsForXDerivation(matrix.at(i)));
		}

		for (auto& row : matrix)
		{
			for (auto& col : row)
			{
				std::cout << col << ", ";

			}
			std::cout << std::endl;

		}

		for (auto& row : actual)
		{
			for (auto& col : row)
			{
				std::cout << col << ", ";
			}
			std::cout << std::endl;
		}
		//	std::cout << "next test" << std::endl  << std::endl;

		for (int i = 0; i < actual.size(); i++)
		{
			std::vector<double> row = actual.at(i);
			for (int j = 0; j < row.size(); j++)
			{
				double expected = expectedXDeriv.at(i).at(j);
				double actualValue = actual.at(i).at(j);
				//	std::cout << i << "i vs j: " << j << std::endl;
				//	std::cout << expected << "expected vs actual: " << actualValue << std::endl;
				//	REQUIRE(actualValue == expected);
			}
		}

	}
}



