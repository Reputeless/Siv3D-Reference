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
# include <DirectXPackedVector.h>

namespace s3d
{ 
	/// <summary>
	/// 半精度浮動小数点数
	/// </summary>
	struct HalfFloat
	{
		uint16 m_value;

		HalfFloat() = default;

		HalfFloat(float value)
		{
			set(value);
		}

		template <class Type> HalfFloat(Type value)
			: HalfFloat(static_cast<float>(value)) {}

		float get() const
		{
			return DirectX::PackedVector::XMConvertHalfToFloat(m_value);
		}

		void set(float value)
		{
			m_value = DirectX::PackedVector::XMConvertFloatToHalf(value);
		}

		template <class Type>
		void set(Type value)
		{
			set(static_cast<float>(value));
		}

		operator float() const
		{
			return get();
		}
	};
}
