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
# include "Optional.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// ダウンロードの進行状況
	/// </summary>
	enum class DownloadStatus
	{
		/// <summary>
		/// ダウンロードするものが無い
		/// </summary>
		None,

		/// <summary>
		/// ダウンロード中
		/// </summary>
		Working,

		/// <summary>
		/// ダウンロード失敗
		/// </summary>
		Failed,

		/// <summary>
		/// ダウンロードがキャンセルされた
		/// </summary>
		Canceled,

		/// <summary>
		/// ダウンロード完了
		/// </summary>
		Succeeded,
	};

	/// <summary>
	/// ファイルのダウンロード状況
	/// </summary>
	struct DownloadProgress
	{
		/// <summary>
		/// ダウンロード済みのサイズ（バイト）
		/// </summary>
		size_t readSize = 0;

		/// <summary>
		/// ファイルのサイズの Optional. 不明の場合 none
		/// </summary>
		Optional<int64> fileSize;

		/// <summary>
		/// ダウンロードの進行状況
		/// </summary>
		DownloadStatus status = DownloadStatus::None;

		/// <summary>
		/// ダウンロードしているファイルの URL
		/// </summary>
		URL url;

		Optional<double> getProgress() const
		{
			if (!fileSize)
			{
				return none;
			}

			return static_cast<double>(readSize) / fileSize.value();
		}
	};


	class HTTPClient
	{
	private:

		class CHTTPClient;

		std::shared_ptr<CHTTPClient> pImpl;

	public:

		HTTPClient();

		/// <summary>
		/// 指定した URL のファイルをダウンロードします。
		/// </summary>
		/// <param name="url">
		/// ダウンロードするファイルの URL
		/// </param>
		/// <param name="savePath">
		/// ダウンロードしたファイルの保存パス
		/// </param>
		/// <remarks>
		/// ダウンロードが完了するか失敗するまでこの関数は制御を返しません。
		/// </remarks>
		/// <returns>
		/// ダウンロードが完了したら true, それ以外の場合は false
		/// </returns>
		bool download(const URL& url, const FilePath& savePath);

		bool download(const URL& url, ByteArray& dst);

		/// <summary>
		/// 指定した URL のファイルの非同期ダウンロードを開始します。
		/// </summary>
		/// <param name="url">
		/// ダウンロードするファイルの URL
		/// </param>
		/// <param name="savePath">
		/// ダウンロードしたファイルの保存パス
		/// </param>
		/// <returns>
		/// ダウンロード開始に成功した場合 true, 失敗した場合 false
		/// </returns>
		bool downloadAsync(const URL& url, const FilePath& savePath);

		bool downloadAsync(const URL& url, ByteArray& dst);

		/// <summary>
		/// 非同期ダウンロードを中止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void cannelDownload();

		/// <summary>
		/// 非同期ダウンロードの進行状況を取得します。
		/// </summary>
		/// <returns>
		/// 非同期ダウンロードの進行状況
		/// </returns>
		DownloadProgress retreiveProgress();

		bool wait();


		bool requestGET(const URL& url, const String& header, void* content, size_t contentLength, const String& contentType);

		bool requestGET(const URL& url, const FilePath& savePath, const String& header, void* content, size_t contentLength, const String& contentType);

		bool requestGET(const URL& url, ByteArray& dst, const String& header, void* content, size_t contentLength, const String& contentType);


		bool requestPOST(const URL& url, const String& header, void* content, size_t contentLength, const String& contentType);

		bool requestPOST(const URL& url, const FilePath& savePath, const String& header, void* content, size_t contentLength, const String& contentType);

		bool requestPOST(const URL& url, ByteArray& dst, const String& header, void* content, size_t contentLength, const String& contentType);
	};
}
