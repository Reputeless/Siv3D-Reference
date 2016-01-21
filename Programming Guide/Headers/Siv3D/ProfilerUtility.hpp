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
# include <intrin.h>
# include "Time.hpp"
# include "Logger.hpp"
# include "ApplicationUtility.hpp"

namespace s3d
{
	/// <summary>
	/// ミリ秒カウンター
	/// </summary>
	/// <remarks>
	/// 経過時間をミリ秒で計測します。
	/// </remarks>
	class MillisecClock
	{
	private:

		uint64 m_start = Time::GetMicrosec();

	public:

		/// <summary>
		/// 経過時間（ミリ秒）
		/// </summary>
		uint64 ms() const { return (Time::GetMicrosec() - m_start) / 1000ULL; }

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { LOG(ms(), L"ms"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void print() const { Println(ms(), L"ms"); }
	};

	/// <summary>
	/// マイクロ秒カウンター
	/// </summary>
	/// <remarks>
	/// 経過時間をマイクロ秒で計測します。
	/// </remarks>
	class MicrosecClock
	{
	private:

		uint64 m_start = Time::GetMicrosec();

	public:

		/// <summary>
		/// 経過時間（マイクロ秒）
		/// </summary>
		uint64 us() const { return Time::GetMicrosec() - m_start; }

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { LOG(us(), L"us"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void print() const { Println(us(), L"us"); }
	};

	/// <summary>
	/// CPU サイクルカウンター
	/// </summary>
	/// <remarks>
	/// 経過時間を CPU サイクル数で計測します。
	/// </remarks>
	class RDTSCClock
	{
	private:

		uint64 m_start = ::__rdtsc();

	public:

		/// <summary>
		/// 経過時間（CPU サイクル数）
		/// </summary>
		uint64 cycles() const { return ::__rdtsc() - m_start; }

		/// <summary>
		/// ログに経過時間を出力します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void log() const { LOG(cycles(), L"cycles"); }

		/// <summary>
		/// 経過時間をデバッグ表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void print() const { Println(cycles(), L"cycles"); }
	};
}
