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
# include "Parse.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "String.hpp"
# include "Format.hpp"
# include "FileSystem.hpp"
# include "JSONValue.hpp"

namespace s3d
{
	/// <summary>
	/// JSON ファイルの読み込み
	/// </summary>
	class JSONReader
	{
	private:

		class CJSONReader;

		std::shared_ptr<CJSONReader> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		JSONReader();

		/// <summary>
		/// JSON ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit JSONReader(const FilePath& path, const Optional<TextEncoding>& encoding = TextEncoding::UTF8);

		/// <summary>
		/// JSON ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		explicit JSONReader(Reader&& reader, const Optional<TextEncoding>& encoding = TextEncoding::UTF8)
			: JSONReader()
		{
			open(std::move(reader), encoding);
		}

		/// <summary>
		/// JSON ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		explicit JSONReader(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = TextEncoding::UTF8);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~JSONReader();

		/// <summary>
		/// JSON ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, const Optional<TextEncoding>& encoding = TextEncoding::UTF8);

		/// <summary>
		/// JSON ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		bool open(Reader&& reader, const Optional<TextEncoding>& encoding = TextEncoding::UTF8)
		{
			return open(std::make_shared<Reader>(std::move(reader)), encoding);
		}

		/// <summary>
		/// JSON ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = TextEncoding::UTF8);

		/// <summary>
		/// JSON ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// JSON ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// JSON ファイルの内容が変更されたかを返します。
		/// </summary>
		/// <remarks>
		/// ファイルの内容が変更された場合、reload() を呼ぶまで true を返します。
		/// </remarks>
		/// <returns>
		/// CSV ファイルの内容が変更された場合 true, それ以外の場合は false
		/// </returns>
		bool hasChanged() const;

		/// <summary>
		/// JSON ファイルが変更された場合、データの内容を更新します。
		/// </summary>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool reload();

		/// <summary>
		/// JSON ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// ルートの JSON データを返します。
		/// </summary>
		/// <returns>
		/// ルートの JSON データ
		/// </returns>
		const JSONValue& root() const;

		/// <summary>
		/// JSON データを取得します。
		/// </summary>
		/// <param name="str">
		/// キー（L"KEYA" や L"KEYA.KEYB.KEYC" といった形式）
		/// </param>
		/// <returns>
		/// JSON データ
		/// </returns>
		const JSONValue& operator[](const String& str) const;

		/// <summary>
		/// JSON ファイルのパスを示します。
		/// </summary>
		FilePath path() const;
	};
}

namespace std
{
	template<> inline void swap(s3d::JSONValue& x, s3d::JSONValue& y)
	{
		x.swap(y);
	}
}
