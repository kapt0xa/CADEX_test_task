#pragma once
#include <memory>
#include <stdexcept>

namespace curves_ns
{
	struct Vector3
	{
		double x;
		double y;
		double z;
	};

	struct PointAndDer
	{
		Vector3 point;
		Vector3 derivative;
	};

	class Curve
	{
	public:
		Curve() = default;
		Curve(Curve&&) = default;
		Curve(const Curve&) = default;
		Curve& operator = (Curve&&) = default;
		Curve& operator = (const Curve&) = default;
		virtual ~Curve() = default;

		virtual PointAndDer GetPointState(double t) const = 0;
	};

	class Circle final : public Curve
	{
		double radius;
	public:
		Circle(double radius_val /* positive only */);

		PointAndDer GetPointState(double t) const override;

		double GetRadius() const noexcept;
		void SetRadius(double val /* positive only */);

	private:
	};

	class Ellipse final : public Curve
	{
		double radius_x;
		double radius_y;
	public:
		Ellipse(double radius_x_val /* positive only */, double radius_y_val /* positive only */);

		PointAndDer GetPointState(double t) const override;

		double GetRadiusX() const noexcept;
		void SetRadiusX(double val /* positive only */);

		double GetRadiusY() const noexcept;
		void SetRadiusY(double val /* positive only */);

	private:
	};

	class Hellix final : public Curve
	{
		double radius;
		double step;
		double step_per_radian;
	public:
		Hellix(double radius_val /* positive only */, double step_val /* non-zero */);

		PointAndDer GetPointState(double t) const override;

		double GetRadius() const noexcept;
		void SetRadius(double val /* positive only */);

		double GetStep() const noexcept;
		void SetStep(double val /* non-zero */);

	private:
	};

	class IncorrectCurveParametr : std::invalid_argument
	{
	public:
		IncorrectCurveParametr(const char * const message);
		using invalid_argument::what;
	};
}
