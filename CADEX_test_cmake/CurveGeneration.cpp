#include "CurveGeneration.h"
#include <cassert>
#include <functional>
#include <vector>

namespace curves_ns
{
	using std::uniform_real_distribution;
	using std::vector;
	using std::reference_wrapper;

	double RandomNonZeroReal(double min_val, double max_val, mt19937& randomiser);

	class RandomCurveMaker
	{
	public:
		RandomCurveMaker() = default;
		virtual ~RandomCurveMaker() = default;
		virtual unique_ptr<Curve> MakeRandomCurve(double max_radius, double max_hellix_step, mt19937& randomiser) const = 0;

		const static vector<reference_wrapper<const RandomCurveMaker>> curve_makers;
	};

	class RandomCircleMaker final : public RandomCurveMaker
	{
	public:
		unique_ptr<Curve> MakeRandomCurve(double max_radius, double, mt19937& randomiser) const override;

		const static RandomCircleMaker maker;
	};

	class RandomEllipseMaker final : public RandomCurveMaker
	{
	public:
		unique_ptr<Curve> MakeRandomCurve(double max_radius, double, mt19937& randomiser) const override;

		const static RandomEllipseMaker maker;
	};

	class RandomHellixMaker final : public RandomCurveMaker
	{
	public:
		unique_ptr<Curve> MakeRandomCurve(double max_radius, double max_hellix_step, mt19937& randomiser) const override;

		const static RandomHellixMaker maker;
	};

	//=============vv definitions vv===================================================================================


	unique_ptr<Curve> MakeRandomCurve(double max_radius, double max_hellix_step, mt19937& randomiser)
	{
		int makers_count = static_cast<int>(RandomCurveMaker::curve_makers.size());

		assert(makers_count != 0);

		const RandomCurveMaker& maker = RandomCurveMaker::curve_makers[randomiser() % makers_count];

		return maker.MakeRandomCurve(max_radius, max_hellix_step, randomiser);
	}

	unique_ptr<Curve> MakeRandomCircle(double max_radius, mt19937& randomiser)
	{
		return unique_ptr<Curve>(new Circle(RandomNonZeroReal(0, max_radius, randomiser)));
	}

	unique_ptr<Curve> RandomCircleMaker::MakeRandomCurve(double max_radius, double, mt19937& randomiser) const
	{
		return MakeRandomCircle(max_radius, randomiser);
	}

	unique_ptr<Curve> MakeRandomEllipse(double max_radius, mt19937& randomiser)
	{
		return unique_ptr<Curve>(new Ellipse(RandomNonZeroReal(0, max_radius, randomiser),
			RandomNonZeroReal(0, max_radius, randomiser)));
	}

	unique_ptr<Curve> RandomEllipseMaker::MakeRandomCurve(double max_radius, double, mt19937& randomiser) const
	{
		return MakeRandomEllipse(max_radius, randomiser);
	}

	unique_ptr<Curve> MakeRandomHellix(double max_radius, double max_hellix_step, mt19937& randomiser)
	{
		return unique_ptr<Curve>(new Hellix(RandomNonZeroReal(0, max_radius, randomiser),
			RandomNonZeroReal(-max_hellix_step, max_hellix_step, randomiser)));
	}

	unique_ptr<Curve> RandomHellixMaker::MakeRandomCurve(double max_radius, double max_hellix_step, mt19937& randomiser) const
	{
		return MakeRandomHellix(max_radius, max_hellix_step, randomiser);
	}

	double RandomNonZeroReal(double min_val, double max_val, mt19937& randomiser)
	{
		double val;
		do
		{
			val = uniform_real_distribution<double>(min_val, max_val)(randomiser);
		} while (val == 0);
		return val;
	}

	const vector<reference_wrapper<const RandomCurveMaker>> RandomCurveMaker::curve_makers =
	{
		RandomCircleMaker::maker,
		RandomEllipseMaker::maker,
		RandomHellixMaker::maker,
	};

	const RandomCircleMaker RandomCircleMaker::maker = {};
	const RandomEllipseMaker RandomEllipseMaker::maker = {};
	const RandomHellixMaker RandomHellixMaker::maker = {};
}
