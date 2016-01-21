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
# include "Color.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// HSV カラー
	/// </summary>
	/// <remarks>
	/// 色を 色相(H), 彩度(S), 明度(V) で表します。
	/// </remarks>
	struct HSV
	{
		/// <summary>
		/// 色相 [0.0, 360.0)
		/// </summary>
		double h;

		/// <summary>
		/// 彩度 [0.0, 1.0]
		/// </summary>
		double s;
			
		/// <summary>
		/// 明度 [0.0, 1.0]
		/// </summary>
		double v;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		HSV() = default;

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="_h">
		/// 色相 [0.0, 360.0)
		/// </param>
		explicit constexpr HSV(double _h)
			: h(_h)
			, s(1.0)
			, v(1.0) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="_h">
		/// 色相 [0.0, 360.0)
		/// </param>
		/// <param name="_s">
		/// 彩度 [0.0, 1.0]
		/// </param>
		/// <param name="_v">
		/// 明度 [0.0, 1.0]
		/// </param>
		constexpr HSV(double _h, double _s, double _v)
			: h(_h)
			, s(_s)
			, v(_v) {}

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="col">
		/// RGB カラー
		/// </param>
		HSV(const Color& col);

		/// <summary>
		/// 色を作成します。
		/// </summary>
		/// <param name="col">
		/// RGB カラー
		/// </param>
		HSV(const ColorF& col);

		/// <summary>
		/// HSV の値を加算します。
		/// </summary>
		/// <param name="hsv">
		/// 加算する値
		/// </param>
		/// <returns>
		/// 加算した結果
		/// </returns>
		HSV operator + (const HSV& hsv) const;

		/// <summary>
		/// HSV の値を減算します。
		/// </summary>
		/// <param name="hsv">
		/// 減算する値
		/// </param>
		/// <returns>
		/// 減算した結果
		/// </returns>
		HSV operator - (const HSV& hsv) const;

		/// <summary>
		/// Color 型に変換します。
		/// </summary>
		/// <param name="alpha">
		/// アルファ値 [0, 255]
		/// </param>
		/// <returns>
		/// 変換した値
		/// </returns>
		Color toColor(uint32 alpha = 255) const;

		/// <summary>
		/// ColorF 型に変換します。
		/// </summary>
		/// <param name="alpha">
		/// アルファ値 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// 変換した値
		/// </returns>
		ColorF toColorF(double alpha = 1.0) const;

		/// <summary>
		/// RGB 値から HSV 値に変換します。
		/// </summary>
		/// <param name="r">
		/// R [0.0, 1.0]
		/// </param>
		/// <param name="g">
		/// G [0.0, 1.0]
		/// </param>
		/// <param name="b">
		/// B [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void convertFrom(double r, double g, double b);

		constexpr HSV lerp(const HSV& other, double f) const
		{
			return{ h + (other.h - h) * f, s + (other.s - s) * f, v + (other.v - v) * f };
		}

		/// <summary>
		/// Vec3(h, s, v)
		/// </summary>
		Vec3 asVec3() const
		{
			return{ h, s, v };
		}
	};

	/// <summary>
	/// 出力ストリームに色を渡します。
	/// </summary>
	/// <param name="os">
	/// 出力ストリーム
	/// </param>
	/// <param name="hsv">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const HSV& hsv)
	{
		return os << CharType('(')
			<< hsv.h << CharType(',')
			<< hsv.s << CharType(',')
			<< hsv.v << CharType(')');
	}

	/// <summary>
	/// 入力ストリームに色を渡します。
	/// </summary>
	/// <param name="is">
	/// 入力ストリーム
	/// </param>
	/// <param name="hsv">
	/// 色
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, HSV& hsv)
	{
		CharType unused;

		return is >> unused
			>> hsv.h >> unused
			>> hsv.s >> unused
			>> hsv.v >> unused;
	}

	/// <summary>
	/// HSV の値を加算します。
	/// </summary>
	/// <param name="color">
	/// 加算対象の色
	/// </param>
	/// <param name="hsv">
	/// 加算する値
	/// </param>
	/// <returns>
	/// 加算した結果
	/// </returns>
	inline HSV operator + (const Color& color, const HSV& hsv)
	{
		return HSV(color) + hsv;
	}

	/// <summary>
	/// HSV の値を減算します。
	/// </summary>
	/// <param name="color">
	/// 減算対象の色
	/// </param>
	/// <param name="hsv">
	/// 減算する値
	/// </param>
	/// <returns>
	/// 減算した結果
	/// </returns>
	inline HSV operator - (const Color& color, const HSV& hsv)
	{
		return HSV(color) - hsv;
	}

	/// <summary>
	/// 色相から Color を作成します。
	/// </summary>
	/// <param name="hue">
	/// 色相 [0.0, 360.0)
	/// </param>
	/// <returns>
	/// 作成したカラー
	/// </returns>
	Color HueToColor(double hue);

	/// <summary>
	/// 色相から ColorF を作成します。
	/// </summary>
	/// <param name="hue">
	/// 色相 [0.0, 360.0)
	/// </param>
	/// <returns>
	/// 作成したカラー
	/// </returns>
	ColorF HueToColorF(double hue);
}
