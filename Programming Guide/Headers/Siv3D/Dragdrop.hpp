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
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// ドラッグ &amp; ドロップ
	/// </summary>
	/// <remarks>
	/// ドラッグ &amp; ドロップの機能を提供します。
	/// </remarks>
	namespace Dragdrop
	{
		/// <summary>
		/// ドラッグ &amp; ドロップが有効かどうかを取得します。
		/// </summary>
		/// <returns>
		/// ドラッグ &amp; ドロップが有効な場合 true、それ以外の場合は false
		/// </returns>
		bool IsEnabled();

		/// <summary>
		/// ドラッグ &amp; ドロップの ON / OFF を切り替えます。
		/// </summary>
		/// <param name="enable">
		/// ドラッグ &amp; ドロップを有効にする場合 true, 無効にする場合は false
		/// </param>
		/// <remarks>
		/// 直前にドロップされたアイテムがある状態でドラッグ &amp; ドロップを無効に設定すると、そのドロップはキャンセルされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetEnabled(bool enable);

		/// <summary>
		/// ドロップされたアイテムがあるかどうかを返します。
		/// </summary>
		/// <returns>
		/// ドロップされたアイテムがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasItems();

		/// <summary>
		/// ドロップされたアイテムの一覧を取得します。
		/// </summary>
		/// <remarks>
		/// この関数を呼ぶたびに、ドロップされたアイテムのリストは空になります。
		/// </remarks>
		/// <returns>
		/// ドロップされたすべてのファイルのパス一覧
		/// </returns>
		Array<FilePath> GetFilePaths();

		/// <summary>
		/// アイテムが最後にドロップされたクライアント領域上の座標を取得します。
		/// </summary>
		/// <returns>
		/// アイテムが最後にドロップされたクライアント領域上の座標
		/// </returns>
		Point GetPos();
	}
}
