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

namespace s3d
{
	/// <summary>
	/// イベント付きストップウォッチ
	/// </summary>
	class EventTimer : public Stopwatch
	{
	private:

		struct Event
		{
			String name;

			MillisecondsF time;

			enum class State { StandBy, Triggered, Sleep } state;
		};

		Array<Event> m_events;

	public:

		/// <summary>
		/// イベントを作成します。
		/// </summary>
		/// <param name="event">
		/// イベント名
		/// </param>
		/// <param name="time">
		/// イベントが発生するタイマー経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void addEvent(const String& event, const MillisecondsF& time)
		{
			m_events.push_back({ event, time, Event::State::StandBy });

			std::stable_sort(m_events.begin(), m_events.end(),
				[](const Event& a, const Event& b)
			{
				return a.time < b.time;
			});
		}

		/// <summary>
		/// イベントの状態を更新します。
		/// </summary>
		/// <returns>
		/// タイマーの経過時間[ミリ秒]
		/// </returns>
		Milliseconds update()
		{
			const auto time = elapsed();

			for (auto& event : m_events)
			{
				if (event.state == Event::State::StandBy && time >= event.time)
				{
					event.state = Event::State::Triggered;
				}
				else if (event.state == Event::State::Triggered)
				{
					event.state = Event::State::Sleep;
				}
			}

			return DurationCast<Milliseconds>(time);
		}

		/// <summary>
		/// 直前の更新でイベントが発生したかどうかを返します。
		/// </summary>
		/// <param name="_event">
		/// イベント名
		/// </param>
		/// <returns>
		/// 直前の更新でイベントが発生したときは true, それ以外の場合は false
		/// </returns>
		bool onTriggered(const String& _event) const
		{
			for (const auto& event : m_events)
			{
				if (event.state == Event::State::Triggered && event.name == _event)
				{
					return true;
				}
			}

			return false;
		}

		/// <summary>
		/// 直前の更新で発生したイベント名を返します。
		/// </summary>
		/// <remarks>
		/// イベントは時間の早い順、そして追加した順にソートされています。
		/// </remarks>
		/// <returns>
		/// 直前の更新で発生したいイベント一覧
		/// </returns>
		Array<String> getTriggeredEvents() const
		{
			Array<String> events;

			for (const auto& event : m_events)
			{
				if (event.state == Event::State::Triggered)
				{
					events.push_back(event.name);
				}
			}

			return events;
		}

		/// <summary>
		/// イベントを初期状態に戻し、タイマーを停止して経過時間を 0 にリセットします。
		/// </summary>
		/// <remarks>
		/// イベントを削除するには clearEvents() を使います。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void reset()
		{
			Stopwatch::reset();

			for (auto& event : m_events)
			{
				event.state = Event::State::StandBy;
			}
		}

		/// <summary>
		/// イベントを初期状態に戻し、経過時間を 0 にリセットしてタイマーを開始します。
		/// </summary>
		/// <remarks>
		/// イベントを削除するには clearEvents() を使います。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void restart()
		{
			reset();

			start();
		}

		/// <summary>
		/// すべてのイベントを削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clearEvents()
		{
			m_events.clear();
		}
	};
}
