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

namespace s3d
{
	/// <summary>
	/// マウス
	/// </summary>
	/// <remarks>
	/// マウス入力の機能を提供します。
	/// </remarks>
	namespace Mouse
	{
		/// <summary>
		/// マウスカーソルがクライアント領域上にあるかを返します。
		/// </summary>
		/// <returns>
		/// マウスカーソルがクライアント領域上にある場合 true, それ以外の場合は false
		/// </returns>
		bool OnClient();

		/// <summary>
		/// クライアント座標系でのマウスカーソルの位置を返します。
		/// </summary>
		/// <returns>
		/// クライアント座標系でのマウスカーソルの位置
		/// </returns>
		Point Pos();

		Vec2 PosF();

		/// <summary>
		/// クライアント座標系での 1 フレーム前のマウスカーソルの位置を返します。
		/// </summary>
		/// <returns>
		/// クライアント座標系での 1 フレーム前のマウスカーソルの位置
		/// </returns>
		Point PreviousPos();

		Vec2 PreviousPosF();

		/// <summary>
		/// クライアント座標系でのマウスカーソルの移動量を返します。
		/// </summary>
		/// <returns>
		/// クライアント座標系でのマウスカーソルの移動量
		/// </returns>
		Point Delta();

		Vec2 DeltaF();

		/// <summary>
		/// クライアント座標系での 1 フレーム前と現在のフレームの中間のマウスカーソルの位置を返します。
		/// </summary>
		/// <returns>
		/// クライアント座標系での 1 フレーム前と現在のフレームの中間のマウスカーソルの位置
		/// </returns>
		Point HalfPreviousPos();

		Vec2 HalfPreviousPosF();

		/// <summary>
		/// スクリーン座標系でのマウスカーソルの位置を返します。
		/// </summary>
		/// <returns>
		/// スクリーン座標系でのマウスカーソルの位置
		/// </returns>
		Point ScreenPos();

		/// <summary>
		/// スクリーン座標系での 1 フレーム前のマウスカーソルの位置を返します。
		/// </summary>
		/// <returns>
		/// スクリーン座標系での 1 フレーム前のマウスカーソルの位置
		/// </returns>
		Point PreviousScreenPos();

		/// <summary>
		/// スクリーン座標系でのマウスカーソルの移動量を返します。
		/// </summary>
		/// <returns>
		/// スクリーン座標系でのマウスカーソルの移動量
		/// </returns>
		Point ScreenDelta();

		/// <summary>
		/// クライアント座標系のマウスカーソル位置に適用する座標変換を設定します。
		/// </summary>
		/// <param name="scale">
		/// 適用するスケーリング
		/// </param>
		/// <param name="offset">
		/// 適用するオフセット（ピクセル）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetTransform(const Mat3x2& matrix);

		/// <summary>
		/// 現在の、クライアント座標系のマウスカーソル位置に適用されている座標変換を返します。
		/// </summary>
		/// <returns>
		/// 適用されているスケーリングとオフセット（ピクセル）のペア
		/// </returns>
		Mat3x2 GetTransform();

		/// <summary>
		/// 垂直方向のマウスホイールの回転量を返します。
		/// </summary>
		/// <returns>
		/// 垂直方向のマウスホイールの回転量
		/// </returns>
		int32 Wheel();

		/// <summary>
		/// 水平方向のマウスホイールの回転量を返します。
		/// </summary>
		/// <returns>
		/// 水平方向のマウスホイールの回転量
		/// </returns>
		int32 WheelH();

		/// <summary>
		/// 3D シーンに対するマウスカーソルのレイを取得します。
		/// </summary>
		/// <returns>
		/// 3D シーンに対するマウスカーソルのレイ
		/// </returns>
		const s3d::Ray& Ray();

		[[deprecated("** Mouse::LeftClicked() is a deprecated function. Use Input::MouseL.clicked instead. **")]]
		bool LeftClicked();

		[[deprecated("** Mouse::RightClicked() is a deprecated function. Use Input::MouseR.clicked instead. **")]]
		bool RightClicked();
	}
}
