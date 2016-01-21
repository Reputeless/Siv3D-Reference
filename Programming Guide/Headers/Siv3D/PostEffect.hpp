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
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// レンダリング結果へのポストエフェクト
	/// </summary>
	namespace PostEffect
	{
		void Register(const PixelShader& ps);

		void SetConstant(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);

		template <class Type>
		inline void SetConstant(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			SetConstant(stage, slot, buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(__m128));
		}

		void Unregister();
	}
}
