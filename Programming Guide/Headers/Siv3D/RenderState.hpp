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
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Mat3x2.hpp"
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "DepthStencilState.hpp"
# include "SamplerState.hpp"

namespace s3d
{
	struct RenderState
	{
		RenderState() = default;

		RenderState(
			const Mat3x2& _transform2D,
			const BlendState& _blend,
			const RasterizerState& _rasterizer,
			const DepthStencilState& _depthStencil,
			const Rect& _scissorRect,
			const std::array<SamplerState, SamplerState::MaxSamplerCount>& _samplerVS,
			const std::array<SamplerState, SamplerState::MaxSamplerCount>& _samplerPS,
			uint16 _z,
			uint8 _stencilValue
			)
			: transform2D(_transform2D)
			, blend(_blend)
			, rasterizer(_rasterizer)
			, depthStencil(_depthStencil)
			, scissorRect(_scissorRect)
			, samplerVS(_samplerVS)
			, samplerPS(_samplerPS)
			, z(_z)
			, stencilValue(_stencilValue)
		{

		}

		Mat3x2 transform2D;

		BlendState blend;

		RasterizerState rasterizer;

		DepthStencilState depthStencil;

		Rect scissorRect;

		std::array<SamplerState, SamplerState::MaxSamplerCount> samplerVS;

		std::array<SamplerState, SamplerState::MaxSamplerCount> samplerPS;

		uint16 z;

		uint8 stencilValue;

		enum class Predefined
		{
			Default2D,
			Default3D,
		};

		RenderState(Predefined predefined)
		{
			static const RenderState predefinedStates[2] =
			{
				{ Mat3x2::Identity(), BlendState::Default, RasterizerState::Default2D, DepthStencilState::Default2D, Rect(0),
					{ SamplerState::Default2D, SamplerState::Default2D, SamplerState::Default2D, SamplerState::Default2D },
					{ SamplerState::Default2D, SamplerState::Default2D, SamplerState::Default2D, SamplerState::Default2D },
				0, 0 },
				{ Mat3x2::Identity(), BlendState::Default, RasterizerState::Default3D, DepthStencilState::Default3D, Rect(0),
					{ SamplerState::Default2D, SamplerState::Default2D, SamplerState::Default2D, SamplerState::Default2D },
					{ SamplerState::Default3D, SamplerState::Default3D, SamplerState::Default3D, SamplerState::Default3D },
				0, 0 },
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		static constexpr Predefined Default2D = Predefined::Default2D;

		static constexpr Predefined Default3D = Predefined::Default3D;
	};
}
