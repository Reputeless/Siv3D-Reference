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
# include "Color.hpp"
# include "PropertyMacro.hpp"
# include "Format.hpp"
# include "Geometry2D.hpp"

namespace s3d
{
	/// <summary>
	/// 点、またはサイズ
	/// </summary>
	struct Point
	{
		using value_type = int32;

		value_type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Point() = default;

		constexpr Point(int32 _x, int32 _y)
			: x(_x)
			, y(_y) {}

		template <class U, class V>
		constexpr Point(U _x, V _y)
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y)) {}

		/// <summary>
		/// Point{ x, x }
		/// </summary>
		constexpr Point xx() const
		{
			return{ x, x };
		}

		/// <summary>
		/// Point{ x, y }
		/// </summary>
		constexpr Point xy() const
		{
			return *this;
		}

		/// <summary>
		/// Point{ y, x }
		/// </summary>
		constexpr Point yx() const
		{
			return{ y, x };
		}

		/// <summary>
		/// Point{ y, y }
		/// </summary>
		constexpr Point yy() const
		{
			return{ y, y };
		}

		constexpr Point operator + () const;

		constexpr Point operator - () const;

		constexpr Point operator + (const Point& p) const;

		constexpr Point operator - (const Point& p) const;

		constexpr Point operator * (int32 s) const;

		constexpr Float2 operator * (float s) const;

		constexpr Vec2 operator * (double s) const;

		constexpr Point operator * (const Point& p) const;

		constexpr Point operator / (int32 s) const;

		constexpr Float2 operator / (float s) const;

		constexpr Vec2 operator / (double s) const;

		Point& operator += (const Point& p);

		Point& operator -= (const Point& p);

		Point& operator *= (int32 s);

		Point& operator /= (int32 s);

		constexpr bool operator == (const Point& p) const;

		constexpr bool operator != (const Point& p) const;

		Point& set(int32 _x, int32 _y) { x = _x; y = _y; return *this; }

		Point& set(const Point& p) { return *this = p; }

		constexpr Point movedBy(int32 _x, int32 _y) const { return{ x + _x, y + _y }; }

		constexpr Point movedBy(const Point& p) const { return{ x + p.x, y + p.y }; }

		Point& moveBy(int32 _x, int32 _y) { x += _x; y += _y; return *this; }

		Point& moveBy(const Point& p) { return *this += p; }

		constexpr bool isZero() const { return x == 0 && y == 0; }

		double distanceFrom(const Vec2& p) const;

		constexpr double distanceFromSq(const Vec2& p) const;

		constexpr Vec2 lerp(const Vec2& other, double f) const;

		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		/// <summary>
		/// 点が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 点がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 点の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 点が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 点がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 点の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 点の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		const Point& draw(const Color& color = Palette::White) const;

		/// <summary>
		/// Point{ 0, 0 }
		/// </summary>
		const static Point Zero;

		/// <summary>
		/// Point{ 1, 1 }
		/// </summary>
		const static Point One;

		/// <summary>
		/// Point{ 1, 0 }
		/// </summary>
		const static Point UnitX;

		/// <summary>
		/// Point{ 0, 1 }
		/// </summary>
		const static Point UnitY;

		/// <summary>
		/// Point{ -1, 0 }
		/// </summary>
		const static Point Left;

		/// <summary>
		/// Point{ 1, 0 }
		/// </summary>
		const static Point Right;

		/// <summary>
		/// Point{ 0, -1 }
		/// </summary>
		const static Point Up;

		/// <summary>
		/// Point{ 0, 1 }
		/// </summary>
		const static Point Down;
	};

	/// <summary>
	/// 出力ストリームに点を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 点
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Point& v)
	{
		return os << CharType('(') << v.x << CharType(',') << v.y << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに点を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 点
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Point& v)
	{
		CharType unused;
		return is >> unused >> v.x >> unused >> v.y >> unused;
	}

	inline constexpr Point operator * (int32 s, const Point& p);

	inline constexpr Float2 operator * (float s, const Point& p);

	inline constexpr Vec2 operator * (double s, const Point& p);

	using Size = Point;
}

namespace std
{
	template <>
	struct hash<s3d::Point>
	{
		size_t operator () (const s3d::Point& keyVal) const
		{
			return hash<s3d::uint64>()(*((s3d::uint64*)&keyVal));
		}
	};
}
