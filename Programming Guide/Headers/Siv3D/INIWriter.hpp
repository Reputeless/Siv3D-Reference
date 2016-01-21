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
# include <set>
# include <unordered_map>
# include "String.hpp"
# include "Array.hpp"
# include "TextWriter.hpp"

namespace s3d
{
	class INIWriterHelper
	{
	private:

		String& m_ref;

	public:

		explicit INIWriterHelper(String& ref)
			: m_ref(ref) {}

		template <class Type>
		void operator = (const Type& value)
		{
			m_ref = Format(value);
		}
	};

	/// <summary>
	/// INI ファイルの書き出し
	/// </summary>
	class INIWriter
	{
	private:

		std::unordered_map<String, String> m_globalSection;

		std::unordered_map<String, std::unordered_map<String, String>> m_sections;

		TextWriter m_writer;

		bool m_sort = false;

		void flushUnordered()
		{
			for (const auto& name : m_globalSection)
			{
				m_writer.write(name.first);
				m_writer.write(L" = ");
				m_writer.write(name.second);
				m_writer.write(L"\r\n");
			}

			if (!m_globalSection.empty())
			{
				m_writer.write(L"\r\n");
			}

			for (const auto& section : m_sections)
			{
				m_writer.write(L'[');
				m_writer.write(section.first);
				m_writer.write(L"]\r\n");

				for (const auto& name : section.second)
				{
					m_writer.write(name.first);
					m_writer.write(L" = ");
					m_writer.write(name.second);
					m_writer.write(L"\r\n");
				}

				m_writer.write(L"\r\n");
			}
		}

		void flushOrdered()
		{
			{
				int32 index = 0;
				std::set<std::pair<String, int32>> ordered;

				for (const auto& name : m_globalSection)
				{
					ordered.emplace(name.first.lower(), index++);
				}

				int32 currentIndex = 0;
				auto it = m_globalSection.begin();

				for (const auto& order : ordered)
				{
					std::advance(it, order.second - currentIndex);
					currentIndex = order.second;

					m_writer.write(it->first);
					m_writer.write(L" = ");
					m_writer.write(it->second);
					m_writer.write(L"\r\n");
				}
			}

			if (!m_globalSection.empty())
			{
				m_writer.write(L"\r\n");
			}

			int32 sectionIndex = 0;
			std::set<std::pair<String, int32>> orderedSections;

			for (const auto& section : m_sections)
			{
				orderedSections.emplace(section.first.lower(), sectionIndex++);
			}

			int32 currentSectionIndex = 0;
			auto itSection = m_sections.begin();

			for (const auto& orderdSection : orderedSections)
			{
				std::advance(itSection, orderdSection.second - currentSectionIndex);
				currentSectionIndex = orderdSection.second;

				m_writer.write(L'[');
				m_writer.write(itSection->first);
				m_writer.write(L"]\r\n");

				int32 index = 0;
				std::set<std::pair<String, int32>> ordered;

				for (const auto& name : itSection->second)
				{
					ordered.emplace(name.first.lower(), index++);
				}

				int32 currentIndex = 0;
				auto it = itSection->second.begin();

				for (const auto& order : ordered)
				{
					std::advance(it, order.second - currentIndex);
					currentIndex = order.second;

					m_writer.write(it->first);
					m_writer.write(L" = ");
					m_writer.write(it->second);
					m_writer.write(L"\r\n");
				}

				m_writer.write(L"\r\n");
			}
		}

		void flush()
		{
			if (m_sort)
			{
				flushOrdered();
			}
			else
			{
				flushUnordered();
			}

			clear();
		}

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		INIWriter() = default;

		/// <summary>
		/// 書き出し用のファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="sort">
		/// セクションとプロパティをアルファベット順にソートするかのフラグ
		/// </param>
		INIWriter(const FilePath& path, bool sort = false)
			: m_writer(path)
			, m_sort(sort) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~INIWriter()
		{
			close();
		}

		/// <summary>
		/// 書き出し用のファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="sort">
		/// セクションとプロパティをアルファベット順にソートするかのフラグ
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, bool sort = false)
		{
			close();

			m_sort = sort;

			return m_writer.open(path);
		}

		/// <summary>
		/// INI データを書き出し、ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close()
		{
			if (m_writer)
			{
				flush();
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
		/// 書き出したデータをすべて削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear()
		{
			m_globalSection.clear();

			m_sections.clear();
		}

		/// <summary>
		/// プロパティを書き込みます。
		/// </summary>
		/// <param name="name">
		/// 値の名前
		/// </param>
		/// <param name="value">
		/// 値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Type>
		void write(const String& name, const Type& value)
		{
			m_globalSection[name] = Format(value);
		}

		/// <summary>
		/// プロパティを書き込みます。
		/// </summary>
		/// <param name="section">
		/// セクション
		/// </param>
		/// <param name="name">
		/// 値の名前
		/// </param>
		/// <param name="value">
		/// 値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Type>
		void write(const String& section, const String& name, const Type& value)
		{
			m_sections[section][name] = Format(value);
		}

		/// <summary>
		/// プロパティへの参照を返します。
		/// </summary>
		/// <param name="key">
		/// キー（L"PARAMETER" または L"SECTION.PARAMETER" といった形式）
		/// </param>
		/// <returns>
		/// プロパティへの参照
		/// </returns>
		INIWriterHelper operator[] (const String& key)
		{
			const auto sep = key.indexOf(L'.');

			if (sep == String::npos)
			{
				return INIWriterHelper(m_globalSection[key]);
			}

			return INIWriterHelper(m_sections[key.substr(0, sep)][key.substr(sep + 1)]);
		}

		/// <summary>
		/// オープンしているファイルのパスを示します。
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
