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

namespace s3d
{
	/// <summary>
	/// アライメントを考慮したアロケータ
	/// </summary>
	template <class T, size_t Alignment = alignof(T)>
	struct AlignedAllocator
	{
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;

		template <class U>
		struct rebind
		{
			using other = AlignedAllocator<U>;
		};

		AlignedAllocator() noexcept {}

		AlignedAllocator(const AlignedAllocator&) noexcept {}

		~AlignedAllocator() noexcept {}

		template <class _Other>
		AlignedAllocator(const AlignedAllocator<_Other>&) noexcept {}

		pointer allocate(size_type n, const void* = nullptr)
		{
			assert(n);

			return (pointer) _mm_malloc(n*sizeof(T), Alignment);
		}

		void deallocate(pointer p, size_type)
		{
			assert(p);

			_mm_free(p);
		}

		void construct(pointer p, const_reference t)
		{
			new(p) T(t);
		}

		void destroy(pointer p)
		{
			p;
			
			p->~T();
		}

		pointer address(reference r) const
		{
			return std::addressof(r);
		}

		const_pointer address(const_reference r) const
		{
			return std::addressof(r);
		}

		size_type max_size() const
		{
			return std::numeric_limits<size_t>::max() / sizeof(T);
		}

		bool operator==(const AlignedAllocator&) const
		{
			return true;
		}

		bool operator!=(const AlignedAllocator& other) const
		{
			return false;
		}
	};

	template <class Type, size_t Alignment = alignof(Type)>
	inline Type* AlignedMalloc(size_t N)
	{
		return static_cast<Type*>(::_aligned_malloc(sizeof(Type)*N, Alignment));
	}

	inline void AlignedFree(void* p)
	{
		::_aligned_free(p);
	}
}
