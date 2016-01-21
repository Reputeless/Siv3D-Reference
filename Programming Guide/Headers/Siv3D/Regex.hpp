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
# include <regex>
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// 正規表現マッチの結果
	/// </summary>
	using Match = std::wsmatch;

	/// <summary>
	/// 正規表現
	/// </summary>
	/// <remarks>
	/// 正規表現の機能を提供します。
	/// </remarks>
	namespace Regex
	{
		/// <summary>
		/// 正規表現に一致した最初の文字列を置換します。
		/// </summary>
		/// <param name="input">
		/// 対象の文字列
		/// </param>
		/// <param name="regex">
		/// 検索する正規表現
		/// </param>
		/// <param name="replacement">
		/// 置換後の正規表現
		/// </param>
		/// <returns>
		/// 置換した文字列
		/// </returns>
		inline String ReplaceFirst(const String& input, const String& regex, const String& replacement);

		/// <summary>
		/// 正規表現に一致した文字列を全て置換します。
		/// </summary>
		/// <param name="input">
		/// 対象の文字列
		/// </param>
		/// <param name="regex">
		/// 検索する正規表現
		/// </param>
		/// <param name="replacement">
		/// 置換後の正規表現
		/// </param>
		/// <returns>
		/// 置換した文字列
		/// </returns>
		inline String ReplaceAll(const String& input, const String& regex, const String& replacement);

		/// <summary>
		/// 正規表現に一致する全てのマッチを返します。
		/// </summary>
		/// <param name="input">
		/// 対象の文字列
		/// </param>
		/// <param name="regex">
		/// 検索する正規表現
		/// </param>
		/// <returns>
		/// マッチの一覧
		/// </returns>
		inline Array<Match> Search(const String& input, const String& regex);
	}
}

# include "Regex.inl"
