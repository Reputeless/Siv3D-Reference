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
	/// 円柱座標
	/// </summary>
	struct Cylindrical
	{
		double r, phi, y;

		Cylindrical() = default;

		constexpr Cylindrical(double _r, double _phi, double _y)
			: r{ _r }
			, phi{ _phi }
			, y{ _y } {}

		Cylindrical(const Vec3& pos)
			: r{ pos.xz().length() }
			, phi{ std::atan2(pos.z, pos.x) }
			, y{ pos.y } {}

		constexpr Cylindrical operator + () const
		{
			return *this;
		}

		constexpr Cylindrical operator - () const
		{
			return{ r, phi + Math::Pi, -y };
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
			return{ r * std::cos(phi), y, r * std::sin(phi) };
		}
	};

	/// <summary>
	/// 出力ストリームに円柱座標を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="c">
	/// 円柱座標
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Cylindrical& c)
	{
		return os << CharType('(')
			<< c.r << CharType(',')
			<< c.phi << CharType(',')
			<< c.y << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに円柱座標を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="c">
	/// 円柱座標
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Cylindrical& c)
	{
		CharType unused;

		return is >> unused
			>> c.r >> unused
			>> c.phi >> unused
			>> c.y >> unused;
	}
}
