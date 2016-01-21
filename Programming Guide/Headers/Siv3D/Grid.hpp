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
# include <cassert>
# include "Fwd.hpp"
# include "Point.hpp"
# include "Array.hpp"
# include "Format.hpp"
# include "Utility.hpp"
# include "PropertyMacro.hpp"

namespace s3d
{
	/// <summary>
	/// 可変長二次元配列
	/// </summary>
	template <class Type>
	class Grid
	{
	private:

		using ContainerType				= Array<Type>;
		using value_type				= typename ContainerType::value_type;
		using allocator_type			= typename ContainerType::allocator_type;
		using size_type					= typename ContainerType::size_type;
		using difference_type			= typename ContainerType::difference_type;
		using reference					= typename ContainerType::reference;
		using const_reference			= typename ContainerType::const_reference;
		using iterator					= typename ContainerType::iterator;
		using const_iterator			= typename ContainerType::const_iterator;
		using reverse_iterator			= typename ContainerType::reverse_iterator;
		using const_reverse_iterator	= typename ContainerType::const_reverse_iterator;
		using pointer					= typename ContainerType::pointer;
		using const_pointer				= typename ContainerType::const_pointer;

		ContainerType m_data;

		size_type m_width = 0;

		size_type m_height = 0;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Grid() = default;

		/// <summary>
		/// 幅と高さを指定して二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		Grid(size_type w, size_type h)
			: m_data(w * h, Type())
			, m_width(w)
			, m_height(h) {}

		/// <summary>
		/// 幅と高さを指定して二次元配列を作成します。
		/// </summary>
		/// <param name="size">
		/// 幅(列数)と高さ(行数)
		/// </param>
		Grid(const Size& size)
			: Grid(size.x, size.y) {}

		/// <summary>
		/// 幅と高さと初期値を指定して二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		/// <param name="val">
		/// 初期値
		/// </param>
		Grid(size_type w, size_type h, const Type& val)
			: m_data(w*h, val)
			, m_width(w)
			, m_height(h) {}

		/// <summary>
		/// 幅と高さと初期値を指定して二次元配列を作成します。
		/// </summary>
		/// <param name="size">
		/// 幅(列数)と高さ(行数)
		/// </param>
		/// <param name="val">
		/// 初期値
		/// </param>
		Grid(const Size& size, const Type& val)
			: Grid(size.x, size.y, val) {}

		/// <summary>
		/// 配列から二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		/// <param name="data">
		/// 初期値
		/// </param>
		Grid(size_type w, size_type h, Array<Type>&& data)
			: m_data(std::move(data))
			, m_width(w)
			, m_height(h)
		{
			if (m_data.size() != w * h)
			{
				m_data.resize(w * h);
			}
		}

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		Grid(const Grid& g) = default;

		/// <summary>
		/// ムーブコンストラクタ
		/// </summary>
		Grid(Grid&& g) noexcept
		{
			m_width = g.m_width;

			m_height = g.m_height;

			m_data = std::move(g.m_data);

			g.m_width = g.m_height = 0;
		}

		/// <summary>
		/// Initializer-list から二次元配列を作成します。
		/// </summary>
		/// <param name="set">
		/// Initializer-list
		/// </param>
		Grid(const std::initializer_list<std::initializer_list<Type>>& set)
			: Grid(std::max_element(set.begin(), set.end(),
				[](auto& lhs, auto& rhs) { return lhs.size() < rhs.size(); })->size(), set.size())
		{
			auto dst = begin();

			for (const auto& a : set)
			{
				std::copy(a.begin(), a.end(), dst);
				dst += m_width;
			}
		}

		/// <summary>
		/// アロケータオブジェクトを返します。
		/// </summary>
		/// <returns>
		/// アロケータオブジェクト
		/// </returns>
		allocator_type get_allocator() const noexcept
		{
			return m_data.get_allocator();
		}

		/// <summary>
		/// コピー代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Grid& operator = (const Grid& other) = default;

