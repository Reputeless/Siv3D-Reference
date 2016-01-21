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
# include <wchar.h>
# include <sal.h>
# include "Types.hpp"
# define HalfWidthSpace L' '
# define FullWidthSpace L'　'

namespace s3d
{
	/// <summary>
	/// 10 進数の数字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 10 進数の数字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsDigit(uint32 ch)
	{
		return (ch - L'0') <= (L'9' - L'0');
	}

	/// <summary>
	/// アルファベットの小文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットの小文字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsLower(uint32 ch)
	{
		return (ch - L'a') <= (L'z' - L'a');
	}

	/// <summary>
	/// アルファベットの大文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットの大文字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsUpper(uint32 ch)
	{
		return (ch - L'A') <= (L'Z' - L'A');
	}

	/// <summary>
	/// アルファベットであるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// アルファベットである場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsAlpha(uint32 ch)
	{
		return IsLower(ch) || IsUpper(ch);
	}

	/// <summary>
	/// アルファベットもしくは数字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 1アルファベットもしくは数字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsAlnum(uint32 ch)
	{
		return IsDigit(ch) || IsAlpha(ch);
	}

	/// <summary>
	/// 16 進数の数字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 16 進数の数字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsXdigit(uint32 ch)
	{
		return IsDigit(ch) || ((ch - L'A') <= (L'F' - L'A')) || ((ch - L'a') <= (L'f' - L'a'));
	}

	/// <summary>
	/// 制御文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 制御文字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsControl(uint32 ch)
	{
		return (ch <= 0x1F) || ((ch - 0x7F) <= (0x9F - 0x7F));
	}

	/// <summary>
	/// 空白文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <remarks>
	/// L' ', L'\t', L'　' が該当します。
	/// </remarks>
	/// <returns>
	/// 空白文字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsBlank(uint32 ch)
	{
		return (ch == HalfWidthSpace) || (ch == L'\t') || (ch == FullWidthSpace);
	}

	/// <summary>
	/// 空白類文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <remarks>
	/// L' ', L'\t', L'\n', L'\v', L'\f', L'\r', L'　' が該当します。
	/// </remarks>
	/// <returns>
	/// 空白類文字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline constexpr bool IsSpace(uint32 ch)
	{
		return ((ch - L'\t') <= (L'\r' - L'\t')) || (ch == HalfWidthSpace) || (ch == FullWidthSpace);
	}

	/// <summary>
	/// 印字可能文字であるかを返します。
	/// </summary>
	/// <param name="ch">
	/// 文字
	/// </param>
	/// <returns>
	/// 印字可能文字である場合 true, それ以外の場合は false
	/// </returns>
	_Check_return_
	inline bool IsPrint(uint32 ch)
	{
		return !!::iswprint(static_cast<wchar_t>(ch));
	}
}

# undef HalfWidthSpace
# undef FullWidthSpace
