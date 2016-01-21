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

namespace s3d
{
	/// <summary>
	/// 4 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector4D
	{
		using value_type = Type;

		Type x, y, z, w;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector4D() = default;

		template <class U, class V, class W, class X>
		constexpr Vector4D(U _x, V _y, W _z, X _w)
			: x(static_cast<Type>(_x))
			, y(static_cast<Type>(_y))
			, z(static_cast<Type>(_z))
			, w(static_cast<Type>(_w)) {}

		constexpr Vector4D(Type _x, Type _y, Type _z, Type _w)
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w) {}

		template <class U>
		constexpr Vector4D(const Vector2D<U>& xy, Type _z, Type _w)
			: x(static_cast<Type>(xy.x))
			, y(static_cast<Type>(xy.y))
			, z(_z)
			, w(_w) {}

		template <class U>
		constexpr Vector4D(Type _x, Type _y, const Vector2D<U>& zw)
			: x(_x)
			, y(_y)
			, z(static_cast<Type>(zw.x))
			, w(static_cast<Type>(zw.y)) {}

		template <class U, class V>
		constexpr Vector4D(const Vector2D<U>& xy, const Vector2D<V>& zw)
			: x(static_cast<Type>(xy.x))
			, y(static_cast<Type>(xy.y))
			, z(static_cast<Type>(zw.x))
			, w(static_cast<Type>(zw.y)) {}

		template <class U>
		constexpr Vector4D(const Vector3D<U>& xyz, Type _w)
			: x(static_cast<Type>(xyz.x))
			, y(static_cast<Type>(xyz.y))
			, z(static_cast<Type>(xyz.z))
			, w(_w) {}

		template <class U>
		constexpr Vector4D(Type _x, const Vector3D<U>& yzw)
			: x(_x)
			, y(static_cast<Type>(yzw.y))
			, z(static_cast<Type>(yzw.y))
			, w(static_cast<Type>(yzw.z)) {}

		template <class U>
		constexpr Vector4D(const Vector4D<U>& v)
			: x(static_cast<Type>(v.x))
			, y(static_cast<Type>(v.y))
			, z(static_cast<Type>(v.z))
			, w(static_cast<Type>(v.w)) {}

		constexpr Vector4D operator + () const { return *this; }

		constexpr Vector4D operator - () const { return{ -x, -y, -z, -w }; }

		constexpr Vector4D operator + (const Vector4D& v) const { return{ x + v.x, y + v.y, z + v.z, w + v.w }; }

		constexpr Vector4D operator - (const Vector4D& v) const { return{ x - v.x, y - v.y, z - v.z, w - v.w }; }

		constexpr Vector4D operator * (Type s) const { return{ x*s, y*s, z*s, w*s }; }

		constexpr Vector4D operator * (const Vector4D& v) const { return{ x*v.x, y*v.y, z*v.z, w*v.w }; }

		constexpr Vector4D operator / (Type s) const { return{ x / s, y / s, z / s, w / s }; }

		Vector4D& operator += (const Vector4D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}

		Vector4D& operator -= (const Vector4D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		Vector4D& operator *= (Type s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		Vector4D& operator /= (Type s)
		{
			return *this *= static_cast<Type>(1.0) / s;
		}

		constexpr bool operator == (const Vector4D& v) const { return v.x == x && v.y == y && v.z == z && v.w == w; }

		constexpr bool operator != (const Vector4D& v) const { return v.x != x || v.y != y || v.z != z || v.w != w; }

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		constexpr Vector2D<Type> xy() const
		{
			return{ x, y };
		}

		/// <summary>
		/// Vector2D{ y, z }
		/// </summary>
		constexpr Vector2D<Type> yz() const
		{
			return{ y, z };
		}

		/// <summary>
		/// Vector2D{ z, w }
		/// </summary>
		constexpr Vector2D<Type> zw() const
		{
			return{ z, w };
		}

		/// <summary>
		/// Vector3D{ x, y, z }
		/// </summary>
		constexpr Vector3D<Type> xyz() const
		{
			return{ x, y, z };
		}

		/// <summary>
		/// Vector3D{ y, z, w }
		/// </summary>
		constexpr Vector3D<Type> yzw() const
		{
			return{ y, z, w };
		}

		Vector4D& set(Type _x, Type _y, Type _z, Type _w) { x = _x; y = _y; z = _z; w = _w; return *this; }

		Vector4D& set(const Vector4D& v) { return *this = v; }

		constexpr Vector4D movedBy(Type _x, Type _y, Type _z, Type _w) const { return{ x + _x, y + _y, z + _z, w + _w }; }

		constexpr Vector4D movedBy(const Vector4D& v) const { return{ x + v.x, y + v.y, z + v.z, w + v.w }; }

		Vector4D& moveBy(Type _x, Type _y, Type _z, Type _w) { x += _x; y += _y; z += _z; w += _w; return *this; }

		Vector4D& moveBy(const Vector4D& v) { return *this += v; }

		constexpr bool isZero() const
		{
			return x == static_cast<Type>(0.0)
				&& y == static_cast<Type>(0.0)
				&& z == static_cast<Type>(0.0)
				&& w == static_cast<Type>(0.0);
		}

		Type length() const { return std::sqrt(lengthSq()); }

		constexpr Type lengthSq() const { return dot(*this); }

		Type lengthInv() const { return static_cast<Type>(1.0) / length(); }

		Vector4D& setLength(Type _length)
		{
			if (_length == static_cast<Type>(0.0))
			{
				return set(0, 0, 0, 0);
			}

			return *this *= (_length / length());
		}

		Type distanceFrom(const Vector4D& v) const { return (*this - v).length(); }

		constexpr Type distanceFromSq(const Vector4D& v) const { return (*this - v).lengthSq(); }

		constexpr Type dot(const Vector4D& v) const { return x*v.x + y*v.y + z*v.z + w*v.w; }

		Vector4D normalized() const { return *this * lengthInv(); }

		Vector4D& normalize() { return *this *= lengthInv(); }

		constexpr Vector4D lerp(const Vector4D& other, Type f) const
		{
			return{ x + (other.x - x) * f, y + (other.y - y) * f, z + (other.z - z) * f, w + (other.w - w) * f };
		}

		/// <summary>
		/// Vector4D{ 0, 0, 0, 0 }
		/// </summary>
		const static Vector4D Zero;

		/// <summary>
		/// Vector4D{ 1, 1, 1, 1 }
		/// </summary>
		const static Vector4D One;

		/// <summary>
		/// Vector4D{ 1, 0, 0, 0 }
		/// </summary>
		const static Vector4D UnitX;

		/// <summary>
		/// Vector4D{ 0, 1, 0, 0 }
		/// </summary>
		const static Vector4D UnitY;

		/// <summary>
		/// Vector4D{ 0, 0, 1, 0 }
		/// </summary>
		const static Vector4D UnitZ;

		/// <summary>
		/// Vector4D{ 0, 0, 0, 1 }
		/// </summary>
		const static Vector4D UnitW;
	};

	/// <summary>
	/// 出力ストリームに 4 次元ベクトルを渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 4 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Vector4D<Type>& v)
	{
		return os << CharType('(') << v.x << CharType(',') << v.y << CharType(',') << v.z << CharType(',') << v.w << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに 4 次元ベクトルを渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 4 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Vector4D<Type>& v)
	{
		CharType unused;
		return is >> unused >> v.x >> unused >> v.y >> unused >> v.z >> unused >> v.w >> unused;
	}

	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;

	template <class Type, class U>
	inline constexpr Vector4D<Type> operator * (U s, const Vector4D<Type>& v)
	{
		return v*s;
	}
}
