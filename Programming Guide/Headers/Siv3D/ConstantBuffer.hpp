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
# include "StaticAssertMacro.hpp"

namespace s3d
{
	class ConstantBufferBase
	{
	private:

		class ConstantBufferDetail;

		std::shared_ptr<ConstantBufferDetail> m_detail;

	public:

		ConstantBufferBase();

		bool _internal_init(int32 size);

		bool _internal_update(const void* data, size_t size);

		const ConstantBufferDetail* _detail() const;
	};

	template <class Type>
	class ConstantBuffer
	{
	private:

		static constexpr size_t Size = sizeof(Type);

		s3d_static_assert(Size <= 16 * 4096);

		s3d_static_assert(Size % 16 == 0);

		ConstantBufferBase m_base;

		Type* m_data = static_cast<Type*>(::_aligned_malloc(Size, 16));

	public:

		ConstantBuffer()
		{
			m_base._internal_init(Size);
		}

		explicit ConstantBuffer(const Type& data)
			: ConstantBuffer()
		{
			*m_data = data;
		}

		~ConstantBuffer()
		{
			::_aligned_free(m_data);
		}

		const float* getPtr() const
		{
			return static_cast<const float*>(static_cast<const void*>(m_data));
		}

		Type& get()
		{
			return *m_data;
		}

		const Type& get() const
		{
			return *m_data;
		}

		bool _internal_update()
		{
			return m_base._internal_update(m_data, sizeof(Type));
		}

		bool _internal_update(const Type& data)
		{
			*m_data = data;

			return update();
		}

		const ConstantBufferBase& base() const
		{
			return m_base;
		}

		Type& operator *()
		{
			return *m_data;
		}

		const Type& operator *() const
		{
			return *m_data;
		}

		Type* operator ->()
		{
			return m_data;
		}

		const Type* operator ->() const
		{
			return *m_data;
		}
	};
}
