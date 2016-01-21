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
# include "Line.hpp"
# include "Polygon.hpp"

namespace s3d
{
	/// <summary>
	/// 矢印型のポリゴンを作成します。
	/// </summary>
	/// <param name="start">
	/// 矢印の根元の座標
	/// </param>
	/// <param name="end">
	/// 矢印が指す座標
	/// </param>
	/// <param name="thickness">
	/// 矢印の太さ
	/// </param>
	/// <param name="headSize">
	/// 矢印の三角形部分の大きさ
	/// </param>
	/// <returns>
	/// 矢印型のポリゴン
	/// </returns>
	Polygon Arrow(const Vec2& start, const Vec2& end, double thickness, const Vec2& headSize);

	/// <summary>
	/// 矢印型のポリゴンを作成します。
	/// </summary>
	/// <param name="line">
	/// 矢印の線
	/// </param>
	/// <param name="thickness">
	/// 矢印の太さ
	/// </param>
	/// <param name="headSize">
	/// 矢印の三角形部分の大きさ
	/// </param>
	/// <returns>
	/// 矢印型のポリゴン
	/// </returns>
	inline Polygon Arrow(const Line& line, double thickness, const Vec2& headSize)
	{
		return Arrow(line.begin, line.end, thickness, headSize);
	}
}
