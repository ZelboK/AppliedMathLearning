#include <iostream>
#include <functional>
#include "src/bounds.h"
#include "src/spline_interpolation/spline_interpolation.h"

template <class B, class A>
float function(std::function<B(A)> fn) {

}

template <class A>
float computeCdfUnaryPdf(std::function<A(A)> pdf, Bounds bounds) {
	auto atLower = pdf(bounds.lower);
	auto atHigher = pdf(bounds.upper);


}


int main()
{
	std::function<float(float)> uniform = [](float x) {
		if(x<0 || x>1) {
			return 0;
		} else {
			return 1;
		}
	};
	std::cout << "Hello, World!" << std::endl;
	return 0;
}
