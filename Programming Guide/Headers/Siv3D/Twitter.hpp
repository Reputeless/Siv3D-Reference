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
# include "Image.hpp"

namespace s3d
{
	/// <summary>
	/// Twitter クライアント
	/// </summary>
	class TwitterClient
	{
	private:

		class CTwitterClient;

		std::shared_ptr<CTwitterClient> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TwitterClient();

		/// <summary>
		/// Twitter クライアントを初期化します。
		/// </summary>
		/// <param name="API_key">
		/// Twitter から付与された API key
		/// </param>
		/// <param name="API_secret">
		/// Twitter から付与された API secret
		/// </param>
		TwitterClient(const String& API_key, const String& API_secret);

		/// <summary>
		/// Twitter クライアントを初期化します。
		/// </summary>
		/// <param name="API_key">
		/// Twitter から付与された API key
		/// </param>
		/// <param name="API_secret">
		/// Twitter から付与された API secret
		/// </param>
		/// <returns>
		/// 初期化に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const String& API_key, const String& API_secret);

		/// <summary>
		/// Twitter oAuth 認証ページを開きます。
		/// </summary>
		/// <returns>
		/// 認証ページのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool openTokenPage();

		/// <summary>
		/// PIN による認証を行います。
		/// </summary>
		/// <param name="pin">
		/// PIN
		/// </param>
		/// <returns>
		/// 認証に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool verifyPIN(const String& pin);

		/// <summary>
		/// 認証されているかを示します。
		/// </summary>
		bool authorized() const;

		/// <summary>
		/// スクリーンネーム
		/// </summary>
		String getScreenName() const;

		/// <summary>
		/// ユーザ ID
		/// </summary>
		String getUserID() const;

		/// <summary>
		/// メッセージを投稿します。
		/// </summary>
		/// <param name="message">
		/// 投稿するメッセージ
		/// </param>
		/// <returns>
		/// メッセージが投稿されれば true, それ以外の場合は false
		/// </returns>
		bool tweet(const String& message);

		/// <summary>
		/// 画像とメッセージを投稿します。
		/// </summary>
		/// <param name="message">
		/// 投稿するメッセージ
		/// </param>
		/// <param name="image">
		/// 投稿する画像
		/// </param>
		/// <returns>
		/// 投稿リクエストが送られれば true, それ以外の場合は false
		/// </returns>
		bool tweetWithMedia(const String& message, const Image& image);

		bool tweetWithMedia(const String& message, const Array<Image>& images);

		/// <summary>
		/// Twitter への接続を切断します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();
	};

	/// <summary>
	/// Twitter
	/// </summary>
	/// <remarks>
	/// Twitter に関する機能を提供します。
	/// </remarks>
	namespace Twitter
	{
		/// <summary>
		/// Twitter への投稿ページをユーザの既定のブラウザで開きます。
		/// </summary>
		/// <param name="text">
		/// 投稿するテキスト
		/// </param>
		/// <returns>
		/// ブラウザを起動できたら true, それ以外の場合は false
		/// </returns>
		bool OpenTweetWindow(const String& text);
	}
}
