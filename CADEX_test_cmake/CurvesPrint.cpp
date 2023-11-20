#include "CurvesPrint.h"
#include <iomanip>
#include <unordered_map>
#include <typeinfo>
#include <iostream>

namespace curves_ns
{
	using std::setw;
	using std::unordered_map;
	using std::type_info;
	using std::out_of_range;
	using std::cerr;
	using std::endl;
	using std::reference_wrapper;

	void NoManip::operator()(const ostream&) const
	{}

	void DefauldNumManip::operator()(ostream& out) const
	{
		out << setw(10) << std::fixed;
	}

	void DefauldStringManip::operator()(ostream& out) const
	{
		out << setw(10);
	}

	class BaseCurvePrinter
	{
	public:
		BaseCurvePrinter() = default;
		virtual ~BaseCurvePrinter() = default;

		virtual void Print(ostream& out, const Curve& curve) const = 0;
	};

	template<typename CurveType>
	class CurvePrinter : public BaseCurvePrinter
	{
	public:

		void Print(ostream& out, const Curve& curve) const override;

		static const CurvePrinter<CurveType> printer;
	};

	using TypeInfoRef = reference_wrapper<const std::type_info>;

	struct TypeInfoHasher {
		std::size_t operator()(TypeInfoRef the_type_info) const
		{
			return the_type_info.get().hash_code();
		}
	};

	struct TypeInfoEqualTo {
		bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
		{
			return lhs.get() == rhs.get();
		}
	};

	const std::unordered_map<TypeInfoRef, reference_wrapper<const BaseCurvePrinter>, TypeInfoHasher, TypeInfoEqualTo> type_printers =
	{
		{typeid(Circle),	dynamic_cast<const BaseCurvePrinter&>(CurvePrinter<Circle>::printer)},
		{typeid(Ellipse),	dynamic_cast<const BaseCurvePrinter&>(CurvePrinter<Ellipse>::printer)},
		{typeid(Hellix),	dynamic_cast<const BaseCurvePrinter&>(CurvePrinter<Hellix>::printer)},
	};

	ostream& operator<<(ostream& out, const Curve& curve)
	{
		type_printers.at(typeid(curve)).get().Print(out, curve);
		return out;
	}

	template<>
	void CurvePrinter<Circle>::Print(ostream& out, const Curve& curve) const
	{
		auto& circle = dynamic_cast<const Circle&>(curve);
		out << "circle: R"sv << circle.GetRadius();
	}

	template<>
	void CurvePrinter<Ellipse>::Print(ostream& out, const Curve& curve) const
	{
		auto& ellipse = dynamic_cast<const Ellipse&>(curve);
		out << "ellipse: RX"sv << ellipse.GetRadiusX() << ", RY"sv << ellipse.GetRadiusY();
	}

	template<>
	void CurvePrinter<Hellix>::Print(ostream& out, const Curve& curve) const
	{
		auto& hellix = dynamic_cast<const Hellix&>(curve);
		out << "hellix: R" << hellix.GetRadius() << ", S" << hellix.GetStep();
	}

	template<typename CurveType>
	const CurvePrinter<CurveType> CurvePrinter<CurveType>::printer = CurvePrinter<CurveType>();
}
