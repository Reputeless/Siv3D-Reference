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
# include "Point.hpp"

namespace s3d
{
	/// <summary>
	/// 2 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector2D
	{
		using value_type = Type;

		Type x, y;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector2D() = default;

		template <class U, class V>
		constexpr Vector2D(U _x, V _y)
			: x(static_cast<Type>(_x))
			, y(static_cast<Type>(_y)) {}

		constexpr Vector2D(Type _x, Type _y)
			: x(_x)
			, y(_y) {}

		constexpr Vector2D(const Point& v)
			: x(static_cast<Type>(v.x))
			, y(static_cast<Type>(v.y)) {}

		template <class U>
		constexpr Vector2D(const Vector2D<U>& v)
			: x(static_cast<Type>(v.x))
			, y(static_cast<Type>(v.y)) {}

		constexpr Vector2D operator + () const { return *this; }

		constexpr Vector2D operator - () const { return{ -x, -y }; }

		constexpr Vector2D operator + (const Vector2D& v) const { return{ x + v.x, y + v.y }; }

		constexpr Vector2D operator - (const Vector2D& v) const { return{ x - v.x, y - v.y }; }

		constexpr Vector2D operator * (Type s) const { return{ x*s, y*s }; }

		constexpr Vector2D operator * (const Vector2D& v) const { return{ x*v.x, y*v.y }; }

		constexpr Vector2D operator / (Type s) const { return{ x / s, y / s }; }

		Vector2D& operator += (const Vector2D& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2D& operator -= (const Vector2D& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vector2D& operator *= (Type s)
		{
			x *= s;
			y *= s;
			return *this;
		}

		Vector2D& operator /= (Type s)
		{
			return *this *= static_cast<Type>(1.0) / s;
		}

		constexpr bool operator == (const Vector2D& v) const { return v.x == x && v.y == y; }

		constexpr bool operator != (const Vector2D& v) const { return v.x != x || v.y != y; }

		/// <summary>
		/// Vector2D{ x, x }
		/// </summary>
		constexpr Vector2D xx() const { return{ x, x }; }

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		constexpr Vector2D xy() const { return{ x, y }; }

		/// <summary>
		/// Vector2D{ y, x }
		/// </summary>
		constexpr Vector2D yx() const { return{ y, x }; }

		/// <summary>
		/// Vector2D{ y, y }
		/// </summary>
		constexpr Vector2D yy() const { return{ y, y }; }

		constexpr Point asPoint() const { return{ static_cast<int>(x), static_cast<int>(y) }; }

		Vector2D& set(Type _x, Type _y) { x = _x; y = _y; return *this; }

		Vector2D& set(const Vector2D& v) { return *this = v; }

		constexpr Vector2D movedBy(Type _x, Type _y) const { return{ x + _x, y + _y }; }

		constexpr Vector2D movedBy(const Vector2D& v) const { return{ x + v.x, y + v.y }; }

		Vector2D& moveBy(Type _x, Type _y) { x += _x; y += _y; return *this; }

		Vector2D& moveBy(const Vector2D& v) { return *this += v; }

		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		constexpr bool isZero() const
		{
			return x == static_cast<Type>(0.0)
				&& y == static_cast<Type>(0.0);
		}

		constexpr Type dot(const Vector2D& v) const
		{
			return x * v.x + y * v.y;
		}

		constexpr Type cross(const Vector2D& v) const
		{
			return x * v.y - y * v.x;
		}

		Type length() const
		{
			return std::sqrt(lengthSq());
		}

		constexpr Type lengthSq() const
		{
			return dot(*this);
		}

		Type lengthInv() const
		{
			return static_cast<Type>(1.0) / length();
		}

		Vector2D& setLength(Type _length)
		{
			if (_length == static_cast<Type>(0.0))
			{
				return set(0, 0);
			}
			
			return *this *= (_length / length());
		}

		Type distanceFrom(const Vector2D& v) const
		{
			return (*this - v).length();
		}

		constexpr Type distanceFromSq(const Vector2D& v) const
		{
			return (*this - v).lengthSq();
		}

		Vector2D normalized() const
		{
			return *this * lengthInv();
		}

		Vector2D& normalize()
		{
			return *this *= lengthInv();
		}

		Vector2D rotated(double angle) const
		{
			const double s = std::sin(angle);
			const double c = std::cos(angle);
			return{ x*c - y*s, x*s + y*c };
		}

		Vector2D& rotate(double angle)
		{
			return *this = rotated(angle);
		}

		constexpr Vector2D projection(const Vector2D& onto) const
		{
			return onto.lengthSq() ? onto * dot(onto) / onto.lengthSq() : Zero;
		}

		constexpr Vector2D lerp(const Vector2D& other, Type f) const
		{
			return{ x + (other.x - x) * f, y + (other.y - y) * f };
		}

		const Vector2D& draw(const Color& color = Palette::White) const;

		/// <summary>
		/// Vector2D{ 0, 0 }
		/// </summary>
		const static Vector2D Zero;

		/// <summary>
		/// Vector2D{ 1, 1 }
		/// </summary>
		const static Vector2D One;

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		const static Vector2D UnitX;

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		const static Vector2D UnitY;

		/// <summary>
		/// Vector2D{ -1, 0 }
		/// </summary>
		const static Vector2D Left;

		/// <summary>
		/// Vector2D{ 1, 0 }
		/// </summary>
		const static Vector2D Right;

		/// <summary>
		/// Vector2D{ 0, -1 }
		/// </summary>
		const static Vector2D Up;

		/// <summary>
		/// Vector2D{ 0, 1 }
		/// </summary>
		const static Vector2D Down;
	};

	/// <summary>
	/// 出力ストリームに 2 次元ベクトルを渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 2 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Vector2D<Type>& v)
	{
		return os << CharType('(') << v.x << CharType(',') << v.y << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに 2 次元ベクトルを渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 2 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Vector2D<Type>& v)
	{
		CharType unused;
		return is >> unused >> v.x >> unused >> v.y >> unused;
	}

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;

	template <class Type, class U>
	inline constexpr Vector2D<Type> operator * (U s, const Vector2D<Type>& v)
	{
		return v*s;
	}

	template <class Type>
	inline constexpr Vector2D<Type> operator + (const Point& p, const Vector2D<Type>& v)
	{
		return v + p;
	}

	template <class Type>
	inline constexpr Vector2D<Type> operator - (const Point& p, const Vector2D<Type>& v)
	{
		return Vector2D<Type>(p)-v;
	}
}
