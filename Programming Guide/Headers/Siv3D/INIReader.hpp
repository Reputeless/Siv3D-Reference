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
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// INI ファイルの読み込み
	/// </summary>
	class INIReader
	{
	private:

		class CINIReader;

		std::shared_ptr<CINIReader> pImpl;

		Optional<String> getItem(const String& key) const;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		INIReader();

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit INIReader(const FilePath& path, bool trackFile = true);

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		explicit INIReader(Reader&& reader)
			: INIReader()
		{
			open(std::move(reader));
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		explicit INIReader(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~INIReader();

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, bool trackFile = true);

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::move(reader)));
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// INI ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// INI ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// INI ファイルの内容が変更されたかを返します。
		/// </summary>
		/// <remarks>
		/// ファイルの内容が変更された場合、reload() を呼ぶまで true を返します。
		/// </remarks>
		/// <returns>
		/// INI ファイルの内容が変更された場合 true, それ以外の場合は false
		/// </returns>
		bool hasChanged() const;

		/// <summary>
		/// INI ファイルが変更された場合、データの内容を更新します。
		/// </summary>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool reload();

		/// <summary>
		/// INI ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return isOpened();
		}

		/// <summary>
		/// 指定したキーのデータを取得します。
		/// </summary>
		/// <param name="key">
		/// キー（L"PARAMETER" または L"SECTION.PARAMETER" といった形式）
		/// </param>
		/// <returns>
		/// 指定した位置のデータ。変換に失敗した場合はデフォルトの値
		/// </returns>
		template <class Type>
		Type get(const String& key) const
		{
			if (const auto opt = getOpt<Type>(key))
			{
				return opt.value();
			}

			return Type();
		}

		/// <summary>
		/// 指定したキーのデータを取得します。
		/// </summary>
		/// <param name="key">
		/// キー（L"PARAMETER" または L"SECTION.PARAMETER" といった形式）
		/// </param>
		/// <param name="defaultValue">
		/// キーが存在しない、またはデータの変換に失敗したときに返す値
		/// </param>
		/// <returns>
		/// 指定したキーのデータ。変換に失敗した場合は defaultValue
		/// </returns>
		template <class Type>
		Type getOr(const String& key, Type&& defaultValue) const
		{
			return getOpt<Type>(key).value_or(std::move(defaultValue));
		}

		/// <summary>
		/// 指定したキーのデータを取得します。
		/// </summary>
		/// <param name="key">
		/// キー（L"PARAMETER" または L"SECTION.PARAMETER" といった形式）
		/// </param>
		/// <returns>
		/// 指定したキーのデータの Optional 型。キーが存在しない、またはデータの変換に失敗した場合は none
		/// </returns>
		template <class Type>
		Optional<Type> getOpt(const String& key) const
		{
			if (const auto item = getItem(key))
			{
				return ParseOpt<Type>(item.value());
			}

			return none;
		}

		/// <summary>
		/// INI データが空かどうかを返します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// INI ファイルのパスを返します。
		/// </summary>
		FilePath path() const;
	};
}
