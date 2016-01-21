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
# include "ArchivedFileReader.hpp"

namespace s3d
{
	/// <summary>
	/// アーカイブ
	/// </summary>
	/// <remarks>
	/// ファイルアーカイブを作成する機能を提供します。
	/// </remarks>
	namespace Archive
	{
		/// <summary>
		/// ファイルアーカイブを作成します。
		/// </summary>
		/// <param name="from">
		/// アーカイブ化するディレクトリ
		/// </param>
		/// <param name="to">
		/// 保存するアーカイブファイル名
		/// </param>
		/// <returns>
		/// ファイルアーカイブの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Create(const FilePath& from, const FilePath& to);
	}

	/// <summary>
	/// ファイルアーカイブ
	/// </summary>
	class FileArchive
	{
	private:

		class CFileArchive;

		std::shared_ptr<CFileArchive> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		FileArchive();

		/// <summary>
		/// ファイルアーカイブを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit FileArchive(const FilePath& path);

		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		explicit FileArchive(Reader&& reader)
		{
			open(std::move(reader));
		}

		explicit FileArchive(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~FileArchive();

		/// <summary>
		/// ファイルアーカイブを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルアーカイブのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path);

		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::move(reader)));
		}

		bool open(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// ファイルアーカイブがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルアーカイブがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// アーカイブされたファイル名の一覧を返します。
		/// </summary>
		/// <returns>
		/// アーカイブされたファイル名の一覧
		/// </returns>
		Array<FilePath> contents() const;

		/// <summary>
		/// ファイルアーカイブがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルアーカイブがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// アーカイブされたファイルをロードします。
		/// </summary>
		/// <param name="path">
		/// アーカイブされたファイルのパス
		/// </param>
		/// <returns>
		/// アーカイブされたファイルの ArchivedFileReader
		/// </returns>
		ArchivedFileReader load(const FilePath& path);

		ByteArray loadByteArray(const FilePath& path) const;
	};
}
