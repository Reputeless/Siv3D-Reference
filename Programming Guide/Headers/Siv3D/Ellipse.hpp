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
# include "Fwd.hpp"
# include "PropertyMacro.hpp"
# include "PointVector.hpp"
# include "Circle.hpp"
# include "Rectangle.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// 楕円
	/// </summary>
	struct Ellipse
	{
#pragma warning(disable:4201)
		union
		{
			struct { Vec2 center; Vec2 axis; };
			struct { double x, y, a, b; };
		};
#pragma warning(default:4201)

		Ellipse() = default;

		explicit Ellipse(double _r)
			: Ellipse(0, 0, _r, _r) {}

		Ellipse(double _a, double _b)
			: Ellipse(0, 0, _a, _b) {}

		Ellipse(double _x, double _y, double _r)
			: Ellipse(_x, _y, _r, _r) {}

		Ellipse(double _x, double _y, double _a, double _b)
			: x(_x)
			, y(_y)
			, a(_a)
			, b(_b) {}

		explicit Ellipse(const Vec2& p)
			: Ellipse(p, { 0, 0 }) {}

		Ellipse(const Vec2& p, double _r)
			: Ellipse(p, { _r, _r }) {}

		Ellipse(const Vec2& p, double _a, double _b) 
			: Ellipse(p, { _a, _b }) {}

		Ellipse(double _x, double _y, const Vec2& _axis)
			: Ellipse({ _x, _y }, _axis) {}

		Ellipse(const Vec2& p, const Vec2& _axis)
			: center(p)
			, axis(_axis) {}

		explicit Ellipse(const Circle& circle)
			: Ellipse(circle.center, circle.r) {}

		explicit Ellipse(const RectF& rect)
			: center(rect.center)
			, axis(rect.w * 0.5, rect.h * 0.5) {}

		Ellipse& set(double _x, double _y, double _r) { setPos(_x, _y); setSize(_r);  return *this; }

		Ellipse& set(double _x, double _y, double _a, double _b) { setPos(_x, _y); setSize(_a, _b);  return *this; }

		Ellipse& set(const Vec2& pos, double _r) { setPos(pos); setSize(_r);  return *this; }

		Ellipse& set(const Vec2& pos, double _a, double _b) { setPos(pos); setSize(_a, _b);  return *this; }

		Ellipse& set(double _x, double _y, const Vec2& _axis) { setPos(_x, _y); setSize(_axis);  return *this; }

		Ellipse& set(const Vec2& pos, const Vec2& _axis) { setPos(pos); setSize(_axis);  return *this; }

		Ellipse& set(const Ellipse& ellipse) { return *this = ellipse; }

		Ellipse& setPos(double _x, double _y) { x = _x; y = _y; return *this; }

		Ellipse& setPos(const Vec2& _pos) { center = _pos; return *this; }

		Ellipse& setSize(double _r) { a = _r; b = _r; return *this; }

		Ellipse& setSize(double _a, double _b) { a = _a; b = _b; return *this; }

		Ellipse& setSize(const Vec2& _axis) { axis.set(_axis); return *this; }

		Ellipse movedBy(double _x, double _y) const { return{ center.movedBy(_x, _y), axis }; }

		Ellipse movedBy(const Vec2& v) const { return{ center.movedBy(v), axis }; }

		/// <summary>
		/// 楕円を移動させます。
		/// </summary>
		/// <param name="_x">
		/// X 方向の移動量
		/// </param>
		/// <param name="_y">
		/// Y 方向の移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Ellipse& moveBy(double _x, double _y) { center.moveBy(_x, _y); return *this; }

		/// <summary>
		/// 楕円を移動させます。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Ellipse& moveBy(const Vec2& v) { center.moveBy(v); return *this; }

		Ellipse operator + (const Vec2& v) const { return{ center + v, a, b }; }

		Ellipse operator - (const Vec2& v) const { return{ center - v, a, b }; }

		Ellipse stretched(double s) const { return{ center, a + s, b + s }; }

		double area() const { return a * b * Math::Pi; }

		Property_Get(Vec2, top) const { return{ x, y - b }; }

		Property_Get(Vec2, bottom) const { return{ x, y + b }; }

		Property_Get(Vec2, left) const { return{ x - a, y }; }

		Property_Get(Vec2, right) const { return{ x + a, y }; }

		Property_Get(RectF, boundingRect) const { return{ x - a, y - b, a * 2, b * 2 }; }

		/// <summary>
		/// 他の図形と交差しているかを調べます。
		/// </summary>
		/// <param name="shape">
		/// 他の図形
		/// </param>
		/// <returns>
		/// 交差している場合 true, それ以外の場合は false
		/// </returns>
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

		/// <summary>
		/// 楕円が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 楕円がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 楕円の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 楕円が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 楕円がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 楕円の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 楕円の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, int32 innerThickness = 1, int32 outerThickness = 0, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, int32 innerThickness = 1, int32 outerThickness = 0, const Color& color = Palette::Black) const;

		const Ellipse& draw(const Color& color = Palette::White) const;

		const Ellipse& drawFrame(double innerThickness = 1.0, double outerThickness = 0.0, const Color& color = Palette::White) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Ellipse& c)
	{
		return os << CharType('(') << c.x << CharType(',') << c.y << CharType(',') << c.a << CharType(',') << c.b << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Ellipse& c)
	{
		CharType unused;
		return is >> unused >> c.x >> unused >> c.y >> unused >> c.a >> unused >> c.b >> unused;
	}
}
