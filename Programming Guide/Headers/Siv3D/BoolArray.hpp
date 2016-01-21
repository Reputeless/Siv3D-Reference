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
# include <string>
# include <algorithm>

namespace s3d
{
	/// <summary>
	/// 動的配列 (bool)
	/// </summary>
	class BoolArray
	{
	private:

		std::basic_string<bool> m_array;

	public:

		using boolarray_base	= std::basic_string<bool>;
		using value_type		= boolarray_base::value_type;
		using allocator_type	= boolarray_base::allocator_type;
		using size_type			= boolarray_base::size_type;
		using difference_type	= boolarray_base::difference_type;
		using reference			= boolarray_base::reference;
		using const_reference	= boolarray_base::const_reference;
		using pointer			= boolarray_base::pointer;
		using const_pointer		= boolarray_base::const_pointer;
		using iterator			= boolarray_base::iterator;
		using const_iterator	= boolarray_base::const_iterator;
		using reverse_iterator	= boolarray_base::reverse_iterator;
		using const_reverse_iterator = boolarray_base::const_reverse_iterator;

		BoolArray() = default;

		BoolArray(size_type count, const bool& value)
			: m_array(count, value) {}

		explicit BoolArray(size_type count)
			: m_array(count, false) {}

		template <class InputIt>
		BoolArray(InputIt first, InputIt last)
			: m_array(first, last) {}

		BoolArray(const BoolArray& other)
			: m_array(other.m_array) {}

		BoolArray(BoolArray&& other) noexcept
			: m_array(std::move(other.m_array)) {}

		BoolArray(std::initializer_list<bool> init)
			: m_array(init.begin(), init.end()) {}

		BoolArray& operator = (const BoolArray& other)
		{
			m_array = other.m_array;
			return *this;
		}

		BoolArray& operator = (BoolArray&& other) 
			noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value
				  || std::allocator_traits<allocator_type>::is_always_equal::value)
		{
			m_array = std::move(other.m_array);
			return *this;
		}

		BoolArray& operator = (std::initializer_list<bool> ilist)
		{
			m_array = ilist;
			return *this;
		}

		void assign(size_type count, const bool& value)
		{
			m_array.assign(count, value);
		}

		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{
			m_array.assign(first, last);
		}
	
		void assign(std::initializer_list<bool> ilist)
		{
			m_array.assign(ilist.begin(), ilist.end());
		}

		allocator_type get_allocator() const noexcept
		{
			return m_array.get_allocator();
		}

		reference at(size_type pos)
		{
			return m_array.at(pos);
		}

		const_reference at(size_type pos) const
		{
			return m_array.at(pos);
		}

		reference operator[] (size_type pos)
		{
			return m_array[pos];
		}

		const_reference operator[] (size_type pos) const
		{
			return m_array[pos];
		}

		reference front()
		{
			return m_array.front();
		}

		const_reference front() const
		{
			return m_array.front();
		}

		reference back()
		{
			return m_array.back();
		}

		const_reference back() const
		{
			return m_array.back();
		}

		bool* data() noexcept
		{
			return &m_array[0];
		}

		const bool* data() const noexcept
		{
			return m_array.data();
		}

		iterator begin() noexcept
		{
			return m_array.begin();
		}

		const_iterator begin() const noexcept
		{
			return m_array.begin();
		}

		const_iterator cbegin() const noexcept
		{
			return m_array.cbegin();
		}

		iterator end() noexcept
		{
			return m_array.end();
		}

		const_iterator end() const noexcept
		{
			return m_array.end();
		}

		const_iterator cend() const noexcept
		{
			return m_array.cend();
		}

		reverse_iterator rbegin() noexcept
		{
			return m_array.rbegin();
		}

		const_reverse_iterator rbegin() const noexcept
		{
			return m_array.rbegin();
		}

		const_reverse_iterator crbegin() const noexcept
		{
			return m_array.crbegin();
		}

		reverse_iterator rend() noexcept
		{
			return m_array.rend();
		}

		const_reverse_iterator rend() const noexcept
		{
			return m_array.rend();
		}

		const_reverse_iterator crend() const noexcept
		{
			return m_array.crend();
		}

		bool empty() const
		{
			return m_array.empty();
		}

		size_type size() const noexcept
		{
			return m_array.size();
		}

		size_type max_size() const noexcept
		{
			return m_array.max_size();
		}

		void reserve(size_type new_cap)
		{
			m_array.reserve(new_cap);
		}

		size_type capacity() const noexcept
		{
			return m_array.capacity();
		}

		void shrink_to_fit()
		{
			return m_array.shrink_to_fit();
		}

		void clear() noexcept
		{
			m_array.clear();
		}

		iterator insert(const_iterator pos, const bool& value)
		{
			return m_array.insert(pos, value);
		}

		iterator insert(const_iterator pos, bool&& value)
		{
			return m_array.insert(pos, value);
		}

		iterator insert(const_iterator pos, size_type count, const bool& value)
		{
			return m_array.insert(pos, count, value);
		}

		template <class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last)
		{
			return m_array.insert(pos, first, last);
		}

		iterator insert(const_iterator pos, std::initializer_list<bool> ilist)
		{
			return m_array.insert(pos, ilist);
		}
	
		template <class... Args>
		iterator emplace(const_iterator pos, Args&&... args)
		{
			return m_array.insert(pos, bool(std::forward<Args>(args)));
		}

		iterator erase(const_iterator pos)
		{
			return m_array.erase(pos);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			return m_array.erase(first, last);
		}

		void push_back(const bool& value)
		{
			m_array.push_back(value);
		}

		void push_back(bool&& value)
		{
			m_array.push_back(value);
		}

		template <class... Args>
		void emplace_back(Args&&... args)
		{
			m_array.push_back(bool(std::forward<Args>(args)));
		}

		void pop_back()
		{
			m_array.pop_back();
		}

		void resize(size_type count)
		{
			m_array.resize(count, false);
		}

		void resize(size_type count, const value_type& value)
		{
			m_array.resize(count, value);
		}

		void swap(BoolArray& other)
			noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value
				  || std::allocator_traits<allocator_type>::is_always_equal::value)
		{
			m_array.swap(other.m_array);
		}

		bool all() const
		{
			return std::find(m_array.begin(), m_array.end(), false) == m_array.end();
		}

		bool any() const
		{
			return std::find(m_array.begin(), m_array.end(), true) != m_array.end();
		}

		bool none() const
		{
			return std::find(m_array.begin(), m_array.end(), true) == m_array.end();
		}
	};

	inline bool operator == (const BoolArray& lhs, const BoolArray& rhs)
	{
		return lhs.size() == rhs.size()
			&& std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	inline bool operator != (const BoolArray& lhs, const BoolArray& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator < (const BoolArray& lhs, const BoolArray& rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	inline bool operator <= (const BoolArray& lhs, const BoolArray& rhs)
	{
		return !(rhs < lhs);
	}

	inline bool operator > (const BoolArray& lhs, const BoolArray& rhs)
	{
		return rhs < lhs;
	}

	inline bool operator >= (const BoolArray& lhs, const BoolArray& rhs)
	{
		return !(lhs < rhs);
	}
}

namespace std
{
	inline void swap(s3d::BoolArray& lhs, s3d::BoolArray& rhs)
		noexcept(noexcept(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}
