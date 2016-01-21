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
# include "String.hpp"
# pragma warning (disable: 4127)
# include "../ThirdParty/cppformat/format.h"
# pragma warning (default: 4127)

namespace s3d
{
	/// <summary>
	/// Python 風フォーマットのためのタグ
	/// </summary>
	constexpr struct fmt_tag {} PyFmt;

	struct PyFmtString
	{
		PyFmtString() = default;

		PyFmtString(const wchar_t *str, size_t len)
			: string(str, len) {}

		PyFmtString(const std::wstring& str)
			: string(str) {}

		PyFmtString(std::wstring&& str)
			: string(std::move(str)) {}

		PyFmtString(const String& str)
			: string(str.str()) {}

		std::wstring string;
	};

	namespace literals
	{
		inline namespace formatting_literals
		{
			inline PyFmtString operator "" _fmt(const wchar_t *str, size_t len)
			{
				return PyFmtString(str, len);
			}
		}
	}

	/// <summary>
	/// 一連の引数を Python 風フォーマットで文字列に変換します。
	/// </summary>
	/// <param name="args">
	/// 変換する値、第二引数は変換指定文字列
	/// </param>
	/// <returns>
	/// 引数を文字列に変換して連結した文字列
	/// </returns>
	template <class ... Args>
	inline String Format(fmt_tag, const Args& ... args)
	{
		return fmt::format(args...);
	}

	/// <summary>
	/// 一連の引数を Python 風フォーマットで文字列に変換します。
	/// </summary>
	/// <param name="args">
	/// 変換する値、第二引数は変換指定文字列
	/// </param>
	/// <returns>
	/// 引数を文字列に変換して連結した文字列
	/// </returns>
	template <class ... Args>
	inline String Format(const PyFmtString& py, const Args& ... args)
	{
		return fmt::format(py.string, args...);
	}
}
