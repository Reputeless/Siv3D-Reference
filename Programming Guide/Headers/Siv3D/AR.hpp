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
# include "Array.hpp"
# include "Quad.hpp"
# include "Quaternion.hpp"

namespace s3d
{
	/// <summary>
	/// 検出した AR マーカーの情報
	/// </summary>
	struct ARMarker
	{
		/// <summary>
		/// カメラ空間での回転
		/// </summary>
		/// <remarks>
		/// カメラキャリブレーションを設定していない場合、利用できません。
		/// </remarks>
		Quaternion rotation3D;

		/// <summary>
		/// フレーム画像内のマーカーの領域
		/// </summary>
		Quad quad;

		/// <summary>
		/// フレーム画像内のマーカーの中心位置
		/// </summary>
		Vec2 screenPos;

		/// <summary>
		/// カメラ空間での座標
		/// </summary>
		/// <remarks>
		/// カメラキャリブレーションを設定していない場合、利用できません。
		/// </remarks>
		Vec3 pos;

		/// <summary>
		/// フレーム画像内のマーカーの回転
		/// </summary>
		double rotation2D;

		/// <summary>
		/// フレーム画像内のマーカー領域の周の長さ
		/// </summary>
		double perimeter;

		/// <summary>
		/// フレーム画像内のマーカー領域の面積
		/// </summary>
		double area;

		/// <summary>
		/// マーカー ID
		/// </summary>
		int32 id;
	};

	/// <summary>
	/// AR
	/// </summary>
	/// <remarks>
	/// AR マーカー検出機能を提供します。
	/// </remarks>
	namespace AR
	{
		/// <summary>
		/// AR マーカー画像を作成します。
		/// </summary>
		/// <param name="id">
		/// AR マーカーの ID [0, 1023]
		/// </param>
		/// <param name="tileSize">
		/// 画像の縦横の大きさ（ピクセル）
		/// </param>
		/// <returns>
		/// AR マーカー画像、ID が範囲外の場合空の画像
		/// </returns>
		Image CreateMarker(int32 id, int32 tileSize);
	}
}
