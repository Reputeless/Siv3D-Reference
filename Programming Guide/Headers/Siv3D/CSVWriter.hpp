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
# include "Format.hpp"
# include "TextWriter.hpp"

namespace s3d
{
	/// <summary>
	/// CSV データの書き出し
	/// </summary>
	class CSVWriter
	{
	private:

		TextWriter m_writer;

		bool m_isHead = true;

		void format()
		{
			return;
		}

		template <class Type, class ... Args>
		inline void format(const Type& record, const Args& ... records)
		{
			write(Format(record));

			return format(records...);
		}

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		CSVWriter() = default;

		/// <summary>
		/// 書き出し用のファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit CSVWriter(const FilePath& path)
			: m_writer(path) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~CSVWriter()
		{
			close();
		}

		/// <summary>
		/// 書き出し用のファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path)
		{
			return m_writer.open(path);
		}

		/// <summary>
		/// CSV データを書き出し、ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close()
		{
			if (!isOpened())
			{
				return;
			}

			if (!m_isHead)
			{
				nextLine();
			}

			m_writer.close();
		}

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const
		{
			return m_writer.isOpened();
		}

		/// <summary>
		/// 書き出し用ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// レコードを書き込みます。
		/// </summary>
		/// <param name="record">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(const String& record)
		{
			if (!std::exchange(m_isHead, false))
			{
				m_writer.write(L',');
			}

			m_writer.write(L'\"');

			m_writer.write(record);

			m_writer.write(L'\"');
		}

		/// <summary>
		/// 複数のレコードを書き込みます。
		/// </summary>
		/// <param name="records">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(const Array<String>& records)
		{
			for (const auto& record : records)
			{
				write(record);
			}
		}

		/// <summary>
		/// 複数のレコードを書き込みます。
		/// </summary>
		/// <param name="records">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class ... Args>
		void write(const Args& ... records)
		{
			format(records...);
		}

		/// <summary>
		/// 複数のレコードを書き込み、改行します。
		/// </summary>
		/// <param name="records">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeRow(const Array<String>& records)
		{
			for (const auto& record : records)
			{
				write(record);
			}

			nextLine();
		}

		/// <summary>
		/// 複数のレコードを書き込み、改行します。
		/// </summary>
		/// <param name="records">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class ... Args>
		void writeRow(const Args& ... records)
		{
			format(records...);

			nextLine();
		}

		/// <summary>
		/// 改行します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void nextLine()
		{
			m_writer.write(L"\r\n");

			m_isHead = true;
		}

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		FilePath path() const
		{
			return m_writer.path();
		}
	};
}
