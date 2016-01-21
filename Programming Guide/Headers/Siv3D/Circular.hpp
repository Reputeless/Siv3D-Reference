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
	/// 円座標
	/// </summary>
	template <int32 Oclock>
	struct CircularBase
	{
	private:

		constexpr double offset() const
		{
			return Oclock * (Math::TwoPi / 12);
		}

	public:

		/// <summary>
		/// 半径
		/// </summary>
		double r;
		
		/// <summary>
		/// 角度（ラジアン）
		/// </summary>
		double theta;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		CircularBase() = default;

		constexpr CircularBase(double _r, double _theta)
			: r(_r)
			, theta(_theta) {}

		CircularBase(const Vec2& pos)
			: r(pos.length()), theta(std::atan2(pos.x, -pos.y) - offset()) {}

		constexpr CircularBase operator + () const
		{
			return *this;
		}

		constexpr CircularBase operator - () const
		{
			return{ r, theta + Math::Pi };
		}

		Vec2 operator + (const Vec2& v) const
		{
			return operator Vec2() + v;
		}

		Vec2 operator - (const Vec2& v) const
		{
			return operator Vec2() - v;
		}

		operator Vec2() const
		{
			return{ std::sin(theta + offset())*r, -std::cos(theta + offset())*r };
		}
	};

	/// <summary>
	/// 出力ストリームに極座標を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="c">
	/// 極座標
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType, int32 Oclock>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const CircularBase<Oclock>& c)
	{
		return os << CharType('(') << c.r << CharType(',') << c.theta << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに極座標を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="c">
	/// 極座標
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType, int32 Oclock>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, CircularBase<Oclock>& c)
	{
		CharType unused;
		return is >> unused >> c.r >> unused >> c.theta >> unused;
	}

	template <int32 Oclock>
	inline Vec2 operator + (const Vec2& pos, const CircularBase<Oclock>& c)
	{
		return c + pos;
	}

	template <int32 Oclock>
	inline Vec2 operator - (const Vec2& pos, const CircularBase<Oclock>& c)
	{
		return pos + (-c);
	}

	using Circular	= CircularBase<0>;
	using Circular0	= CircularBase<0>;
	using Circular3 = CircularBase<3>;
	using Circular6 = CircularBase<6>;
	using Circular9 = CircularBase<9>;
}
