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
# include <utility>
# include "Fwd.hpp"

namespace s3d
{
	enum class FillMode : uint8
	{
		Wireframe	= 2,
		Solid		= 3,
	};

	enum class CullMode : uint8
	{
		None		= 1,
		Front		= 2,
		Back		= 3,
	};

	/// <summary>
	/// ラスタライザーステート
	/// </summary>
	struct RasterizerState
	{
		constexpr RasterizerState(
			FillMode _fillMode = FillMode::Solid,
			CullMode _cullMode = CullMode::Back,
			bool _frontCounterClockwise = false,
			bool _scissorEnable = false,
			bool _antialiasedLine3D = false,
			int32 _depthBias = 0
			)
			: fillMode(_fillMode)
			, cullMode(_cullMode)
			, frontCounterClockwise(_frontCounterClockwise)
			, scissorEnable(_scissorEnable)
			, antialiasedLine3D(_antialiasedLine3D)
			, depthBias(_depthBias) {}

		using DataType = uint64;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// 面の塗りつぶし方法
				/// </summary>
				FillMode fillMode : 2;

				/// <summary>
				/// カリングの基準
				/// </summary>
				CullMode cullMode : 2;

				/// <summary>
				/// 頂点が反時計回りの面を表面とするかどうかを示します。 
				/// </summary>
				bool frontCounterClockwise : 1;

				/// <summary>
				/// 頂点が反時計回りの面を表面とするかどうかを示します。 
				/// </summary>
				bool scissorEnable : 1;

				/// <summary>
				/// アンリエイリアスされた Line3D 描画
				/// </summary>
				bool antialiasedLine3D : 2;

				/// <summary>
				/// デプスのバイアス
				/// </summary>
				int32 depthBias;
			};

			DataType _data;
		};
#pragma warning(default:4201)

		bool operator == (const RasterizerState& r) const
		{
			return _data == r._data;
		}

		bool operator != (const RasterizerState& r) const
		{
			return _data != r._data;
		}

		enum class Predefined
		{
			SolidCullBack,
			SolidCullFront,
			SolidCullNone,
			WireframeCullBack,
			WireframeCullFront,
			WireframeCullNone,
			AntialiasedLine3D,
			Default2D = SolidCullNone,
			Default3D = SolidCullBack,
		};

		RasterizerState(Predefined predefined)
		{
			static constexpr RasterizerState predefinedStates[7] =
			{
				{ FillMode::Solid,		CullMode::Back	},	// SolidCullBack
				{ FillMode::Solid,		CullMode::Front	},	// SolidCullFront
				{ FillMode::Solid,		CullMode::None	},	// SolidCullNone
				{ FillMode::Wireframe,	CullMode::Back	},	// WireframeCullBack
				{ FillMode::Wireframe,	CullMode::Front },	// WireframeCullFront
				{ FillMode::Wireframe,	CullMode::None	},	// WireframeCullNone
				{ FillMode::Solid,		CullMode::None, false, false, true }, // AntialiasedLine3D
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		/// <summary>
		/// ソリッド表示、裏向きの面をカリング
		/// RasterizerState{ FillMode::Solid, CullMode::Back }
		/// </summary>
		static constexpr Predefined SolidCullBack = Predefined::SolidCullBack;

		/// <summary>
		/// ソリッド表示、表向きの面をカリング
		/// RasterizerState{ FillMode::Solid, CullMode::Front }
		/// </summary>
		static constexpr Predefined SolidCullFront = Predefined::SolidCullFront;

		/// <summary>
		/// ソリッド表示、カリングなし
		/// RasterizerState{ FillMode::Solid, CullMode::None }
		/// </summary>
		static constexpr Predefined SolidCullNone = Predefined::SolidCullNone;

		/// <summary>
		/// ワイヤフレーム表示、裏向きの面をカリング
		/// RasterizerState{ FillMode::Wireframe, CullMode::Back }
		/// </summary>
		static constexpr Predefined WireframeCullBack = Predefined::WireframeCullBack;

		/// <summary>
		/// ワイヤフレーム表示、表向きの面をカリング
		/// RasterizerState{ FillMode::Wireframe, CullMode::Front }
		/// </summary>
		static constexpr Predefined WireframeCullFront = Predefined::WireframeCullFront;

		/// <summary>
		/// ワイヤフレーム表示、カリングなし
		/// RasterizerState{ FillMode::Wireframe, CullMode::None }
		/// </summary>
		static constexpr Predefined WireframeCullNone = Predefined::WireframeCullNone;

		static constexpr Predefined AntialiasedLine3D = Predefined::AntialiasedLine3D;

		/// <summary>
		/// 2D 描画時のデフォルト
		/// RasterizerState::SolidNone
		/// </summary>
		static constexpr Predefined Default2D = Predefined::Default2D;

		/// <summary>
		/// 3D 描画時のデフォルト
		/// RasterizerState::SolidBack
		/// </summary>
		static constexpr Predefined Default3D = Predefined::Default3D;
	};

	static_assert(sizeof(RasterizerState) == sizeof(RasterizerState::DataType), "");
}

template<>
struct std::hash<s3d::RasterizerState>
{
	size_t operator()(const s3d::RasterizerState& keyVal) const
	{
		return std::hash<s3d::RasterizerState::DataType>()(keyVal._data);
	}
};
