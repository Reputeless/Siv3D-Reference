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
# include "PropertyMacro.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 動画の読み込み
	/// </summary>
	class VideoReader
	{
	private:

		class CVideoReader;

		std::shared_ptr<CVideoReader> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		VideoReader();

		/// <summary>
		/// 動画ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <remarks>
		/// 対応形式は AVI のみです。
		/// </remarks>
		explicit VideoReader(const FilePath& path);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~VideoReader();

		/// <summary>
		/// 動画ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <remarks>
		/// 対応形式は AVI のみです。
		/// </remarks>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path);

		/// <summary>
		/// 動画ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		bool close();

		/// <summary>
		/// 動画ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// 動画ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 動画ファイルからフレームを読み込みます。
		/// </summary>
		/// <param name="frame">
		/// フレーム番号
		/// </param>
		/// <param name="image">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool readFrame(uint32 frame, Image& image);

		/// <summary>
		/// 動画のフレーム数を示します。
		/// </summary>
		Property_Get(size_t, num_frames) const;

		/// <summary>
		/// 動画のサイズ（ピクセル）を示します。
		/// </summary>
		Property_Get(Size, size) const;

		/// <summary>
		/// 動画の幅（ピクセル）を示します。
		/// </summary>
		Property_Get(int32, width) const { return size.x; }

		/// <summary>
		/// 動画の高さ（ピクセル）を示します。
		/// </summary>
		Property_Get(int32, height) const { return size.y; }

		/// <summary>
		/// 動画のフレームレートを示します。
		/// </summary>
		double fps() const;

		/// <summary>
		/// 現在の読み込みフレームのタイムスタンプ（秒）を示します。
		/// </summary>
		double posSec() const;
	};
}
