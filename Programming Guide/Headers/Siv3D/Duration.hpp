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
# include <iostream>
# include <chrono>
# include "Types.hpp"

namespace s3d
{
	/// <summary>
	/// 日数
	/// </summary>
	using Days = std::chrono::duration<int32, std::ratio<86400>>;

	/// <summary>
	/// 日数
	/// </summary>
	using DaysF = std::chrono::duration<long double, std::ratio<86400>>;


	/// <summary>
	/// 時間
	/// </summary>
	using Hours = std::chrono::hours;

	/// <summary>
	/// 時間
	/// </summary>
	using HoursF = std::chrono::duration<long double, std::ratio<3600>>;


	/// <summary>
	/// 分
	/// </summary>
	using Minutes = std::chrono::minutes;

	/// <summary>
	/// 分
	/// </summary>
	using MinutesF = std::chrono::duration<long double, std::ratio<60>>;


	/// <summary>
	/// 秒
	/// </summary>
	using Seconds = std::chrono::seconds;

	/// <summary>
	/// 秒
	/// </summary>
	using SecondsF = std::chrono::duration<long double>;


	/// <summary>
	/// ミリ秒
	/// </summary>
	using Milliseconds = std::chrono::milliseconds;

	/// <summary>
	/// ミリ秒
	/// </summary>
	using MillisecondsF = std::chrono::duration<long double, std::milli>;


	/// <summary>
	/// マイクロ秒
	/// </summary>
	using Microseconds = std::chrono::microseconds;

	/// <summary>
	/// マイクロ秒
	/// </summary>
	using MicrosecondsF = std::chrono::duration<long double, std::micro>;


	/// <summary>
	/// ナノ秒
	/// </summary>
	using Nanoseconds = std::chrono::nanoseconds;

	/// <summary>
	/// ナノ秒
	/// </summary>
	using NanosecondsF = std::chrono::duration<long double, std::nano>;

	/// <summary>
	/// 時間の単位を変換します。
	/// </summary>
	/// <param name="duration">
	/// 変換する時間
	/// </param>
	/// <returns>
	/// DurationTo 型に変換された時間
	/// </returns>
	template<class DurationTo, class DurationFrom> inline constexpr DurationTo DurationCast(const DurationFrom& duration)
	{
		return std::chrono::duration_cast<DurationTo>(duration);
	}

	namespace literals
	{
		inline namespace chrono_literals
		{
			inline constexpr Days operator "" _d(unsigned long long days)
			{
				return Days(days);
			}

			inline constexpr DaysF operator "" _d(long double days)
			{
				return DaysF(days);
			}
		}
	}

	inline std::wostream& operator << (std::wostream& output, const Days& days)
	{
		return output << days.count() << L"d";
	}

	inline std::wostream& operator << (std::wostream& output, const DaysF& days)
	{
		return output << days.count() << L"d";
	}

	inline std::wostream& operator << (std::wostream& output, const Hours& hours)
	{
		return output << hours.count() << L"h";
	}

	inline std::wostream& operator << (std::wostream& output, const HoursF& hours)
	{
		return output << hours.count() << L"h";
	}

	inline std::wostream& operator << (std::wostream& output, const Minutes& minutes)
	{
		return output << minutes.count() << L"min";
	}

	inline std::wostream& operator << (std::wostream& output, const MinutesF& minutes)
	{
		return output << minutes.count() << L"min";
	}

	inline std::wostream& operator << (std::wostream& output, const Seconds& seconds)
	{
		return output << seconds.count() << L"s";
	}

	inline std::wostream& operator << (std::wostream& output, const SecondsF& seconds)
	{
		return output << seconds.count() << L"s";
	}

	inline std::wostream& operator << (std::wostream& output, const Milliseconds& milliseconds)
	{
		return output << milliseconds.count() << L"ms";
	}

	inline std::wostream& operator << (std::wostream& output, const MillisecondsF& milliseconds)
	{
		return output << milliseconds.count() << L"ms";
	}

	inline std::wostream& operator << (std::wostream& output, const Microseconds& microseconds)
	{
		return output << microseconds.count() << L"us";
	}

	inline std::wostream& operator << (std::wostream& output, const MicrosecondsF& microseconds)
	{
		return output << microseconds.count() << L"us";
	}

	inline std::wostream& operator << (std::wostream& output, const Nanoseconds& nanoseconds)
	{
		return output << nanoseconds.count() << L"ns";
	}

	inline std::wostream& operator << (std::wostream& output, const NanosecondsF& nanoseconds)
	{
		return output << nanoseconds.count() << L"ns";
	}
}
