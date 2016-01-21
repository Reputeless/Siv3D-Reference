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
# include "Time.hpp"
# include "Duration.hpp"

namespace s3d
{
	/// <summary>
	/// ストップウォッチ
	/// </summary>
	class Stopwatch
	{
	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit Stopwatch(bool startImmediately = false)
		{
			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを開始・再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start();

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		int32 h() const { return ms() / (1000 * 60 * 60); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		int32 min() const { return ms() / (1000 * 60); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		int32 s() const { return ms() / 1000; }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		int32 ms() const;

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		Milliseconds elapsed() const { return Milliseconds(ms()); }

		/// <summary>
		/// ストップウォッチが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isActive() const noexcept { return m_isActive; }

		/// <summary>
		/// ストップウォッチが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const noexcept { return m_isActive && m_pausing; }

		/// <summary>
		/// ストップウォッチを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause();

		/// <summary>
		/// ストップウォッチが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume();

		/// <summary>
		/// ストップウォッチを停止し、経過時間を 0 にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept;

		/// <summary>
		/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart();

		/// <summary>
		/// ストップウォッチの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const MillisecondsF& time);

	private:

		int32 m_startTimeMillisec = 0;

		int32 m_accumulationMillisec = 0;

		bool m_isActive = false;

		bool m_pausing = true;
	};

	/// <summary>
	/// ストップウォッチ(64bit)
	/// </summary>
	class Stopwatch64
	{
	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit Stopwatch64(bool startImmediately = false)
		{
			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを開始・再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start();

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		int64 h() const { return ms() / (1000 * 60 * 60); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		int64 min() const { return ms() / (1000 * 60); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		int64 s() const { return ms() / 1000; }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		int64 ms() const;

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		Milliseconds elapsed() const {	return Milliseconds(ms()); }

		/// <summary>
		/// ストップウォッチが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isActive() const noexcept { return m_isActive; }

		/// <summary>
		/// ストップウォッチが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const noexcept { return m_isActive && m_pausing; }

		/// <summary>
		/// ストップウォッチを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause();

		/// <summary>
		/// ストップウォッチが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume();

		/// <summary>
		/// ストップウォッチを停止し、経過時間を 0 にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept;

		/// <summary>
		/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart();

		/// <summary>
		/// ストップウォッチの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const MillisecondsF& time);

	private:

		int64 m_startTimeMillisec = 0;

		int64 m_accumulationMillisec = 0;

		bool m_isActive = false;

		bool m_pausing = true;
	};

	/// <summary>
	/// マイクロ秒単位のストップウォッチ
	/// </summary>
	class StopwatchMicrosec
	{
	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit StopwatchMicrosec(bool startImmediately = false)
		{
			if (startImmediately)
			{
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを開始・再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start();

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		int64 h() const { return us() / (1000LL * 1000LL * 60LL * 60LL); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		int64 min() const { return us() / (1000LL * 1000LL * 60LL); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		int64 s() const { return us() / (1000LL * 1000LL); }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		int64 ms() const { return us() / 1000LL; }

		/// <summary>
		/// ストップウォッチの経過時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[マイクロ秒]
		/// </returns>
		int64 us() const;

		/// <summary>
		/// ストップウォッチの経過時間を返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		Microseconds elapsed() const { return Microseconds(us()); }

		/// <summary>
		/// ストップウォッチが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isActive() const { return m_isActive; }

		/// <summary>
		/// ストップウォッチが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		bool isPaused() const { return m_isActive && m_pausing; }

		/// <summary>
		/// ストップウォッチを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause();

		/// <summary>
		/// ストップウォッチが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume();

		/// <summary>
		/// ストップウォッチを停止し、経過時間を 0 にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept;

		/// <summary>
		/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart();

		/// <summary>
		/// ストップウォッチの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const MicrosecondsF& time);

	private:

		int64 m_startTimeMicrosec = 0;

		int64 m_accumulationMicrosec = 0;

		bool m_isActive = false;

		bool m_pausing = true;
	};
}

# include "Stopwatch.inl"
