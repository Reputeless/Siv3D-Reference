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
# include "Optional.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// XML ドキュメントの種類
	/// </summary>
	enum class XMLDocumentType
	{
		/// <summary>
		/// 指定しない
		/// </summary>
		/// <remarks>
		/// 文字列が L".xml" で終わる場合 File, それ以外の場合は Text とみなします。
		/// </remarks>
		Unspecified,

		/// <summary>
		/// XML ファイルのパス
		/// </summary>
		File,

		/// <summary>
		/// XML を記述した文字列
		/// </summary>
		Text,
	};

	/// <summary>
	/// XML ドキュメントの読み込み
	/// </summary>
	class XMLReader
	{
	private:

		class CXMLReader;

		std::shared_ptr<CXMLReader> pImpl;

		friend class s3d::XMLElement;

		struct XMLInternal;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		XMLReader();

		/// <summary>
		/// XML ドキュメントを読み込みます。
		/// </summary>
		/// <param name="document">
		/// XML ドキュメント
		/// </param>
		/// <param name="type">
		/// XML ドキュメントの種類
		/// </param>
		explicit XMLReader(const String& document, XMLDocumentType type = XMLDocumentType::Unspecified);

		/// <summary>
		/// XML ファイルを読み込みます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		explicit XMLReader(Reader&& reader)
			: XMLReader()
		{
			open(std::move(reader));
		}

		/// <summary>
		/// XML ファイルを読み込みます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		explicit XMLReader(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// XML ファイルを読み込みます。
		/// </summary>
		/// <param name="path">
		/// XML ファイルのパス
		/// </param>
		/// <returns>
		/// ファイルの読み込みに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path);

		/// <summary>
		/// XML ファイルを読み込みます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルの読み込みに成功した場合 true, それ以外の場合は false
		/// </returns>
		template <class Reader, class = std::enable_if_t<std::is_base_of<IReader, Reader>::value>>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::move(reader)));
		}

		/// <summary>
		/// XML ドキュメントを読み込みます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ドキュメントの読み込みに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// XML テキストを読み込みます。
		/// </summary>
		/// <param name="text">
		/// XML テキスト
		/// </param>
		/// <returns>
		/// XML の読み込みに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool parse(const String& text);

		/// <summary>
		/// XML を正常に読み込めたかを返します。
		/// </summary>
		/// <returns>
		/// 正常に読み込めた場合 true, それ以外の場合は false
		/// </returns>
		bool isValid() const;

		/// <summary>
		/// XML を正常に読み込めたかを返します。
		/// </summary>
		/// <returns>
		/// 正常に読み込めた場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return isValid();
		}

		/// <summary>
		/// XML のルートノードを取得します。
		/// </summary>
		/// <returns>
		/// XML のルートノード
		/// </returns>
		XMLElement root() const;
	};

	/// <summary>
	/// XML の要素
	/// </summary>
	class XMLElement
	{
	private:

		class CXMLElement;

		std::shared_ptr<CXMLElement> m_element;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		XMLElement();

		/// <summary>
		/// 内部で使用するコンストラクタ
		/// </summary>
		explicit XMLElement(const XMLReader::XMLInternal& xmlInternal);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~XMLElement();

		/// <summary>
		/// 要素が空であるかを示します。
		/// </summary>
		/// <returns>
		/// 要素が空の場合 true, それ以外の場合は false
		/// </returns>
		bool isNull() const;

		/// <summary>
		/// 要素が空であるかを示します。
		/// </summary>
		/// <returns>
		/// 要素が空の場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return !isNull(); }

		/// <summary>
		/// 要素の名前を示します。
		/// </summary>
		String name() const;

		/// <summary>
		/// 要素を示します。
		/// </summary>
		String text() const;

		/// <summary>
		/// 最初の子要素を返します。
		/// </summary>
		/// <returns>
		/// 最初の子要素
		/// </returns>
		XMLElement firstChild() const;

		/// <summary>
		/// 次の兄弟要素を返します。
		/// </summary>
		/// <returns>
		/// 次の兄弟要素
		/// </returns>
		XMLElement nextSibling() const;

		/// <summary>
		/// 親要素を返します。
		/// </summary>
		/// <returns>
		/// 親要素
		/// </returns>
		XMLElement parent() const;

		/// <summary>
		/// 属性と属性値のペアの一覧を返します。
		/// </summary>
		/// <returns>
		/// 属性と属性値のペアの一覧
		/// </returns>
		Array<std::pair<String, String>> attributes() const;

		/// <summary>
		/// 指定した属性の属性値を返します。
		/// </summary>
		/// <returns>
		/// 指定した属性の属性値の Optional, 存在しない場合は none
		/// </returns>
		Optional<String> attribute(const String& name) const;
	};
}
