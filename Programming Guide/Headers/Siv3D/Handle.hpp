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
# include "Types.hpp"

namespace s3d
{
	enum { NullHandleID = 0 };

	using HandleIDType = uint32;

	template <class Type>
	struct Siv3DHandle
	{
	private:

		HandleIDType m_id = NullHandleID;

	public:

		Siv3DHandle() = default;

		constexpr Siv3DHandle(HandleIDType id)
			: m_id(id) {}

		~Siv3DHandle();

		constexpr HandleIDType getID() const noexcept
		{
			return m_id;
		}
	};
}
