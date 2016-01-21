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
# include "PropertyMacro.hpp"

namespace s3d
{
	/// <summary>
	/// CSV ファイルの読み込み
	/// </summary>
	class CSVReader
	{
	private:

		class CCSVReader;

		std::shared_ptr<CCSVReader> pImpl;

		Optional<String> getItem(size_t row, size_t column) const;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		CSVReader();

		/// <summary>
		/// CSV ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit CSVReader(const FilePath& path);

		/// <summary>
		/// CSV ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		explicit CSVReader(Reader&& reader)
			: CSVReader()
		{
			open(std::move(reader));
		}

		/// <summary>
		/// CSV ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		explicit CSVReader(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~CSVReader();

		/// <summary>
		/// CSV ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path);

		/// <summary>
		/// CSV ファイルを開きます。
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
		/// CSV ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// CSV ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// CSV ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// CSV ファイルの内容が変更されたかを返します。
		/// </summary>
		/// <remarks>
		/// ファイルの内容が変更された場合、reload() を呼ぶまで true を返します。
		/// </remarks>
		/// <returns>
		/// CSV ファイルの内容が変更された場合 true, それ以外の場合は false
		/// </returns>
		bool hasChanged() const;

		/// <summary>
		/// CSV ファイルが変更された場合、データの内容を更新します。
		/// </summary>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool reload();

		/// <summary>
		/// CSV ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 指定した行の列数を返します。
		/// </summary>
		/// <param name="row">
		/// 行
		/// </param>
		/// <returns>
		/// 指定した行の列数
		/// </returns>
		size_t columns(size_t row) const;

		/// <summary>
		/// 指定した位置のデータを取得します。
		/// </summary>
		/// <param name="row">
		/// 行
		/// </param>
		/// <param name="column">
		/// 列
		/// </param>
		/// <returns>
		/// 指定した位置のデータ。変換に失敗した場合はデフォルトの値
		/// </returns>
		template <class Type>
		Type get(size_t row, size_t column) const
		{
			if (const auto opt = getOpt<Type>(row, column))
			{
				return opt.value();
			}

			return Type();
		}

		/// <summary>
		/// 指定した位置のデータを取得します。
		/// </summary>
		/// <param name="row">
		/// 行
		/// </param>
		/// <param name="column">
		/// 列
		/// </param>
		/// <param name="defaultValue">
		/// 変換に失敗したときに返す値
		/// </param>
		/// <returns>
		/// 指定した位置のデータ。変換に失敗した場合は defaultValue
		/// </returns>
		template <class Type>
		Type getOr(size_t row, size_t column, Type&& defaultValue) const
		{
			return getOpt<Type>(row, column).value_or(std::move(defaultValue));
		}

		/// <summary>
		/// 指定した位置のデータを取得します。
		/// </summary>
		/// <param name="row">
		/// 行
		/// </param>
		/// <param name="column">
		/// 列
		/// </param>
		/// <returns>
		/// 指定した位置のデータの Optional 型。変換に失敗した場合は none
		/// </returns>
		template <class Type>
		Optional<Type> getOpt(size_t row, size_t column) const
		{
			if (const auto item = getItem(row, column))
			{
				return ParseOpt<Type>(item.value());
			}

			return none;
		}

		/// <summary>
		/// CSV データが空かどうかを返します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// CSV データの行数を示します。
		/// </summary>
		Property_Get(size_t, rows) const;

		/// <summary>
		/// CSV ファイルのパスを返します。
		/// </summary>
		FilePath path() const;
	};
}
