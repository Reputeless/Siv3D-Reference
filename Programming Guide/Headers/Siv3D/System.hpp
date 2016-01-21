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
# include <memory>
# include "Fwd.hpp"
# include "Duration.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// ウィンドウイベントのフラグ
	/// </summary>
	struct WindowEvent
	{
		enum Flag : uint32
		{
			/// <summary>
			/// ウィンドウの [x] ボタンが押される
			/// </summary>
			CloseButton = 0x01,

			/// <summary>
			/// エスケープキーが押される
			/// </summary>
			EscapeKey = 0x02,

			/// <summary>
			/// マウスの左クリック
			/// </summary>
			LeftClick = 0x04,

			/// <summary>
			/// マウスの右クリック
			/// </summary>
			RightClick = 0x08,

			/// <summary>
			/// ウィンドウのフォーカスが外れる
			/// </summary>
			Unfocus = 0x10,

			/// <summary>
			/// 何らかのキーが押される
			/// </summary>
			AnyKey = 0x20,

			/// <summary>
			/// デフォルト（ウィンドウの [x] ボタンが押されるか、エスケープキーが押される）
			/// </summary>
			Default = CloseButton | EscapeKey,

			/// <summary>
			/// 設定しない
			/// </summary>
			/// <remarks>
			/// 必ず System::Exit() を実行して終了する必要があります。
			/// </remarks>
			Manual = 0x00,
		};
	};

	enum class LaunchVerb
	{
		Open,

		Edit
	};

	class ProcessInfo
	{
	private:

		struct ProcessInfoDetail;

		std::shared_ptr<ProcessInfoDetail> m_detail;

	public:

		ProcessInfo();

		bool isRunning() const;

		Optional<int32> getExitCode() const;

		ProcessInfoDetail* _detail() const;
	};

	namespace System
	{
		/// <summary>
		/// グラフィックスと入力を更新します。またフレームの更新が 60fps 以下になるよう時間を調整します。
		/// 終了イベントが発生した場合や、エンジンの内部でエラーが発生した場合 false を返します。
		/// </summary>
		/// <returns>
		/// アプリケーションが続行できる場合 true, アプリケーションを終了する場合 false
		/// </returns>
		bool Update();

		/// <summary>
		/// アプリケーションの終了をエンジンに伝えます。
		/// 次の System::Update() は必ず false を返します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Exit();

		/// <summary>
		/// アプリケーションを終了させるウィンドウイベントを設定します。
		/// </summary>
		/// <param name="windowEventFlag">
		/// WindowEvent::Flag の組み合わせ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetExitEvent(int32 windowEventFlag);

		/// <summary>
		/// 直前のフレームで発生したウィンドウイベントを返します。
		/// </summary>
		/// <returns>
		/// 直前のフレームで発生したウィンドウイベントを表す WindowEvent::Flag の組み合わせ
		/// </returns>
		int32 GetPreviousEvent();

		/// <summary>
		/// 指定したミリ秒だけ処理を停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Sleep(int32 milliseconds);

		/// <summary>
		/// 指定したミリ秒だけ処理を停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		inline void Sleep(MillisecondsF milliseconds)
		{
			Sleep(static_cast<int32>(milliseconds.count()));
		}

		/// <summary>
		/// 指定したミリ秒だけ処理を停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SleepAccurately(double milliseconds);

		/// <summary>
		/// 指定したミリ秒だけ処理を停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		inline void SleepAccurately(MillisecondsF milliseconds)
		{
			SleepAccurately(static_cast<double>(milliseconds.count()));
		}

		/// <summary>
		/// System::Update() が呼ばれた回数（＝更新したフレーム数）を返します。
		/// </summary>
		/// <returns>
		/// System::Update() が呼ばれた回数
		/// </returns>
		int32 FrameCount();

		bool LaunchFile(const FilePath& fileName, LaunchVerb verb, const String& params = L"");

		bool ExploreFolder(const FilePath& path);

		ProcessInfo CreateProcess(const FilePath& applicationName, const String& params = L"");
	}
}