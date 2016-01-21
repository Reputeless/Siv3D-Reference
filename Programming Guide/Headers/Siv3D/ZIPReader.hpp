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
	/// Zip 圧縮ファイルの読み込み
	/// </summary>
	class ZIPReader
	{
	private:

		class CZIPReader;

		std::shared_ptr<CZIPReader> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		ZIPReader();

		/// <summary>
		/// Zip ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit ZIPReader(const FilePath& path);

		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		explicit ZIPReader(Reader&& reader)
			: ZIPReader()
		{
			open(std::move(reader));
		}

		explicit ZIPReader(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ZIPReader();

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

		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::move(reader)));
		}

		bool open(const std::shared_ptr<IReader>& reader);


		/// <summary>
		/// Zip ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// Zip ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// Zip ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// アーカイブされたファイル名の一覧を返します。
		/// </summary>
		/// <returns>
		/// アーカイブされたファイル名の一覧
		/// </returns>
		const Array<FilePath>& getContents() const;

		/// <summary>
		/// 圧縮されたファイルをすべて展開します。
		/// </summary>
		/// <param name="outputDirectory">
		/// 出力先のディレクトリ
		/// </param>
		/// <returns>
		/// 展開したファイルの保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool extractAll(const FilePath& outputDirectory = L"") const;

		/// <summary>
		/// 圧縮されたファイルを展開します。
		/// </summary>
		/// <param name="index">
		/// 展開するファイルのインデックス
		/// </param>
		/// <param name="outputDirectory">
		/// 出力先のディレクトリ
		/// </param>
		/// <param name="fileName">
		/// 展開したファイルの保存名
		/// </param>
		/// <returns>
		/// 展開したファイルの保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool extract(uint32 index, const FilePath& outputDirectory = L"", const FilePath& fileName = L"") const;

		/// <summary>
		/// 圧縮されたファイルを展開します。
		/// </summary>
		/// <param name="from">
		/// 展開するファイル名
		/// </param>
		/// <param name="outputDirectory">
		/// 出力先のディレクトリ
		/// </param>
		/// <param name="fileName">
		/// 展開したファイルの保存名
		/// </param>
		/// <returns>
		/// 展開したファイルの保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool extract(const FilePath& from, const FilePath& outputDirectory = L"", const FilePath& fileName = L"") const;

		/// <summary>
		/// 圧縮されたファイルを展開してロードします。
		/// </summary>
		/// <param name="index">
		/// 展開するファイルのインデックス
		/// </param>
		/// <returns>
		/// 展開したファイルの IReader
		/// </returns>
		ByteArray decode(uint32 index) const;

		/// <summary>
		/// 圧縮されたファイルを展開してロードします。
		/// </summary>
		/// <param name="from">
		/// 展開するファイル名
		/// </param>
		/// <returns>
		/// 展開したファイルの IReader
		/// </returns>
		ByteArray decode(const FilePath& from) const;

		/// <summary>
		/// Zip ファイルのパスを示します。
		/// </summary>
		FilePath path() const;
	};
}