		/// <summary>
		/// ムーブ代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Grid& operator = (Grid&& other) = default;

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <param name="x">
		/// 位置(列)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		Type& at(size_type y, size_type x)
		{
			if (!inBounds(y, x))
			{
				throw std::out_of_range("Grid::at");
			}

			return m_data[y*m_width + x];
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		Type& at(const Point& pos)
		{
			return at(pos.y, pos.x);
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <param name="x">
		/// 位置(列)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		const Type& at(size_type y, size_type x) const
		{
			if (!inBounds(y, x))
			{
				throw std::out_of_range("Grid::at");
			}

			return m_data[y*m_width + x];
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		const Type& at(const Point& pos) const
		{
			return at(pos.y, pos.x);
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="index">
		/// 位置(行)
		/// </param>
		/// <remarks>
		/// grid[y][x] で指定した要素にアクセスします。
		/// </remarks>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		Type* operator[] (size_t index) { return &m_data[index*m_width]; }

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		Type& operator[] (const Point& pos) { return m_data[pos.y * m_width + pos.x]; }

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="index">
		/// 位置(行)
		/// </param>
		/// <remarks>
		/// grid[y][x] で指定した要素にアクセスします。
		/// </remarks>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		const Type* operator[] (size_t index) const { return &m_data[index*m_width]; }

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		const Type& operator[] (const Point& pos) const { return m_data[pos.y * m_width + pos.x]; }

		/// <summary>
		/// 指定した位置が二次元配列の範囲内かを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <param name="x">
		/// 位置(列)
		/// </param>
		/// <returns>
		/// 二次元配列の範囲内である場合 true, それ以外の場合は false
		/// </returns>
		bool inBounds(int64 y, int64 x) const noexcept
		{
			return (0 <= y) && (y < m_height) && (0 <= x) && (x < m_width);
		}

		/// <summary>
		/// 二次元配列が空であるかを示します。
		/// </summary>
		Property_Get(bool, isEmpty) const noexcept { return m_data.empty(); }

		/// <summary>
		/// 二次元配列の幅(列数)を示します。
		/// </summary>
		Property_Get(size_type, width) const noexcept { return m_width; }

		/// <summary>
		/// 二次元配列の高さ(行数)を示します。
		/// </summary>
		Property_Get(size_type, height) const noexcept { return m_height; }

		/// <summary>
		/// 二次元配列のメモリサイズをバイト単位で返します。
		/// </summary>
		/// <returns>
		/// 二次元配列のメモリサイズ（バイト）
		/// </returns>
		size_t memorySize() const noexcept { return m_data.size() * sizeof(Type); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		iterator begin() noexcept { return m_data.begin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		iterator end() noexcept { return m_data.end(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		const_iterator begin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		const_iterator end() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		reverse_iterator rbegin() noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		reverse_iterator rend() noexcept { return m_data.rend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator rbegin() const noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rend() const noexcept { return m_data.rend(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		const_iterator cbegin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		const_iterator cend() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator crbegin() const noexcept { return m_data.crbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crend() const noexcept { return m_data.crend(); }

		/// <summary>
		/// 二次元配列の不要なメモリを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit() { m_data.shrink_to_fit(); }

		/// <summary>
		/// 要素をすべて消去し、メモリを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release() { clear(); shrink_to_fit(); }

		/// <summary>
		/// 末尾に行を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加される行の要素
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_back_row(const Type& value)
		{
			m_data.insert(m_data.end(), m_width, value);

			++m_height;
		}

		/// <summary>
		/// 末尾の行を削除します。
		/// </summary>
		/// <exception cref="std::out_of_range">
		/// 削除する行が無い場合 throw されます。
		/// </exception>
		/// <returns>
		/// なし
		/// </returns>
		void pop_back_row()
		{
			if (m_height == 0)
			{
				throw std::out_of_range("Grid::pop_row");
			}

			--m_height;

			m_data.resize(m_data.size() - m_width);
		}

		/// <summary>
		/// 指定した位置に行を挿入します。
		/// </summary>
		/// <param name="pos">
		/// 挿入先の位置（行）
		/// </param>
		/// <param name="value">
		/// 追加される行の要素
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void insert_row(size_type pos, const Type& value)
		{
			insert_row(pos, 1, value);
		}

		/// <summary>
		/// 指定した位置に行を挿入します。
		/// </summary>
		/// <param name="pos">
		/// 挿入先の位置（行）
		/// </param>
		/// <param name="count">
		/// 挿入する行数
		/// </param>
		/// <param name="value">
		/// 追加される行の要素
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void insert_row(size_type pos, size_type count, const Type& value)
		{
			m_data.insert(m_data.begin() + m_width * pos, m_width * count, value);

			m_height += count;
		}

		/// <summary>
		/// 指定した位置の行を削除します。
		/// </summary>
		/// <param name="pos">
		/// 削除する行の位置
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void erase_row(size_type pos)
		{
			erase_row(pos, 1);
		}

		/// <summary>
		/// 指定した位置から行を削除します。
		/// </summary>
		/// <param name="pos">
		/// 削除する行の位置
		/// </param>
		/// <param name="count">
		/// 削除する行数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void erase_row(size_type pos, size_type count)
		{
			const auto first = m_data.begin() + m_width * pos;
			const auto last = first + m_width * count;

			m_data.erase(first, last);

			m_height -= count;
		}

		/// <summary>
		/// 二次元配列用のメモリを指定したサイズで確保します。
		/// </summary>
		/// <param name="w">
		/// 確保する幅(列数)
		/// </param>
		/// <param name="h">
		/// 確保する高さ(行数)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reserve(size_type w, size_type h) { m_data.reserve(w*h); }

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="w">
		/// 新しい幅(列数)
		/// </param>
		/// <param name="h">
		/// 新しい高さ(行数)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_type w, size_type h) { resize(w, h, Type()); }

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しい幅(列数)と高さ(行数)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(const Size& size)
		{
			resize(size.x, size.y, Type());
		}

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="w">
		/// 新しい幅(列数)
		/// </param>
		/// <param name="h">
		/// 新しい高さ(行数)
		/// </param>
		/// <param name="val">
		/// 要素を初期化する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_type w, size_type h, const Type& val)
		{
			if (w == m_width && h == m_height)
			{
				return;
			}

			m_width = w;

			m_height = h;

			m_data.assign(w * h, val);
		}

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しい幅(列数)と高さ(行数)
		/// </param>
		/// <param name="val">
		/// 要素を初期化する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(const Size& size, const Type& val)
		{
			resize(size.x, size.y, val);
		}

		/// <summary>
		/// 要素を消去し、空の二次元配列にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear() noexcept
		{
			m_data.clear();

			m_width = m_height = 0;
		}

		/// <summary>
		/// 二次元配列のサイズを返します。
		/// </summary>
		/// <returns>
		/// 幅(列数)と高さ(行数)
		/// </returns>
		Size size() const noexcept { return{ static_cast<int32>(m_width), static_cast<int32>(m_height) }; }

		/// <summary>
		/// 要素の個数を返します。
		/// </summary>
		/// <returns>
		/// 要素の個数
		/// </returns>
		size_t num_elements() const noexcept { return m_data.size(); }

		/// <summary>
		/// 二次元配列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭へのポインタ
		/// </returns>
		pointer data() noexcept { return &m_data[0]; }

		/// <summary>
		/// 二次元配列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭へのポインタ
		/// </returns>
		const_pointer data() const noexcept { return m_data.data(); }

		/// <summary>
		/// Array を返します。
		/// </summary>
		/// <returns>
		/// Array
		/// </returns>
		const ContainerType& getArray() const noexcept { return m_data; }

		/// <summary>
		/// すべての要素に指定した値を代入します。
		/// </summary>
		/// <param name="val">
		/// 代入する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void fill(const Type& val) { std::fill(m_data.begin(), m_data.end(), val); }

		/// <summary>
		/// 二次元配列をスワップします。
		/// </summary>
		/// <param name="other">
		/// スワップする対象
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Grid& other)
			noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value
				  || std::allocator_traits<allocator_type>::is_always_equal::value)
		{
			m_data.swap(other.m_data);
			
			std::swap(m_width, other.m_width);
			
			std::swap(m_height, other.m_height);
		}
	};

	template <class Type>
	inline bool operator == (const Grid<Type>& lhs, const Grid<Type>& rhs)
	{
		return lhs.width == rhs.width
			&& lhs.height == rhs.height
			&& std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Type>
	inline bool operator != (const Grid<Type>& lhs, const Grid<Type>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const Grid<Type>& g)
	{
		formatData.string.push_back(L'{');

		bool b = false;

		for (size_t y = 0; y < g.height; ++y)
		{
			if (std::exchange(b, true))
			{
				formatData.string.push_back(L',');
			}

			Formatter(formatData, g[y], g[y] + g.width);
		}

		formatData.string.push_back(L'}');
	}
}

namespace std
{
	template <class Type>
	inline void swap(s3d::Grid<Type>& lhs, s3d::Grid<Type>& rhs)
		noexcept(noexcept(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}
