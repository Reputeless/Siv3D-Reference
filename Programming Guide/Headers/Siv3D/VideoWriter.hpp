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
# include "String.hpp"
# include "PointVector.hpp"
# include "Color.hpp"

namespace s3d
{
	enum class VideoFormat
	{
		/// <summary>
		/// Microsoft Video 1 | Quality 40
		/// </summary>
		AVI_MSV1_Low,

		/// <summary>
		/// Microsoft Video 1 | Quality 60
		/// </summary>
		AVI_MSV1_Medium,

		/// <summary>
		/// Microsoft Video 1 | Quality 80
		/// </summary>
		AVI_MSV1_High,

		/// <summary>
		/// Microsoft Video 1 | Quality 100
		/// </summary>
		AVI_MSV1_Ultra,

		/// <summary>
		/// Intel Indeo
		/// </summary>
		AVI_Indeo,

		/// <summary>
		/// Cinepak
		/// </summary>
		AVI_Cinepak,

		/// <summary>
		/// 非圧縮
		/// </summary>
		AVI_Uncompressed,
		
		H264,	// .mp4 .wmv .mov
		
		WMV1,	// .wmv
		
		WMV2,	// .wmv
		
		WMV3,	// .wmv
		
		WVC1,	// .wmv

		/// <summary>
		/// デフォルト [H264]
		/// </summary>
		Default = H264
	};

	/// <summary>
	/// 動画の書き出し
	/// </summary>
	class VideoWriter
	{
	private:

		class CVideoWriter;

		std::shared_ptr<CVideoWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		VideoWriter();

		/// <summary>
		/// 動画を書き込むファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// 作成する動画のファイルパス
		/// </param>
		/// <param name="width">
		/// 動画の幅（ピクセル）
		/// </param>
		/// <param name="height">
		/// 動画の高さ（ピクセル）
		/// </param>
		/// <param name="videoCompression">
		/// AVI の圧縮方式
		/// </param>
		/// <param name="frameTime">
		/// フレームレート。 { a, b } で、 b/a[Hz]
		/// </param>
		VideoWriter(const FilePath& path, int width, int height, VideoFormat format = VideoFormat::Default, int fps = 60)
			: VideoWriter(path, { width, height }, format, { 1, fps }) {}

		VideoWriter(const FilePath& path, int width, int height, VideoFormat format, const std::pair<int, int>& frameTime)
			: VideoWriter(path, { width, height }, format, frameTime) {}

		VideoWriter(const FilePath& path, const Size& size, VideoFormat format = VideoFormat::Default, int fps = 60)
			: VideoWriter(path, size, format, { 1, fps }) {}

		VideoWriter(const FilePath& path, const Size& size, VideoFormat format, const std::pair<int, int>& frameTime);

		/// <summary>
		/// 動画の作成を終了し、保存します。
		/// </summary>
		~VideoWriter();

		/// <summary>
		/// 動画を書き込むファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// 作成する動画のファイルパス
		/// </param>
		/// <param name="width">
		/// 動画の幅（ピクセル）
		/// </param>
		/// <param name="height">
		/// 動画の高さ（ピクセル）
		/// </param>
		/// <param name="videoCompression">
		/// AVI の圧縮方式
		/// </param>
		/// <param name="frameTime">
		/// フレームレート。 { a, b } で、 b/a[Hz]
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>


		bool open(const FilePath& path, int32 width, int32 height, VideoFormat format = VideoFormat::Default, int32 fps = 60)
		{
			return open(path, { width, height }, format, { 1, fps });
		}

		bool open(const FilePath& path, int32 width, int32 height, VideoFormat format, const std::pair<int32, int32>& frameTime)
		{
			return open(path, { width, height }, format, frameTime);
		}

		bool open(const FilePath& path, const Size& size, VideoFormat format = VideoFormat::Default, int32 fps = 60)
		{
			return open(path, size, format, { 1, fps });
		}

		bool open(const FilePath& path, const Size& size, VideoFormat format, const std::pair<int32, int32>& frameTime);

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// フレームを書き出します。
		/// </summary>
		/// <param name="image">
		/// 書き出すフレームの画像
		/// </param>
		/// <remarks>
		/// image は動画と同じサイズでなければいけません。
		/// </remarks>
		/// <returns>
		/// フレームの書き出しに成功したら true, 失敗したら false
		/// </returns>
		bool writeFrame(const Image& image);

		/// <summary>
		/// フレームを書き出します。
		/// </summary>
		/// <param name="image">
		/// 書き出すフレームの画像
		/// </param>
		/// <param name="offset">
		/// 画像の位置のオフセット
		/// </param>
		/// <param name="backgroundColor">
		/// 動画の背景色
		/// </param>
		/// <returns>
		/// フレームの書き出しに成功したら true, 失敗したら false
		/// </returns>
		bool writeFrame(const Image& image, const Point& offset, const Color& backgroundColor = Palette::Black);

		/// <summary>
		/// 動画の作成を終了し、保存します。
		/// </summary>
		/// <remarks>
		/// 新しい動画を作成するには、再度 open() する必要があります。
		/// </remarks>
		/// <returns>
		/// 動画の保存に成功したら true, 失敗したら false
		/// </returns>
		bool close();

		Size size() const;
	};
}
