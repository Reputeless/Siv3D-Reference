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
	/// スピードが変更可能なストップウォッチ
	/// </summary>
	class VariableSpeedStopwatch
	{
	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="speed">
		/// 実際の時刻の進み方を 1.0 とした際のスピード
		/// </param>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit VariableSpeedStopwatch(double speed = 1.0, bool startImmediately = false)
			: m_speed(speed)
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
		void start()
		{
			if (!m_pausing)
			{
				return;
			}

			m_isActive = true;

			m_pausing = false;

			m_lastTimeNanosec = Time::GetNanosec();
		}

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		int64 h() const { return ns() / (1'000'000'000LL * 3'600LL); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		int64 min() const { return ns() / (1'000'000'000LL * 60LL); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		int64 s() const { return ns() / 1'000'000'000LL; }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		int64 ms() const { return ns() / 1'000'000LL; }

		/// <summary>
		/// ストップウォッチの経過時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[マイクロ秒]
		/// </returns>
		int64 us() const { return ns() / 1'000LL; }

		/// <summary>
		/// ストップウォッチの経過時間を返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		Milliseconds elapsed() const { return Milliseconds(ns() / 1'000'000LL); }

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
		void pause()
		{
			m_accumulationNanosec = ns();

			m_pausing = true;
		}

		/// <summary>
		/// ストップウォッチが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume()
		{
			if (!isPaused())
			{
				return;
			}

			start();
		}

		/// <summary>
		/// ストップウォッチを停止し、経過時間を 0 にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept
		{
			m_accumulationNanosec = 0;

			m_isActive = false;

			m_pausing = true;
		}

		/// <summary>
		/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart()
		{
			reset();

			start();
		}

		/// <summary>
		/// ストップウォッチの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const MicrosecondsF& time)
		{
			m_isActive |= (time.count() != 0);

			m_accumulationNanosec = static_cast<int64>(time.count() * 1'000LL);

			m_lastTimeNanosec = Time::GetNanosec();
		}

		/// <summary>
		/// ストップウォッチのスピードを設定します。
		/// </summary>
		/// <param name="speed">
		/// 新しく設定するスピード (1.0 が通常)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setSpeed(double speed)
		{
			if (speed == m_speed)
			{
				return;
			}

			m_accumulationNanosec = ns();

			m_speed = speed;
		}

		/// <summary>
		/// ストップウォッチのスピードを返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチのスピード
		/// </returns>
		double getSpeed() const noexcept
		{
			return m_speed;
		}

	private:

		int64 ns() const
		{
			const int64 t = Time::GetNanosec();

			if (!m_isActive)
			{
				return 0;
			}

			if (m_pausing)
			{
				return m_accumulationNanosec;
			}

			const int64 delta = static_cast<int64>((t - m_lastTimeNanosec) * m_speed);

			m_accumulationNanosec += delta;

			m_lastTimeNanosec = t;

			return m_accumulationNanosec;
		}

		double m_speed = 1.0;

		mutable int64 m_lastTimeNanosec = 0;

		mutable int64 m_accumulationNanosec = 0;

		bool m_isActive = false;

		bool m_pausing = true;
	};
}
