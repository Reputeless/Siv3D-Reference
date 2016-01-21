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
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 3 次元ベクトル
	/// </summary>
	template <class Type>
	struct Vector3D
	{
		using value_type = Type;

		Type x, y, z;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Vector3D() = default;

		template <class U, class V, class W>
		constexpr Vector3D(U _x, V _y, W _z)
			: x(static_cast<Type>(_x))
			, y(static_cast<Type>(_y))
			, z(static_cast<Type>(_z)) {}

		constexpr Vector3D(Type _x, Type _y, Type _z)
			: x(_x)
			, y(_y)
			, z(_z) {}

		template <class U>
		constexpr Vector3D(const Vector2D<U>& xy, Type _z)
			: x(static_cast<Type>(xy.x))
			, y(static_cast<Type>(xy.y))
			, z(_z) {}

		template <class U>
		constexpr Vector3D(Type _x, const Vector2D<U>& yz)
			: x(_x)
			, y(static_cast<Type>(yz.x))
			, z(static_cast<Type>(yz.y)) {}

		template <class U>
		constexpr Vector3D(const Vector3D<U>& v)
			: x(static_cast<Type>(v.x))
			, y(static_cast<Type>(v.y))
			, z(static_cast<Type>(v.z)) {}

		constexpr Vector3D operator + () const { return *this; }

		constexpr Vector3D operator - () const { return{ -x, -y, -z }; }

		constexpr Vector3D operator + (const Vector3D& v) const { return{ x + v.x, y + v.y, z + v.z }; }

		constexpr Vector3D operator - (const Vector3D& v) const { return{ x - v.x, y - v.y, z - v.z }; }

		constexpr Vector3D operator * (Type s) const { return{ x*s, y*s, z*s }; }

		constexpr Vector3D operator * (const Vector3D& v) const { return{ x*v.x, y*v.y, z*v.z }; }

		constexpr Vector3D operator / (Type s) const { return{ x / s, y / s, z / s }; }

		Vector3D& operator += (const Vector3D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		Vector3D& operator -= (const Vector3D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		Vector3D& operator *= (Type s)
		{
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		Vector3D& operator /= (Type s)
		{
			return *this *= static_cast<Type>(1.0) / s;
		}

		constexpr bool operator == (const Vector3D& v) const { return v.x == x && v.y == y && v.z == z; }

		constexpr bool operator != (const Vector3D& v) const { return v.x != x || v.y != y || v.z != z; }

		/// <summary>
		/// Vector2D{ x, y }
		/// </summary>
		constexpr Vector2D<Type> xy() const
		{
			return{ x, y };
		}

		/// <summary>
		/// Vector2D{ x, z }
		/// </summary>
		constexpr Vector2D<Type> xz() const
		{
			return{ x, z };
		}

		/// <summary>
		/// Vector2D{ y, z }
		/// </summary>
		constexpr Vector2D<Type> yz() const
		{
			return{ y, z };
		}

		Vector3D& set(Type _x, Type _y, Type _z) { x = _x; y = _y; z = _z; return *this; }

		Vector3D& set(const Vector3D& v) { return *this = v; }

		constexpr Vector3D movedBy(Type _x, Type _y, Type _z) const { return{ x + _x, y + _y, z + _z }; }

		constexpr Vector3D movedBy(const Vector3D& v) const { return{ x + v.x, y + v.y, z + v.z }; }

		Vector3D& moveBy(Type _x, Type _y, Type _z) { x += _x; y += _y; z += _z; return *this; }

		Vector3D& moveBy(const Vector3D& v) { return *this += v; }

		constexpr bool isZero() const
		{
			return x == static_cast<Type>(0.0)
				&& y == static_cast<Type>(0.0)
				&& z == static_cast<Type>(0.0);
		}

		Type length() const { return std::sqrt(lengthSq()); }

		constexpr Type lengthSq() const { return dot(*this); }

		Type lengthInv() const { return static_cast<Type>(1.0) / length(); }

		Vector3D& setLength(Type _length)
		{
			if (_length == static_cast<Type>(0.0))
			{
				return set(0, 0, 0);
			}
			
			return *this *= (_length / length());
		}

		Type distanceFrom(const Vector3D& v) const { return (*this - v).length(); }

		constexpr Type distanceFromSq(const Vector3D& v) const { return (*this - v).lengthSq(); }

		constexpr Type dot(const Vector3D& v) const { return x*v.x + y*v.y + z*v.z; }

		constexpr Vector3D cross(const Vector3D& v) const { return{ y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x }; }

		Vector3D normalized() const { return *this * lengthInv(); }

		Vector3D& normalize() { return *this *= lengthInv(); }

		constexpr Vector3D lerp(const Vector3D& other, Type f) const
		{
			return{ x + (other.x - x) * f, y + (other.y - y) * f, z + (other.z - z) * f };
		}

		template <class Primitive>
		bool intersects(const Primitive& primitive) const
		{
			return Geometry3D::Intersect(*this, primitive);
		}

		/// <summary>
		/// Vector3D{ 0, 0, 0 }
		/// </summary>
		const static Vector3D Zero;

		/// <summary>
		/// Vector3D{ 1, 1, 1 }
		/// </summary>
		const static Vector3D One;

		/// <summary>
		/// Vector3D{ 1, 0, 0 }
		/// </summary>
		const static Vector3D UnitX;

		/// <summary>
		/// Vector3D{ 0, 1, 0 }
		/// </summary>
		const static Vector3D UnitY;

		/// <summary>
		/// Vector3D{ 0, 0, 1 }
		/// </summary>
		const static Vector3D UnitZ;

		/// <summary>
		/// Vector3D{ -1, 0, 0 }
		/// </summary>
		const static Vector3D Left;

		/// <summary>
		/// Vector3D{ 1, 0, 0 }
		/// </summary>
		const static Vector3D Right;

		/// <summary>
		/// Vector3D{ 0, 1, 0 }
		/// </summary>
		const static Vector3D Up;

		/// <summary>
		/// Vector3D{ 0, -1, 0 }
		/// </summary>
		const static Vector3D Down;

		/// <summary>
		/// Vector3D{ 0, 0, 1 }
		/// </summary>
		const static Vector3D Forward;

		/// <summary>
		/// Vector3D{ 0, 0, -1 }
		/// </summary>
		const static Vector3D Backward;
	};

	/// <summary>
	/// 出力ストリームに 3 次元ベクトルを渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="v">
	/// 3 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Vector3D<Type>& v)
	{
		return os << CharType('(') << v.x << CharType(',') << v.y << CharType(',') << v.z << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに 3 次元ベクトルを渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="v">
	/// 3 次元ベクトル
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, class Type>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Vector3D<Type>& v)
	{
		CharType unused;
		return is >> unused >> v.x >> unused >> v.y >> unused >> v.z >> unused;
	}

	using Float3	= Vector3D<float>;
	using Vec3		= Vector3D<double>;

	template <class Type, class U>
	inline constexpr Vector3D<Type> operator * (U s, const Vector3D<Type>& v)
	{
		return v*s;
	}
}
