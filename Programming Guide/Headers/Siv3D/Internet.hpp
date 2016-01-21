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

namespace s3d
{
	/// <summary>
	/// インターネット
	/// </summary>
	/// <remarks>
	/// インターネット上のデータにアクセスする機能を提供します。
	/// </remarks>
	namespace Internet
	{
		/// <summary>
		/// コンピューターがインターネットに接続されているかを調べます。
		/// </summary>
		/// <returns>
		/// コンピューターがインターネットに接続されていれば true, されていなければ false
		/// </returns>
		bool IsConnected();

		/// <summary>
		/// 指定した URL を Internet Explorer で開きます。
		/// </summary>
		/// <param name="url">
		/// http:// もしくは https:// で始まる URL
		/// </param>
		/// <remarks>
		/// 最後に LaunchIE() または LaunchWebBrowser() を呼んでから
		/// 1000 ミリ秒以内に再度呼ばれると関数は失敗します。
		/// </remarks>
		/// <returns>
		/// 成功した場合 true, 失敗した場合 false
		/// </returns>
		bool LaunchIE(const FilePath& url);

		/// <summary>
		/// 指定した URL をユーザの既定のブラウザで開きます。
		/// </summary>
		/// <param name="url">
		/// http:// もしくは https:// で始まる URL
		/// </param>
		/// 最後に LaunchIE() または LaunchWebBrowser() を呼んでから
		/// 1000 ミリ秒以内に再度呼ばれると関数は失敗します。
		/// <returns>
		/// 成功した場合 true, 失敗した場合 false
		/// </returns>
		bool LaunchWebBrowser(const FilePath& url);
	}
}
