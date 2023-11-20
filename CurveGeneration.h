#pragma once

#include "Curve.h"

#include <random>
#include <vector>

namespace curves_ns
{
	using std::mt19937;
	using std::unique_ptr;

	unique_ptr<Curve> MakeRandomCurve(double max_radius, double max_hellix_step, mt19937& randomiser);
	//
	// how to check list of possible types of curves?
	// CurveGeneration.cpp -> ctrl + F "curve_makers"
	//

	unique_ptr<Curve> MakeRandomCircle(double max_radius, mt19937& randomiser);
	unique_ptr<Curve> MakeRandomEllipse(double max_radius, mt19937& randomiser);
	unique_ptr<Curve> MakeRandomHellix(double max_radius, double max_hellix_step, mt19937& randomiser);
}
