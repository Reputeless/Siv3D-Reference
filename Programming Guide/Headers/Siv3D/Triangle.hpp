//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iostream>
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr double Sqrt3 = 1.73205080756887729353; // std::sqrt(3.0);
	}

	/// <summary>
	/// 三角形
	/// </summary>
	struct Triangle
	{
#pragma warning(disable:4201)
		union
		{
			struct { Vec2 p0, p1, p2; };
			struct { Vec2 p[3]; };
		};
#pragma warning(default:4201)

		Triangle() = default;

		explicit Triangle(double sides)
			: p0(0.0, -1.0 / detail::Sqrt3 * sides)
			, p1(sides * 0.5, sides / (2.0*detail::Sqrt3))
			, p2(-p1.x, p1.y) {}

		Triangle(double sides, double angle);

		Triangle(double x, double y, double sides)
			: Triangle({ x, y }, sides) {}

		Triangle(const Vec2& pos, double sides);

		Triangle(double x, double y, double sides, double angle)
			: Triangle({ x, y }, sides, angle) {}

		Triangle(const Vec2& pos, double sides, double angle);

		Triangle(double x0, double y0, double x1, double y1, double x2, double y2)
			: p0(x0, y0)
			, p1(x1, y1)
			, p2(x2, y2) {}

		Triangle(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2)
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		Triangle& set(double x0, double y0, double x1, double y1, double x2, double y2)
		{
			p0.set(x0, y0);
			p1.set(x1, y1);
			p2.set(x2, y2);
			return *this;
		}

		Triangle& set(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2)
		{
			p0.set(_p0);
			p1.set(_p1);
			p2.set(_p2);
			return *this;
		}

		Triangle& set(const Triangle& triangle) { return *this = triangle; }

		Triangle movedBy(const Vec2& v) const
		{
			return{ p0.movedBy(v), p1.movedBy(v), p2.movedBy(v) };
		}

		Triangle movedBy(double x, double y) const { return movedBy(Vec2(x, y)); }

		Triangle& moveBy(double x, double y) { return moveBy({ x, y }); }

		Triangle& moveBy(const Vec2& v);

		Triangle& setCentroid(double x, double y) { return setCentroid({ x, y }); }

		Triangle& setCentroid(const Vec2& pos);

		Triangle rotated(double angle) const;

		Triangle rotatedAt(double x, double y, double angle) const;

		Triangle rotatedAt(const Vec2& pos, double angle) const;

		Triangle operator + (const Vec2& v) const { return{ p0 + v, p1 + v, p2 + v }; }

		Triangle operator - (const Vec2& v) const { return{ p0 - v, p1 - v, p2 - v }; }

		double area() const;

		double perimeter() const;

		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape>
		bool contains(const Shape& shape) const
		{
			return Geometry2D::Within(shape, *this);
		}

		Vec2 centroid() const
		{
			return (p0 + p1 + p2) / 3.0;
		}

		/// <summary>
		/// 三角形が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 三角形がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 三角形の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 三角形が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 三角形がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 三角形の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 三角形の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		const Triangle& draw(const Color& color = Palette::White) const;

		const Triangle& draw(const Color(&colors)[3]) const;

		const Triangle& drawFrame(double thickness = 1.0, const Color& color = Palette::White) const;

		Polygon asPolygon() const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Triangle& triangle)
	{
		return	os << CharType('(')
			<< triangle.p0 << CharType(',')
			<< triangle.p1 << CharType(',')
			<< triangle.p2 << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Triangle& triangle)
	{
		CharType unused;
		return	is >> unused
			>> triangle.p0 >> unused
			>> triangle.p1 >> unused
			>> triangle.p2 >> unused;
	}
}
