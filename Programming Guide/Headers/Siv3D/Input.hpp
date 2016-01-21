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
# include "Fwd.hpp"
# include "Key.hpp"
# include "Touch.hpp"
# include "Gamepad.hpp"

namespace s3d
{
	/// <summary>
	/// 入力
	/// </summary>
	/// <remarks>
	/// ユーザの入力に関する機能を提供します。
	/// </remarks>
	namespace Input
	{
		/// <summary>
		/// 何らかのキーがクリックされたかを返します。
		/// </summary>
		/// <returns>
		/// 何らかのキーがクリックされた場合 true, それ以外の場合は false
		/// </returns>
		bool AnyKeyClicked();

		/// <summary>
		/// 何らかのキーが押されているかを返します。
		/// </summary>
		/// <returns>
		/// 何らかのキーが押されている場合 true, それ以外の場合は false
		/// </returns>
		bool AnyKeyPressed();

		/// <summary>
		/// 何らかのキーが離されたかを返します。
		/// </summary>
		/// <returns>
		/// 何らかのキーが離された場合 true, それ以外の場合は false
		/// </returns>
		bool AnyKeyReleased();

		/// <summary>
		/// 現在アクティブなキーを取得します。
		/// </summary>
		/// <returns>
		/// 現在アクティブなキーの一覧
		/// </returns>
		Array<Key> GetActiveKeys();

		/// <summary>
		/// 文字入力を取得します。
		/// </summary>
		/// <returns>
		/// 文字入力
		/// </returns>
		String GetChars();

		/// <summary>
		/// 文字入力を取得し処理します。
		/// </summary>
		/// <param name="text">
		/// 文字入力処理用のバッファ
		/// </param>
		/// <returns>
		/// 文字入力
		/// </returns>
		void GetCharsHelper(String& text);

		/// <summary>
		/// マルチタッチをサポートしているかを返します。
		/// </summary>
		/// <returns>
		/// マルチタッチをサポートしている場合 true, それ以外の場合は false
		/// </returns>
		bool SupportsMultiTouch();

		/// <summary>
		/// 現在のマルチタッチを取得します。
		/// </summary>
		/// <returns>
		/// 現在のタッチの情報一覧
		/// </returns>
		Array<Touch> GetTouches();

		/// <summary>
		/// PC に接続されているゲームパッドの一覧を取得します。
		/// </summary>
		/// <returns>
		/// PC に接続されているゲームパッドの一覧
		/// </returns>
		Array<GamepadInfo> EnumerateGamepads();
	};
}
