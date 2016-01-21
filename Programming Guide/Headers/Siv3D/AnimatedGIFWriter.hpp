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

namespace s3d
{
	/// <summary>
	/// GIF アニメーション書き出し
	/// </summary>
	class AnimatedGIFWriter
	{
	private:

		class CAnimatedGIFWriter;

		std::shared_ptr<CAnimatedGIFWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		AnimatedGIFWriter();

		AnimatedGIFWriter(const FilePath& path, int32 width, int32 height, bool dither = true, bool hasAlpha = true);

		AnimatedGIFWriter(const FilePath& path, const Size& size, bool dither = true, bool hasAlpha = true);

		/// <summary>
		/// アニメーション GIF の作成を終了し、保存します。
		/// </summary>
		~AnimatedGIFWriter();

		bool open(const FilePath& path, int32 width, int32 height, bool dither = true, bool hasAlpha = true);

		bool open(const FilePath& path, const Size& size, bool dither = true, bool hasAlpha = true);

		/// <summary>
		/// アニメーション GIF の作成を終了し、保存します。
		/// </summary>
		/// <remarks>
		/// 新しいアニメーション GIF を作成するには、再度 open() する必要があります。
		/// </remarks>
		/// <returns>
		/// アニメーション GIF の保存に成功したら true, 失敗したら false
		/// </returns>
		bool close();

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
		/// <param name="delay">
		/// アニメーションの間隔 [100 分の 1 ミリ秒]
		/// </param>
		/// <remarks>
		/// image は動画と同じサイズでなければいけません。
		/// </remarks>
		/// <returns>
		/// フレームの書き出しに成功したら true, 失敗したら false
		/// </returns>
		bool writeFrame(const Image& image, int32 delay = 6);

		uint32 frameCount() const;

		Size imageSize() const;
	};
}
