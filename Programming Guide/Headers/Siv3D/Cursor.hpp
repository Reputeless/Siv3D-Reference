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
# include "PointVector.hpp"
# include "TextureRegion.hpp"

namespace s3d
{
	/// <summary>
	/// カーソルの種類
	/// </summary>
	enum class CursorType
	{
		Arrow,

		Hand,

		Custom,

		None,

		Default = Arrow
	};

	/// <summary>
	/// カーソルのスタイル
	/// </summary>
	struct CursorStyle
	{
		/// <summary>
		/// カーソルのスタイルを設定します。
		/// </summary>
		/// <param name="_type">
		/// カーソルの種類
		/// </param>
		/// <param name="_texture">
		/// カーソルとして使用する TextureRegion
		/// </param>
		/// <param name="_center">
		/// カーソルの中心位置のオフセット
		/// </param>
		CursorStyle(CursorType _type = CursorType::Default, const TextureRegion& _texture = TextureRegion(), const Point& _center = Point::Zero)
			: type(_type)
			, texture(_texture)
			, center(_center) {}

		/// <summary>
		/// カーソルの種類
		/// </summary>
		CursorType type;

		/// <summary>
		/// カーソルとして使用する TextureRegion
		/// </summary>
		TextureRegion texture;

		/// <summary>
		/// カーソルの中心位置のオフセット
		/// </summary>
		Point center;

		/// <summary>
		/// デフォルトの矢印カーソル
		/// </summary>
		const static CursorStyle Default;

		/// <summary>
		/// 手のマークのカーソル
		/// </summary>
		const static CursorStyle Hand;

		/// <summary>
		/// カーソル非表示
		/// </summary>
		const static CursorStyle None;

		/// <summary>
		/// カスタムカーソル
		/// </summary>
		static CursorStyle Custom(const TextureRegion& texture, const Point& center = Point::Zero)
		{
			return CursorStyle(CursorType::Custom, texture, center);
		}
	};

	namespace Cursor
	{
		/// <summary>
		/// カーソルを移動します。
		/// </summary>
		/// <param name="x">
		/// クライアント座標系での新しいカーソルの x 座標
		/// </param>
		/// <param name="y">
		/// クライアント座標系での新しいカーソルの y 座標
		/// </param>
		/// <remarks>
		/// ウィンドウがアクティブな時のみ有効です。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetPos(int x, int y);

		/// <summary>
		/// カーソルを移動します。
		/// </summary>
		/// <param name="pos">
		/// クライアント座標系での新しいカーソルの位置
		/// </param>
		/// <remarks>
		/// ウィンドウがアクティブな時のみ有効です。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetPos(const Point& pos);

		/// <summary>
		/// 現在のカーソルのスタイルを取得します。
		/// </summary>
		/// <returns>
		/// 現在のカーソルのスタイル
		/// </returns>
		const CursorStyle& GetStyle();

		/// <summary>
		/// カーソルのスタイルを変更します。
		/// </summary>
		/// <param name="style">
		/// 新しいカーソルのスタイル
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStyle(const CursorStyle& style);
	}
}
