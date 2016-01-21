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
	/// クリップボードのデータの種類
	/// </summary>
	enum class ClipboardItemType
	{
		/// <summary>
		/// 何もコピーされていない
		/// </summary>
		None,

		/// <summary>
		/// テキスト
		/// </summary>
		Text,

		/// <summary>
		/// 画像
		/// </summary>
		Image,

		/// <summary>
		/// ファイルパス
		/// </summary>
		FilePath
	};

	/// <summary>
	/// クリップボード
	/// </summary>
	/// <remarks>
	/// クリップボードに関する機能を提供します。
	/// </remarks>
	namespace Clipboard
	{
		/// <summary>
		/// クリップボードにコピーされているデータの種類を返します。
		/// </summary>
		/// <returns>
		/// クリップボードにコピーされているデータの種類
		/// </returns>
		ClipboardItemType GetType();

		/// <summary>
		/// クリップボードにコピーされているテキストを返します。
		/// </summary>
		/// <returns>
		/// クリップボードにコピーされている文字列。クリップボードにテキストがない場合は空の文字列
		/// </returns>
		String GetText();

		/// <summary>
		/// クリップボードにコピーされている画像を返します。
		/// </summary>
		/// <returns>
		/// クリップボードにコピーされている画像。クリップボードに画像がない場合は空の画像
		/// </returns>
		Image GetImage();

		/// <summary>
		/// クリップボードにコピーされているファイルパスの一覧を返します。
		/// </summary>
		/// <returns>
		/// クリップボードにコピーされているファイルパスの一覧
		/// </returns>
		Array<FilePath> GetFilePaths();

		/// <summary>
		/// テキストをクリップボードにコピーします。
		/// </summary>
		/// <param name="str">
		/// クリップボードにコピーするテキスト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetText(const String& str);

		/// <summary>
		/// 画像をクリップボードにコピーします。
		/// </summary>
		/// <param name="image">
		/// クリップボードにコピーする画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetImage(const Image& image);

		/// <summary>
		/// クリップボードの中身を空にします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Clear();
	}
}
