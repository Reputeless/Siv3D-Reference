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
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// Zip 圧縮ファイルの書き出し
	/// </summary>
	class ZIPWriter
	{
	private:

		class CZIPWriter;

		std::shared_ptr<CZIPWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		ZIPWriter();

		/// <summary>
		/// Zip ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit ZIPWriter(const FilePath& path);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ZIPWriter();

		/// <summary>
		/// Zip ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path);

		bool close();

		bool isOpened() const;

		explicit operator bool() const { return isOpened(); }

		bool addFile(const FilePath& archiveName, const FilePath& src, _Field_range_(1, 9) int32 level = 7);

		bool addFile(const FilePath& archiveName, const ByteArray& data, _Field_range_(1, 9) int32 level = 7);

		bool addFile(const FilePath& archiveName, const void* data, size_t size, _Field_range_(1, 9) int32 level = 7);

		/// <summary>
		/// Zip ファイルのパスを示します。
		/// </summary>
		FilePath path() const;
	};
}
