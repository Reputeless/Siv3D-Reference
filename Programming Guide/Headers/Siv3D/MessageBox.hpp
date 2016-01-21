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
# ifdef	MessageBox
#  undef MessageBox
# endif
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// メッセージボックスのスタイル
	/// </summary>
	enum class MessageBoxStyle
	{
		/// <summary>
		/// [OK]
		/// </summary>
		Ok,

		/// <summary>
		/// [OK] [キャンセル]
		/// </summary>
		OkCancel,

		/// <summary>
		/// [はい] [いいえ]
		/// </summary>
		YesNo,

		/// <summary>
		/// [はい] [いいえ] [キャンセル]
		/// </summary>
		YesNoCancel,

		/// <summary>
		/// [再試行] [キャンセル]
		/// </summary>
		RetryCancel,

		/// <summary>
		/// [キャンセル] [再実行] [続行]
		/// </summary>
		CancelRetryContinue,
	};

	/// <summary>
	/// メッセージボックスの入力
	/// </summary>
	enum class MessageBoxCommand
	{
		/// <summary>
		/// [OK]
		/// </summary>
		Ok,

		/// <summary>
		/// [キャンセル]
		/// </summary>
		Cancel,

		/// <summary>
		/// [はい]
		/// </summary>
		Yes,

		/// <summary>
		/// [いいえ]
		/// </summary>
		No,

		/// <summary>
		/// [続行]
		/// </summary>
		Continue,

		/// <summary>
		/// [再試行] または [再実行]
		/// </summary>
		Retry,
	};

	/// <summary>
	/// メッセージボックス
	/// </summary>
	/// <remarks>
	/// メッセージボックスに関する機能を提供します。
	/// </remarks>
	namespace MessageBox
	{
		/// <summary>
		/// メッセージボックスを表示します。
		/// </summary>
		/// <param name="text">
		/// メッセージ
		/// </param>
		/// <param name="style">
		/// メッセージボックスのスタイル
		/// </param>
		/// <param name="defaultButton">
		/// 既定のボタン（左から何番目か）
		/// </param>
		/// <returns>
		/// ユーザが押したボタン
		/// </returns>
		MessageBoxCommand Show(const String& text, MessageBoxStyle style = MessageBoxStyle::Ok, int32 defaultButton = 0);

		/// <summary>
		/// メッセージボックスを表示します。
		/// </summary>
		/// <param name="title">
		/// メッセージボックスのタイトル
		/// </param>
		/// <param name="text">
		/// メッセージ
		/// </param>
		/// <param name="style">
		/// メッセージボックスのスタイル
		/// </param>
		/// <param name="defaultButton">
		/// 既定のボタン（左から何番目か）
		/// </param>
		/// <returns>
		/// ユーザが押したボタン
		/// </returns>
		MessageBoxCommand Show(const String& title, const String& text, MessageBoxStyle style = MessageBoxStyle::Ok, int32 defaultButton = 0);
	}
}
