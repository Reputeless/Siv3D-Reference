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
# include <unordered_map>
# include "Fwd.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// JSON 配列データ
	/// </summary>
	using JSONArray = std::vector<JSONValue>;

	/// <summary>
	/// JSON オブジェクトデータ
	/// </summary>
	using JSONObject = std::unordered_map<String, JSONValue>;

	/// <summary>
	/// JSON データ
	/// </summary>
	class JSONValue
	{
	public:

		enum class ValueType
		{
			Null,
			Boolean,
			Number,
			String,
			Array,
			Object,
		};

		union Storage
		{
			bool boolean_;
			double number_;
			String* string_;
			JSONArray* array_;
			JSONObject* object_;
		};

	protected:

		ValueType m_type = ValueType::Null;

		Storage m_data;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		JSONValue() = default;

		JSONValue(ValueType type, bool);

		explicit JSONValue(bool b);

		explicit JSONValue(double n);

		explicit JSONValue(const String& s);

		explicit JSONValue(const JSONArray& a);

		explicit JSONValue(const JSONObject& o);

		explicit JSONValue(const wchar* s);

		JSONValue(const wchar* s, size_t len);

		template <class T> JSONValue(const T*) = delete;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~JSONValue();

		JSONValue(const JSONValue& x);

		JSONValue& operator=(const JSONValue& x);

		void swap(JSONValue& x);

		/// <summary>
		/// データが null であるかを返します。
		/// </summary>
		/// <returns>
		/// データが null の場合 true, それ以外の場合は false
		/// </returns>
		bool isNull() const
		{
			return m_type == ValueType::Null;
		}

		/// <summary>
		/// データが真偽値であるかを返します。
		/// </summary>
		/// <returns>
		/// データが真偽値である場合 true, それ以外の場合は false
		/// </returns>
		bool isBool() const
		{
			return m_type == ValueType::Boolean;
		}

		/// <summary>
		/// データが文字列であるかを返します。
		/// </summary>
		/// <returns>
		/// データが文字列である場合 true, それ以外の場合は false
		/// </returns>
		bool isString() const
		{
			return m_type == ValueType::String;
		}

		/// <summary>
		/// データが数値であるかを返します。
		/// </summary>
		/// <returns>
		/// データが数値である場合 true, それ以外の場合は false
		/// </returns>
		bool isNumber() const
		{
			return m_type == ValueType::Number;
		}

		/// <summary>
		/// データが配列であるかを返します。
		/// </summary>
		/// <returns>
		/// データが配列である場合 true, それ以外の場合は false
		/// </returns>
		bool isArray() const
		{
			return m_type == ValueType::Array;
		}

		/// <summary>
		/// データがオブジェクトであるかを返します。
		/// </summary>
		/// <returns>
		/// データがオブジェクトである場合 true, それ以外の場合は false
		/// </returns>
		bool isObject() const
		{
			return m_type == ValueType::Object;
		}

		/// <summary>
		/// データの型を返します。
		/// </summary>
		/// <returns>
		/// データの型
		/// </returns>
		ValueType getType() const
		{
			return m_type;
		}

		const JSONValue& operator[](size_t index) const;

		JSONValue& operator[](size_t index);

		const JSONValue& operator[](const String& key) const;

		JSONValue& operator[](const String& key);

		bool& getBool();

		const bool& getBool() const;

		double& getNumber();

		const double& getNumber() const;

		String& getString();

		const String& getString() const;

		JSONArray& getArray();

		const JSONArray& getArray() const;

		JSONObject& getObject();

		const JSONObject& getObject() const;

		template<class Type> typename std::enable_if<!std::is_arithmetic<Type>::value, Type>::type get() const
		{
			return Parse<Type>(getString());
		}

		template<class Type> typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type get() const
		{
			return static_cast<Type>(getNumber());
		}

		template <> String get<String>() const
		{
			return getString();
		}

		template <> bool get<bool>() const
		{
			return getBool();
		}

		///////////////////

		template<class Type> typename std::enable_if<!std::is_arithmetic<Type>::value, Optional<Type>>::type getOpt() const
		{
			if (!isString())
			{
				return none;
			}

			return ParseOpt<Type>(getString());
		}

		template<class Type> typename std::enable_if<std::is_arithmetic<Type>::value, Optional<Type>>::type getOpt() const
		{
			if (!isNumber())
			{
				return none;
			}

			return static_cast<Type>(getNumber());
		}

		template <> Optional<String> getOpt<String>() const
		{
			if (!isString())
			{
				return none;
			}

			return getString();
		}

		template <> Optional<bool> getOpt<bool>() const
		{
			if (!isBool())
			{
				return none;
			}

			return getBool();
		}

		///////////////////

		template<class Type, class U> Type getOr(U&& defaultValue) const
		{
			return getOpt<Type>().value_or(std::forward<U>(defaultValue));
		}

		///////////////////

		bool contains(size_t idx) const
		{
			if (!isArray())
			{
				throw std::runtime_error("!isArray()");
			}

			return idx < m_data.array_->size();
		}

		bool contains(const String& key) const
		{
			if (!isObject())
			{
				throw std::runtime_error("!isObject()");
			}

			return m_data.object_->find(key) != m_data.object_->end();
		}

		String to_str() const;
	};

	bool operator==(const JSONValue& x, const JSONValue& y);

	inline bool operator!=(const JSONValue& x, const JSONValue& y)
	{
		return !(x == y);
	}
}
