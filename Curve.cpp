#define _USE_MATH_DEFINES

#include "Curve.h"

#include <cmath>

constexpr double turn = 2 * M_PI;

namespace curves_ns
{
	using std::sin;
	using std::cos;

	//==vv function definitions vv=================================================================

	//-----v Circle v----

	Circle::Circle(double radius_val)
		: radius(radius_val)
	{
		if (radius <= 0)
		{
			throw IncorrectCurveParametr("circle should have positive radius");
		}
	}

	PointAndDer Circle::GetPointState(double t) const
	{
		double sin_r = sin(t) * radius;
		double cos_r = cos(t) * radius;

		return
		{
			{ cos_r, sin_r, 0},
			{-sin_r, cos_r, 0}
		};
	}

	double Circle::GetRadius() const noexcept
	{
		return radius;
	}

	void Circle::SetRadius(double val)
	{
		if (val > 0)
		{
			radius = val;
		}
		else
		{
			throw IncorrectCurveParametr("circle should have positive radius");
		}
	}

	//----v Ellipse v-----

	Ellipse::Ellipse(double radius_x_val, double radius_y_val)
		: radius_x(radius_x_val)
		, radius_y(radius_y_val)
	{
		if (radius_x <= 0 || radius_y <= 0)
		{
			throw IncorrectCurveParametr("ellipse should have positive radiuses");
		}
	}

	PointAndDer Ellipse::GetPointState(double t) const
	{
		double sin_val = sin(t);
		double cos_val = cos(t);

		return
		{
			{ cos_val * radius_x, sin_val * radius_y, 0},
			{-sin_val * radius_x, cos_val * radius_y, 0}
		};
	}

	double Ellipse::GetRadiusX() const noexcept
	{
		return radius_x;
	}

	void Ellipse::SetRadiusX(double val)
	{
		if (val > 0)
		{
			radius_x = val;
		}
		else
		{
			throw IncorrectCurveParametr("ellipse should have positive radiuses");
		}
	}

	double Ellipse::GetRadiusY() const noexcept
	{
		return radius_y;
	}

	void Ellipse::SetRadiusY(double val)
	{
		if (val > 0)
		{
			radius_y = val;
		}
		else
		{
			throw IncorrectCurveParametr("ellipse should have positive radiuses");
		}
	}

	//----v Hellix v------

	Hellix::Hellix(double radius_val, double step_val)
		: radius(radius_val)
		, step(step_val)
		, step_per_radian(step_val / turn)
	{
		if (radius <= 0)
		{
			throw IncorrectCurveParametr("hellix should have positive radius");
		}
		if (step_per_radian == 0)
		{
			throw IncorrectCurveParametr("hellix cant have zero step");
		}
	}

	PointAndDer Hellix::GetPointState(double t) const
	{
		double sin_r = sin(t) * radius;
		double cos_r = cos(t) * radius;

		return
		{
			{ cos_r, sin_r, t * step_per_radian},
			{-sin_r, cos_r, step_per_radian}
		};
	}

	double Hellix::GetRadius() const noexcept
	{
		return radius;
	}

	void Hellix::SetRadius(double val)
	{
		if (val > 0)
		{
			radius = val;
		}
		else
		{
			throw IncorrectCurveParametr("hellix should have positive radius");
		}
	}

	double Hellix::GetStep() const noexcept
	{
		return step;
	}

	void Hellix::SetStep(double val)
	{
		double per_radian = val / turn;
		if (per_radian != 0)
		{
			step = val;
			step_per_radian = per_radian;
		}
		else
		{
			throw IncorrectCurveParametr("hellix cant have zero step");
		}
	}
	
	//----v other v-----

	IncorrectCurveParametr::IncorrectCurveParametr(const char* const message)
		:invalid_argument(message)
	{
	}
}