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
# include <algorithm>
# include <utility>
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// 所有権を持たない文字列の参照
	/// </summary>
	class StringView
	{
	private:

		const wchar* m_ptr = nullptr;

		size_t m_length = 0;

	public:

		using traits_type		= std::char_traits<wchar>;
		using value_type		= wchar;
		using pointer			= const wchar*;
		using const_pointer		= const wchar*;
		using reference			= const wchar&;
		using const_reference	= const wchar&;
		using const_iterator	= pointer;
		using iterator			= const_iterator;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using reverse_iterator	= const_reverse_iterator;
		using size_type			= size_t;
		using difference_type	= ptrdiff_t;

		/// <summary>
		/// 特別な値。用途によって意味が異なります。
		/// </summary>
		static const size_type npos = size_type(-1);

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr StringView() = default;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="str">
		/// 別の StringView
		/// </param>
		constexpr StringView(const StringView& str) = default;

		/// <summary>
		/// 別の StringView を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい StringView
		/// </param>
		StringView& operator = (const StringView& str) = default;

		/// <summary>
		/// 文字列から StringView を作成します。
		/// </summary>
		/// <param name="str">
		/// 文字列
		/// </param>
		StringView(const std::wstring& str) noexcept
			: m_ptr(str.data())
			, m_length(str.length()) {}

		/// <summary>
		/// 文字列から StringView を作成します。
		/// </summary>
		/// <param name="str">
		/// 文字列
		/// </param>
		StringView(const String& str) noexcept
			: m_ptr(str.data())
			, m_length(str.length) {}

		/// <summary>
		/// 文字列から StringView を作成します。
		/// </summary>
		/// <param name="str">
		/// 文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		constexpr StringView(const wchar* str)
			: m_ptr(str)
			, m_length(str ? traits_type::length(str) : 0) {}

		/// <summary>
		/// 文字列から StringView を作成します。
		/// </summary>
		/// <param name="str">
		/// 文字列の先頭ポインタ
		/// </param>
		/// <param name="length">
		/// 文字列の長さ
		/// </param>
		constexpr StringView(const wchar* str, size_type length)
			: m_ptr(str)
			, m_length(str ? length : 0) {}

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		const_iterator begin() const noexcept { return m_ptr; }

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		const_iterator cbegin() const noexcept { return m_ptr; }

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		const_iterator end() const noexcept { return m_ptr + m_length; }

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		const_iterator cend() const noexcept { return m_ptr + m_length; }

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

		/// <summary>
		/// 文字列の長さを返します。
		/// </summary>
		/// <returns>
		/// 文字列の長さ
		/// </returns>
		constexpr size_type size() const noexcept { return m_length; }

		/// <summary>
		/// 文字列の長さを返します。
		/// </summary>
		/// <returns>
		/// 文字列の長さ
		/// </returns>
		constexpr size_type length() const noexcept { return m_length; }

		/// <summary>
		/// メモリ上に確保可能な最大の文字列の長さを返します。
		/// </summary>
		/// <returns>
		/// メモリ上に確保可能な最大の文字列の長さ
		/// </returns>
		constexpr size_type max_size() const noexcept { return m_length; }

		/// <summary>
		/// 空の文字列であるかを返します。
		/// </summary>
		/// <returns>
		/// 空の文字列である場合 true, それ以外の場合は false
		/// </returns>
		constexpr bool empty() const noexcept { return m_length == 0; }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		constexpr const_reference operator[](size_type offset) const { return m_ptr[offset]; }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		const_reference at(size_t offset) const
		{
			if (offset >= m_length)
			{
				throw std::out_of_range("StringView::at");
			}

			return m_ptr[offset];
		}

		/// <summary>
		/// 先頭の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 先頭の文字への参照
		/// </returns>
		constexpr const_reference front() const { return m_ptr[0]; }

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		constexpr const_reference back()  const { return m_ptr[m_length - 1]; }

		/// <summary>
		/// 文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭へのポインタ
		/// </returns>
		constexpr const_pointer data()  const { return m_ptr; }

		/// <summary>
		/// 先頭の文字を削除します。
		/// </summary>
		/// <param name="n">
		/// 削除する文字数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void remove_prefix(size_type n)
		{
			if (n > m_length)
			{
				n = m_length;
			}

			m_ptr += n;
			m_length -= n;
		}

		/// <summary>
		/// 末尾の文字を削除します。
		/// </summary>
		/// <param name="n">
		/// 削除する文字数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void remove_suffix(size_type n)
		{
			if (n > m_length)
			{
				n = m_length;
			}

			m_length -= n;
		}

		/// <summary>
		/// StringView を別の StringView と交換します。
		/// </summary>
		/// <param name="s">
		/// 交換する StringView
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(StringView& str) noexcept
		{
			std::swap(m_length, str.m_length);
			std::swap(m_ptr, str.m_ptr);
		}

		/// <summary>
		/// wstring 型で文字列を返します。
		/// </summary>
		/// <returns>
		/// wstring 型に変換した文字列
		/// </returns>
		explicit operator std::wstring() const
		{
			return std::wstring(m_ptr, m_length);
		}

		/// <summary>
		/// String 型で文字列を返します。
		/// </summary>
		/// <returns>
		/// String 型に変換した文字列
		/// </returns>
		explicit operator String() const
		{
			return String(m_ptr, m_length);
		}

		/// <summary>
		/// 指定したポインタへ文字列をコピーします。
		/// </summary>
		/// <param name="str">
		/// コピー先
		/// </param>
		/// <param name="n">
		/// コピーする文字数
		/// </param>
		/// <param name="pos">
		/// コピー開始位置
		/// </param>
		/// <returns>
		/// 実際にコピーした文字数
		/// </returns>
		size_type copy(wchar* str, size_type n, size_type pos = 0) const
		{
			if (pos > m_length)
			{
				throw std::out_of_range("StringView::copy");
			}

			const size_type rlen = std::min(n, m_length - pos);

			for (auto it = m_ptr + pos, end = it + rlen; it != end;)
			{
				*str++ = *it++;
			}

			return rlen;
		}

		/// <summary>
		/// 指定した範囲の文字列を返します。
		/// </summary>
		/// <param name="offset">
		/// 範囲の開始位置
		/// </param>
		/// <param name="n">
		/// 範囲の長さ。npos の場合は文字列の終端まで
		/// </param>
		/// <exception cref="std::out_of_range">
		/// pos &gt; size() の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した範囲の文字列
		/// </returns>
		StringView substr(size_type pos, size_type n = npos) const
		{
			if (pos > size())
			{
				throw std::out_of_range("StringView::substr");
			}

			if (n == npos || pos + n > size())
			{
				n = size() - pos;
			}

			return StringView(data() + pos, n);
		}

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		int compare(StringView str) const
		{
			const int cmp = traits_type::compare(m_ptr, str.m_ptr, std::min(m_length, str.m_length));

			return cmp != 0 ? cmp : (m_length == str.m_length ? 0 : m_length < str.m_length ? -1 : 1);
		}

		/// <summary>
		/// 指定した文字から始まるかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 指定した文字から始まる場合 true, それ以外の場合は false
		/// </returns>
		bool startsWith(wchar ch) const { return !empty() && ch == front(); }

		/// <summary>
		/// 指定した文字列から始まるかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 指定した文字列から始まる場合 true, それ以外の場合は false
		/// </returns>
		bool startsWith(StringView str) const
		{
			return m_length >= str.m_length && traits_type::compare(m_ptr, str.m_ptr, str.m_length) == 0;
		}

		/// <summary>
		/// 指定した文字で終わるかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 指定した文字で終わる場合 true, それ以外の場合は false
		/// </returns>
		bool endsWith(wchar ch) const { return !empty() && ch == back(); }

		/// <summary>
		/// 指定した文字列で終わるかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 指定した文字列で終わる場合 true, それ以外の場合は false
		/// </returns>
		bool endsWith(StringView str) const
		{
			return m_length >= str.m_length && traits_type::compare(m_ptr + m_length - str.m_length, str.m_ptr, str.m_length) == 0;
		}

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type indexOf(StringView str) const
		{
			const_iterator iter = std::search(cbegin(), cend(), str.cbegin(), str.cend());

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		/// <summary>
		/// 文字を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type indexOf(wchar ch) const noexcept
		{
			const_iterator iter = std::find(cbegin(), cend(), ch);

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type lastIndexOf(StringView str) const
		{
			const_reverse_iterator iter = std::search(crbegin(), crend(), str.crbegin(), str.crend());

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type lastIndexOf(wchar ch) const noexcept
		{
			const_reverse_iterator iter = std::find(crbegin(), crend(), ch);

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		/// <summary>
		/// 文字を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type indexOfAny(wchar ch) const noexcept { return indexOf(ch); }

		/// <summary>
		/// 文字を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type lastIndexOfAny(wchar ch) const noexcept { return lastIndexOf(ch); }

		/// <summary>
		/// 検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type indexOfAny(StringView anyof) const
		{
			const_iterator iter = std::find_first_of(cbegin(), cend(), anyof.cbegin(), anyof.cend());

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type lastIndexOfAny(StringView anyof) const
		{
			const_reverse_iterator iter = std::find_first_of(crbegin(), crend(), anyof.cbegin(), anyof.cend());

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		/// <summary>
		/// 文字を検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type indexNotOfAny(StringView anyof) const
		{
			const_iterator iter = find_not_of(cbegin(), cend(), anyof);

			return (iter == cend()) ? npos : std::distance(cbegin(), iter);
		}

		/// <summary>
		/// 文字を検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type indexNotOf(wchar ch) const noexcept
		{
			for (const_iterator iter = cbegin(); iter != cend(); ++iter)
			{
				if (ch != *iter)
				{
					return std::distance(cbegin(), iter);
				}
			}

			return npos;
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type lastIndexNotOfAny(StringView anyof) const
		{
			const_reverse_iterator iter = find_not_of(crbegin(), crend(), anyof);

			return (iter == crend()) ? npos : reverse_distance(crbegin(), iter);
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_type lastIndexNotOf(wchar ch) const noexcept
		{
			for (const_reverse_iterator iter = crbegin(); iter != crend(); ++iter)
			{
				if (ch != *iter)
				{
					return reverse_distance(crbegin(), iter);
				}
			}

			return npos;
		}

		/// <summary>
		/// 文字列を String 型に変換して返します。
		/// </summary>
		/// <returns>
		/// 文字列の String 型の表現
		/// </returns>
		String to_string() const
		{
			return String(m_ptr, m_length);
		}

	private:

		size_type reverse_distance(const_reverse_iterator first, const_reverse_iterator last) const
		{
			return m_length - 1 - std::distance(first, last);
		}

		template <class Iterator>
		Iterator find_not_of(Iterator first, Iterator last, StringView s) const
		{
			for (; first != last; ++first)
			{
				if (!traits_type::find(s.m_ptr, s.m_length, *first))
				{
					return first;
				}
			}

			return last;
		}
	};

	//  Comparison operators
	//  Equality
	inline bool operator == (StringView x, StringView y)
	{
		if (x.size() != y.size()) return false;
		return x.compare(y) == 0;
	}

	inline bool operator == (StringView x, const String & y)
	{
		return x == StringView(y);
	}

	inline bool operator == (const String & x, StringView y)
	{
		return StringView(x) == y;
	}

	inline bool operator == (StringView x, const wchar* y)
	{
		return x == StringView(y);
	}

	inline bool operator == (const wchar* x, StringView y)
	{
		return StringView(x) == y;
	}

	//  Inequality	
	inline bool operator != (StringView x, StringView y)
	{
		if (x.size() != y.size()) return true;
		return x.compare(y) != 0;
	}

	inline bool operator != (StringView x, const String & y)
	{
		return x != StringView(y);
	}

	inline bool operator != (const String & x, StringView y)
	{
		return StringView(x) != y;
	}

	inline bool operator != (StringView x, const wchar* y)
	{
		return x != StringView(y);
	}

	inline bool operator != (const wchar* x, StringView y)
	{
		return StringView(x) != y;
	}

	//  Less than	
	inline bool operator < (StringView x, StringView y)
	{
		return x.compare(y) < 0;
	}

	inline bool operator < (StringView x, const String & y)
	{
		return x < StringView(y);
	}

	inline bool operator < (const String & x, StringView y)
	{
		return StringView(x) < y;
	}

	inline bool operator < (StringView x, const wchar* y)
	{
		return x < StringView(y);
	}

	inline bool operator < (const wchar* x, StringView y)
	{
		return StringView(x) < y;
	}

	//  Greater than	
	inline bool operator > (StringView x, StringView y)
	{
		return x.compare(y) > 0;
	}

	inline bool operator > (StringView x, const String & y)
	{
		return x > StringView(y);
	}

	inline bool operator > (const String & x, StringView y)
	{
		return StringView(x) > y;
	}

	inline bool operator > (StringView x, const wchar* y)
	{
		return x > StringView(y);
	}

	inline bool operator > (const wchar* x, StringView y)
	{
		return StringView(x) > y;
	}

	//  Less than or equal to	
	inline bool operator <=(StringView x, StringView y)
	{
		return x.compare(y) <= 0;
	}

	inline bool operator <= (StringView x, const String & y)
	{
		return x <= StringView(y);
	}

	inline bool operator <= (const String & x, StringView y)
	{
		return StringView(x) <= y;
	}

	inline bool operator <= (StringView x, const wchar* y)
	{
		return x <= StringView(y);
	}

	inline bool operator <= (const wchar* x, StringView y)
	{
		return StringView(x) <= y;
	}

	//  Greater than or equal to	
	inline bool operator >= (StringView x, StringView y)
	{
		return x.compare(y) >= 0;
	}

	inline bool operator >= (StringView x, const String & y)
	{
		return x >= StringView(y);
	}

	inline bool operator >= (const String & x, StringView y)
	{
		return StringView(x) >= y;
	}

	inline bool operator >= (StringView x, const wchar* y)
	{
		return x >= StringView(y);
	}

	inline bool operator >= (const wchar* x, StringView y)
	{
		return StringView(x) >= y;
	}

	/// <summary>
	/// 出力ストリームに文字列を渡します。
	/// </summary>
	/// <param name="output">
	/// 出力ストリーム
	/// </param>
	/// <param name="str">
	/// 文字列
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	inline std::wostream& operator << (std::wostream& output, const StringView& str)
	{
		return output << str.to_string();
	}
}
