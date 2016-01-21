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
# include <cassert>
# include "Fwd.hpp"
# include "String.hpp"
# include "StaticAssertMacro.hpp"
# include "FormatInt.hpp"
# include "Optional.hpp"

namespace s3d
{
	////////////////////////////////////////////////////////////////
	//
	//		ToString
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int32 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint32 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int64 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint64 value)
	{
		return detail::FormatInt(value).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int8 value)
	{
		return detail::FormatInt(static_cast<int32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint8 value)
	{
		return detail::FormatInt(static_cast<uint32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int16 value)
	{
		return detail::FormatInt(static_cast<int32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint16 value)
	{
		return detail::FormatInt(static_cast<uint32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(long value)
	{
		return detail::FormatInt(static_cast<int32>(value)).str();
	}

	/// <summary>
	/// 整数を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(unsigned long value)
	{
		return detail::FormatInt(static_cast<uint32>(value)).str();
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int32 value, _Field_range_(2, 36) int32 radix)
	{
		assert(2 <= radix && radix <= 36);
		wchar buf[33];
		::_ltow_s(value, buf, radix);
		return{ buf  };
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint32 value, _Field_range_(2, 36)int32 radix)
	{
		assert(2 <= radix && radix <= 36);
		wchar buf[33];
		::_ultow_s(value, buf, radix);
		return{ buf };
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int64 value, _Field_range_(2, 36) int32 radix)
	{
		assert(2 <= radix && radix <= 36);
		wchar buf[65];
		::_i64tow_s(value, buf, std::size(buf), radix);
		return{ buf };
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint64 value, _Field_range_(2, 36) int32 radix)
	{
		assert(2 <= radix && radix <= 36);
		wchar buf[65];
		::_ui64tow_s(value, buf, std::size(buf), radix);
		return{ buf };
	}

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	String ToString(double value, int32 decimalPlace = 3);

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int8 value, _Field_range_(2, 36) int32 radix)
	{
		return ToString(static_cast<int32>(value), radix);
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint8 value, _Field_range_(2, 36) int32 radix)
	{
		return ToString(static_cast<uint32>(value), radix);
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(int16 value, _Field_range_(2, 36) int32 radix)
	{
		return ToString(static_cast<int32>(value), radix);
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(uint16 value, _Field_range_(2, 36) int32 radix)
	{
		return ToString(static_cast<uint32>(value), radix);
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(long value, _Field_range_(2, 36) int32 radix)
	{
		return ToString(static_cast<int32>(value), radix);
	}

	/// <summary>
	/// 整数を指定した基数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <param name="radix">
	///	基数
	///	</param>
	/// <remarks>
	///	基数は [2-36] の範囲で指定します。
	///	</remarks>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(unsigned long value, _Field_range_(2, 36) int32 radix)
	{
		return ToString(static_cast<uint32>(value), radix);
	}

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(float value, int32 decimalPlace = 3)
	{
		return ToString(static_cast<double>(value), decimalPlace);
	}

	/// <summary>
	/// 数値を文字列で表します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <param name="decimalPlace">
	/// 小数点以下の最大桁数
	/// </param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	inline String ToString(long double value, int32 decimalPlace = 3)
	{
		return ToString(static_cast<double>(value), decimalPlace);
	}

	////////////////////////////////////////////////////////////////
	//
	//		FromString
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <class Type>
	Type FromString(const String& str, int32 radix = 0);

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline int8 FromString<int8>(const String& str, int32 radix)
	{
		const int32 result = ::wcstol(str.c_str(), nullptr, radix);
		return (result < INT8_MIN || INT8_MAX < result) ? 0 : static_cast<int8>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline uint8 FromString<uint8>(const String& str, int32 radix)
	{
		const uint32 result = ::wcstoul(str.c_str(), nullptr, radix);
		return (UINT8_MAX < result) ? 0 : static_cast<uint8>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline int16 FromString<int16>(const String& str, int32 radix)
	{
		const int32 result = ::wcstol(str.data(), nullptr, radix);
		return (result < INT16_MIN || INT16_MAX < result) ? 0 : static_cast<int16>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline uint16 FromString<uint16>(const String& str, int32 radix)
	{
		const uint32 result = ::wcstoul(str.data(), nullptr, radix);
		return (UINT16_MAX < result) ? 0 : static_cast<uint16>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline int32 FromString<int32>(const String& str, int32 radix)
	{
		return ::wcstol(str.data(), nullptr, radix);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline uint32 FromString<uint32>(const String& str, int32 radix)
	{
		return ::wcstoul(str.data(), nullptr, radix);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline long FromString<long>(const String& str, int32 radix)
	{
		return ::wcstol(str.data(), nullptr, radix);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline unsigned long FromString<unsigned long>(const String& str, int32 radix)
	{
		return ::wcstoul(str.data(), nullptr, radix);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline int64 FromString<int64>(const String& str, int32 radix)
	{
		return ::_wcstoi64(str.data(), nullptr, radix);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline uint64 FromString<uint64>(const String& str, int32 radix)
	{
		return ::_wcstoui64(str.data(), nullptr, radix);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123.45")
	/// </param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline float FromString<float>(const String& str, int32)
	{
		return static_cast<float>(::_wtof(str.data()));
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123.45")
	/// </param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline double FromString<double>(const String& str, int32)
	{
		return ::_wtof(str.data());
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123.45")
	/// </param>
	/// <returns>
	/// 文字列から変換された数値
	/// </returns>
	template <>
	inline long double FromString<long double>(const String& str, int32)
	{
		return ::_wtof(str.data());
	}

	////////////////////////////////////////////////////////////////
	//
	//		FromStringOpt
	//
	////////////////////////////////////////////////////////////////

	template<class Type>
	Optional<Type> FromStringOpt(const String& str, int32 radix = 0);

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123", L"0x7F")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<int8> FromStringOpt<int8>(const String& str, int32 radix)
	{
		wchar* p;
		const int32 result = ::wcstol(str.data(), &p, radix);

		if (str.data() == p || result < INT8_MIN || INT8_MAX < result)
		{
			return none;
		}

		return static_cast<int8>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<uint8> FromStringOpt<uint8>(const String& str, int32 radix)
	{
		wchar* p;
		const uint32 result = ::wcstol(str.data(), &p, radix);

		if (str.data() == p || UINT8_MAX < result)
		{
			return none;
		}

		return static_cast<uint8>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<int16> FromStringOpt<int16>(const String& str, int32 radix)
	{
		wchar* p;
		const int32 result = ::wcstol(str.data(), &p, radix);

		if (str.data() == p || result < INT16_MIN || INT16_MAX < result)
		{
			return none;
		}

		return static_cast<int16>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<uint16> FromStringOpt<uint16>(const String& str, int32 radix)
	{
		wchar* p;
		const uint32 result = ::wcstol(str.data(), &p, radix);

		if (str.data() == p || UINT16_MAX < result)
		{
			return none;
		}

		return static_cast<uint16>(result);
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<int32> FromStringOpt<int32>(const String& str, int32 radix)
	{
		wchar* p;
		const int32 result = ::wcstol(str.data(), &p, radix);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<uint32> FromStringOpt<uint32>(const String& str, int32 radix)
	{
		wchar* p;
		const uint32 result = ::wcstoul(str.data(), &p, radix);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<long> FromStringOpt<long>(const String& str, int32 radix)
	{
		wchar* p;
		const long result = ::wcstol(str.data(), &p, radix);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<unsigned long> FromStringOpt<unsigned long>(const String& str, int32 radix)
	{
		wchar* p;
		const unsigned long result = ::wcstoul(str.data(), &p, radix);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<int64> FromStringOpt<int64>(const String& str, int32 radix)
	{
		wchar* p;
		const int64 result = ::_wcstoi64(str.data(), &p, radix);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"12345", L"0xFF")
	/// </param>
	/// <param name="radix">
	///	使用する基数、0 の場合は自動
	///	</param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<uint64> FromStringOpt<uint64>(const String& str, int32 radix)
	{
		wchar* p;
		const uint64 result = ::_wcstoui64(str.data(), &p, radix);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123.45")
	/// </param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<float> FromStringOpt<float>(const String& str, int32)
	{
		wchar* p;
		const float result = static_cast<float>(::wcstod(str.data(), &p));

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123.45")
	/// </param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<double> FromStringOpt<double>(const String& str, int32)
	{
		wchar* p;
		const double result = ::wcstod(str.data(), &p);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	/// <summary>
	/// 文字列から数値に変換します。
	/// </summary>
	/// <param name="str">
	///	変換される文字列（例: L"123.45")
	/// </param>
	/// <returns>
	/// 文字列から変換された数値の Optional, 失敗した場合は none
	/// </returns>
	template <>
	inline Optional<long double> FromStringOpt<long double>(const String& str, int32)
	{
		wchar* p;
		const long double result = ::wcstod(str.data(), &p);

		if (str.data() == p)
		{
			return none;
		}

		return result;
	}

	////////////////////////////////////////////////////////////////
	//
	//		AsUint
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	///	浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	inline uint32 AsUint(float value)
	{
		s3d_static_assert(sizeof(uint32) == sizeof(float));
		return *static_cast<const uint32*>(static_cast<const void*>(&value));
	}

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	///	浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	inline uint64 AsUint(double value)
	{
		s3d_static_assert(sizeof(uint64) == sizeof(double));
		return *static_cast<const uint64*>(static_cast<const void*>(&value));
	}

	/// <summary>
	/// 浮動小数点数値のビット列を整数として解釈します。
	/// </summary>
	/// <param name="value">
	///	浮動小数点数値
	/// </param>
	/// <returns>
	/// ビット列を整数として解釈した値
	/// </returns>
	inline uint64 AsUint(long double value)
	{
		s3d_static_assert(sizeof(uint64) == sizeof(long double));
		return *static_cast<const uint64*>(static_cast<const void*>(&value));
	}

	////////////////////////////////////////////////////////////////
	//
	//		ToBinary
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 整数を 2 進数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	template <class Type>
	inline typename std::enable_if<!std::is_floating_point<Type>::value, String>::type ToBinary(Type value)
	{
		return ToString(value, 2);
	}

	/// <summary>
	/// 浮動小数点数のビット表現を 2 進数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	template <class Type>
	inline typename std::enable_if<std::is_floating_point<Type>::value, String>::type ToBinary(Type value)
	{
		return ToString(AsUint(value), 2);
	}

	////////////////////////////////////////////////////////////////
	//
	//		ToOctal
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 整数を 8 進数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	template <class Type>
	inline typename std::enable_if<!std::is_floating_point<Type>::value, String>::type ToOctal(Type value)
	{
		return ToString(value, 8);
	}

	/// <summary>
	/// 浮動小数点数のビット表現を 8 進数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	template <class Type>
	inline typename std::enable_if<std::is_floating_point<Type>::value, String>::type ToOctal(Type value)
	{
		return ToString(AsUint(value), 8);
	}

	////////////////////////////////////////////////////////////////
	//
	//		ToHex
	//
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 整数を 16 進数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	整数
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	template <class Type>
	inline typename std::enable_if<!std::is_floating_point<Type>::value, String>::type ToHex(Type value)
	{
		return ToString(value, 16);
	}

	/// <summary>
	/// 浮動小数点数のビット表現を 16 進数の文字列で表します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <returns>
	///	変換した文字列
	///	</returns>
	template <class Type>
	inline typename std::enable_if<std::is_floating_point<Type>::value, String>::type ToHex(Type value)
	{
		return ToString(AsUint(value), 16);
	}

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	/// <summary>
	/// 表現できる最大の数値を返します。
	/// </summary>
	/// <returns>
	/// 表現できる最大の数値
	/// </returns>
	template<class Type>
	inline constexpr Type Largest()
	{
		return std::numeric_limits<Type>::max();
	}

	/// <summary>
	/// 表現できる最小の数値を返します。
	/// </summary>
	/// <returns>
	/// 表現できる最小の数値
	/// </returns>
	template<class Type>
	inline constexpr Type Smallest()
	{
		return std::numeric_limits<Type>::lowest();
	}

	/// <summary>
	/// 正の無限大を返します。
	/// </summary>
	/// <returns>
	/// 正の無限大
	/// </returns>
	template<class Type>
	inline constexpr Type Infinity()
	{
		return std::numeric_limits<Type>::infinity();
	}

	/// <summary>
	/// 数値が非数 (NaN) であるかを示します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <returns>
	///	数値が非数 (NaN) である場合 true, それ以外の場合は false
	///	</returns>
	template<class Type>
	inline bool IsNaN(Type value)
	{
		return !!::_isnan(value);
	}

	/// <summary>
	/// 数値が有限値であるかを示します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <returns>
	///	数値が有限値である場合 true, それ以外の場合は false
	///	</returns>
	template<class Type>
	inline bool IsFinite(Type value)
	{
		return !!::_finite(value);
	}

	/// <summary>
	/// 数値が無限であるかを示します。
	/// </summary>
	/// <param name="value">
	///	数値
	///	</param>
	/// <returns>
	///	数値が無限である場合 true, それ以外の場合は false
	///	</returns>
	template<class Type>
	inline bool IsInfinity(Type value)
	{
		return !!(::_fpclass(value) & (_FPCLASS_NINF | _FPCLASS_PINF));
	}
}
