#pragma once
#include "Curve.h"
#include <ostream>
#include <string_view>

namespace curves_ns
{
	using std::ostream;
	using namespace std::string_view_literals;
	using std::string_view;

	ostream& operator << (ostream& out, const Curve& curve);

	template<typename NumIOManipulator>
	class VectorPrinter
	{
	public:
		string_view open_bracket = "{"sv;
		string_view close_bracket = "}"sv;
		string_view cord_separation = ", "sv;
		NumIOManipulator io_manipulator;

		void Print(const Vector3& val, ostream& out) const;
	};

	template<typename NumIOManipulator>
	class PointAndDerPrinter
	{
	public:
		string_view point_prefix = ""sv;
		string_view derivative_prefix = ""sv;
		string_view separator = ", "sv;
		VectorPrinter<NumIOManipulator> vector_printer;

		void Print(const PointAndDer& val, ostream& out) const;
	};

	class NoManip
	{
		void operator()(const ostream&) const;
	};

	// out << setw(10) << fixed
	class DefauldNumManip
	{
	public:
		void operator()(ostream& out) const;
	};

	// out << setw(10)
	class DefauldStringManip
	{
	public:
		void operator()(ostream& out) const;
	};

	using VectorPrinterNoManip = VectorPrinter<NoManip>;
	using VectorPrinterDefauld = VectorPrinter<DefauldNumManip>;

	using PointAndDerPrinterNoManip = PointAndDerPrinter<NoManip>;
	using PointAndDerPrinterDefauld = PointAndDerPrinter<DefauldNumManip>;

	//====vvv template implementation vvv===================================================================================================

	template<typename NumIOManipulator>
	inline void VectorPrinter<NumIOManipulator>::Print(const Vector3& val, ostream& out) const
	{
		out << open_bracket;
		io_manipulator(out);
		out << val.x << cord_separation;
		io_manipulator(out);
		out << val.y << cord_separation;
		io_manipulator(out);
		out << val.z;
		out << close_bracket;
	}

	template<typename NumIOManipulator>
	inline void PointAndDerPrinter<NumIOManipulator>::Print(const PointAndDer& val, ostream& out) const
	{
		out << point_prefix;
		vector_printer.Print(val.point, out);
		out << separator;
		out << derivative_prefix;
		vector_printer.Print(val.derivative, out);
	}
}

