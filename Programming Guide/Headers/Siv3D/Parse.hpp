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
# include <sstream>
# include "String.hpp"
# include "Optional.hpp"
# include "Number.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		Parse
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type>
	typename std::enable_if<!std::is_arithmetic<Type>::value, Type>::type Parse(const String& str)
	{
		Type to;

		if (std::wistringstream{ str.str() } >> to)
		{
			return to;
		}

		return to;
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type>
	typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type Parse(const String& str)
	{
		return FromString<Type>(str);
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <>
	inline bool Parse<bool>(const String& str)
	{
		return str.trim().lower() == L"true";
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <>
	inline char Parse<char>(const String& str)
	{
		return static_cast<char>(str.trim()[0]);
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <>
	inline wchar Parse<wchar>(const String& str)
	{
		return str.trim()[0];
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <>
	inline String Parse<String>(const String& str)
	{
		return str;
	}

	////////////////////////////////////////////////////////////////
	//
	//		ParseOpt
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <class Type>
	typename std::enable_if<!std::is_arithmetic<Type>::value, Optional<Type>>::type ParseOpt(const String& str)
	{
		Type to;

		if (std::wistringstream{ str.str() } >> to)
		{
			return Optional<Type>(to);
		}

		return none;
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <class Type>
	typename std::enable_if<std::is_arithmetic<Type>::value, Optional<Type>>::type ParseOpt(const String& str)
	{
		return FromStringOpt<Type>(str);
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<bool> ParseOpt<bool>(const String& str)
	{
		const String lower = str.trim().lower();

		if (lower == L"true")
		{
			return Optional<bool>(true);
		}
		else if (lower == L"false")
		{
			return Optional<bool>(false);
		}

		return none;
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<char> ParseOpt<char>(const String& str)
	{
		const String t = str.trim();

		if (t.isEmpty)
		{
			return none;
		}

		return static_cast<char>(t[0]);
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<wchar> ParseOpt<wchar>(const String& str)
	{
		const String t = str.trim();

		if (t.isEmpty)
		{
			return none;
		}

		return t[0];
	}

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<String> ParseOpt<String>(const String& str)
	{
		return Optional<String>(str);
	}

	////////////////////////////////////////////////////////////////
	//
	//		ParseOr
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <param name="defaultValue">
	/// 変換に失敗した場合に返す値
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの, 失敗した場合は defaultValue
	/// </returns>
	template <class Type, class U>
	Type ParseOr(const String& str, U&& defaultValue)
	{
		return ParseOpt<Type>(str).value_or(std::forward<U>(defaultValue));
	}
}
