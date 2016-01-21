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
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// 球面座標
	/// </summary>
	struct Spherical
	{
		double r, theta, phi;

		Spherical() = default;

		constexpr Spherical(double _r, double _theta, double _phi)
			: r{ _r }
			, theta{ _theta }
			, phi{ _phi } {}

		Spherical(const Vec3& pos)
			: r{ pos.length() }
			, theta{ std::acos(pos.y / r) }
			, phi{ std::atan2(pos.z, pos.x) } {}

		constexpr Spherical operator + () const
		{
			return *this;
		}

		constexpr Spherical operator - () const
		{
			return{ r, theta + Math::Pi, phi + Math::Pi };
		}

		Vec3 operator + (const Vec3& v) const
		{
			return operator Vec3() + v;
		}

		Vec3 operator - (const Vec3& v) const
		{
			return operator Vec3() - v;
		}

		operator Vec3() const
		{
			const double s = std::sin(theta);

			return{ r * s * std::cos(phi), r * std::cos(theta), r * s * std::sin(phi) };
		}
	};

	/// <summary>
	/// 出力ストリームに球面座標を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="s">
	/// 球面座標
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Spherical& s)
	{
		return os << CharType('(')
			<< c.r << CharType(',')
			<< c.theta << CharType(',')
			<< c.phi << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに球面座標を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="s">
	/// 球面座標
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Spherical& s)
	{
		CharType unused;

		return is >> unused
			>> c.r >> unused
			>> c.theta >> unused
			>> c.phi >> unused;
	}
}
