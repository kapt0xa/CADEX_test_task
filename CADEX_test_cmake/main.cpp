//	to do:
//	1)
//	3d curve (double t -> point & derivative)
//		circle (only radius)
//		ellipse (only x-radius and y-radius)
//		hellix (spiral?) (only radius and step)
//	2)
//	fill a container (like vector or list) with that curves, but with random parametrs
// 
//	3)
//	print cords of points & derivatives of all the curves at t = pi/4
//	
//	4)
//	fill a second container that would contain only circles from 1_rst container (share, no copy)
//	
//	5)
//	sort the container with sicles from small to big (by radius)
//  
//  6) 
//	compute the total sum of all curves in the second container
// 
//	*7) 
//	split code into parts and make .dll out of curves
// 
//	*8)
//  make summing of radiuses paralell
//

#define _USE_MATH_DEFINES
#include "Curve.h"
#include "CurvesPrint.h"
#include "CurveGeneration.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <chrono>
#include <cassert>
#include <algorithm>
#include <execution>
#include <numeric>
#include <iomanip>

constexpr double pi = M_PI;

using namespace std;
using namespace curves_ns;

int main()
{

	//---vvv 2 vvv---
	
	//
	// 2. Populate a container (e.g. vector or list) of objects of these types created in random manner with random parameters.
	// what is the size of container???? i'll just take input from cin.
	//
	int curves_count = 0;
	cin >> curves_count;
	if (curves_count < 0)
	{
		throw invalid_argument("count of curves can't be negative");
	}

	vector<shared_ptr<Curve>> curves;
	mt19937 randomizer (std::time(nullptr));
	curves.reserve(static_cast<size_t>(curves_count));

	for (int i = 0; i < curves_count; ++i)
	{
		curves.push_back(MakeRandomCurve(100, 10, randomizer));
	}

	//---vvv 3 vvv---

	//
	// 3. Print coordinates of points and derivatives of all curves in the container at t=PI/4.
	// which format of output? am i free to choose format of printed values?
	//

	PointAndDerPrinterDefauld point_printer;

	for (const shared_ptr<Curve>& curve : curves)
	{
		point_printer.Print(curve->GetPointState(pi / 4), cout);
		cout << '\n';
	}

	//---vvv 4 vvv---

	vector<shared_ptr<Curve>> circles;

	for (const shared_ptr<Curve>& curve : curves)
	{
		if (dynamic_cast<Circle*>(curve.get()) != nullptr)
		{
			circles.push_back(curve);
		}
	}

	//---vvv 5 vvv---

	sort(circles.begin(), circles.end(), 
		[](const shared_ptr<Curve>& l, const shared_ptr<Curve>& r)
		{
			return	dynamic_cast<Circle&>(*l).GetRadius() <
					dynamic_cast<Circle&>(*r).GetRadius();
		});

	//---vvv 6 vvv---

	//
	// 3. Print coordinates of points and derivatives of all curves in the container at t = PI / 4
	//    ^ explicitly said to print
	// 6. Compute the total sum of radii of all curves in the second container
	//    print or not to print - that is the question

	double raduis_summ =
		transform_reduce(execution::par, circles.begin(), circles.end(), 0.0,
		[](double l, double r)
		{
			return l + r;
		},
		[](const shared_ptr<Curve>& circle)
		{
			return dynamic_cast<Circle&>(*circle).GetRadius();
		}
		);
	cout << raduis_summ << endl;
}