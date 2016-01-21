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
# include "Color.hpp"

namespace s3d
{
	/// <summary>
	/// テクスチャのフィルタリング手法
	/// </summary>
	enum class TextureFilter : uint8
	{
		/// <summary>
		/// ポイントサンプリング
		/// </summary>
		MinMagMipPoint				= 0,
		
		MinMagPointMipLinear		= 0x1,
		
		MinPointMagLinearMipPoint	= 0x4,
		
		MinPointMagMipLinear		= 0x5,
		
		MinLinearMagMipPoint		= 0x10,
		
		MinLinearMagPointMipLinear	= 0x11,
		
		MinMagLinearMipPoint		= 0x14,

		/// <summary>
		/// リニアサンプリング
		/// </summary>
		MinMagMipLinear				= 0x15,
		
		/// <summary>
		/// 異方性フィルタリング (3D 描画向け)
		/// </summary>
		Anisotropic					= 0x55,   
	};

	/// <summary>
	/// テクスチャアドレスモード
	/// </summary>
	enum class TextureAddressMode : uint8
	{
		/// <summary>
		/// 繰り返し
		/// </summary>
        Wrap		= 1,

		/// <summary>
		/// ミラーで繰り返し
		/// </summary>
        Mirror		= 2,

		/// <summary>
		/// 繰り返しなし
		/// </summary>
        Clamp		= 3,

		/// <summary>
		/// 繰り返しなしで範囲外は境界色
		/// </summary>
		Border		= 4,

		/// <summary>
		/// 1 度だけミラーで繰り返し、その範囲外は境界色
		/// </summary>
        MirrorOnce	= 5
	};

	/// <summary>
	/// サンプラーステート
	/// </summary>
	struct SamplerState
	{
		constexpr SamplerState(
			TextureAddressMode _addressU = TextureAddressMode::Wrap,
			TextureAddressMode _addressV = TextureAddressMode::Wrap,
			TextureAddressMode _addressW = TextureAddressMode::Wrap,
			TextureFilter _filter = TextureFilter::MinMagMipLinear,
			uint8 _maxAnisotropy = 16,
			const Color& _borderColor = Color(0,0)
			)
			: filter(_filter)
			, addressU(_addressU)
			, addressV(_addressV)
			, addressW(_addressW)
			, maxAnisotropy(_maxAnisotropy)
			, borderColor(_borderColor) {}

		constexpr SamplerState(
			TextureAddressMode _address,
			TextureFilter _filter,
			uint8 _maxAnisotropy = 16,
			const Color& _borderColor = Color(0, 0)
			)
			: filter(_filter)
			, addressU(_address)
			, addressV(_address)
			, addressW(_address)
			, maxAnisotropy(_maxAnisotropy)
			, borderColor(_borderColor) {}

		using DataType = uint64;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// U 方向のテクスチャアドレスモード
				/// </summary>
				TextureAddressMode addressU : 4;

				/// <summary>
				/// V 方向のテクスチャアドレスモード
				/// </summary>
				TextureAddressMode addressV : 4;

				/// <summary>
				/// W 方向のテクスチャアドレスモード
				/// </summary>
				TextureAddressMode addressW : 8;

				/// <summary>
				/// テクスチャのフィルタリング手法
				/// </summary>
				TextureFilter filter;
				
				/// <summary>
				/// 異方性フィルタリングの次数
				/// </summary>
				unsigned char maxAnisotropy;

				/// <summary>
				/// TextureAddressMode::Border / TextureAddressMode::MirrorOnce 指定時の境界色
				/// </summary>
				Color borderColor;
			};

			DataType _data;
		};
#pragma warning(default:4201)

		static constexpr uint32 MaxSamplerCount = 8;

		bool operator == (const SamplerState& s) const
		{
			return _data == s._data;
		}

		bool operator != (const SamplerState& s) const
		{
			return _data != s._data;
		}

		enum class Predefined
		{
			WrapPoint,
			WrapLinear,
			WrapAniso,
			MirrorPoint,
			MirrorLinear,
			MirrorAniso,
			ClampPoint,
			ClampLinear,
			ClampAniso,
			Default2D = WrapLinear,
			Default3D = WrapAniso,
		};

		SamplerState(Predefined predefined)
		{
			static constexpr SamplerState predefinedStates[9] =
			{
				{ TextureAddressMode::Wrap,		TextureFilter::MinMagMipPoint	},	// WrapPoint
				{ TextureAddressMode::Wrap,		TextureFilter::MinMagMipLinear	},	// WrapLinear
				{ TextureAddressMode::Wrap,		TextureFilter::Anisotropic		},	// WrapAniso
				{ TextureAddressMode::Mirror,	TextureFilter::MinMagMipPoint	},	// MirrorPoint
				{ TextureAddressMode::Mirror,	TextureFilter::MinMagMipLinear	},	// MirrorLinear
				{ TextureAddressMode::Mirror,	TextureFilter::Anisotropic		},	// MirrorAniso
				{ TextureAddressMode::Clamp,	TextureFilter::MinMagMipPoint	},	// ClampPoint
				{ TextureAddressMode::Clamp,	TextureFilter::MinMagMipLinear	},	// ClampLinear
				{ TextureAddressMode::Clamp,	TextureFilter::Anisotropic		},	// ClampAniso
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined WrapPoint = Predefined::WrapPoint;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined WrapLinear = Predefined::WrapLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined WrapAniso = Predefined::WrapAniso;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined MirrorPoint = Predefined::MirrorPoint;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined MirrorLinear = Predefined::MirrorLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined MirrorAniso = Predefined::MirrorAniso;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined ClampPoint = Predefined::ClampPoint;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined ClampLinear = Predefined::ClampLinear;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined ClampAniso = Predefined::ClampAniso;

		/// <summary>
		/// 2D 描画時のデフォルト
		/// SamplerState::WrapLinear
		/// </summary>
		static constexpr Predefined Default2D = Predefined::Default2D;

		/// <summary>
		/// 3D 描画時のデフォルト
		/// SamplerState::WrapAniso
		/// </summary>
		static constexpr Predefined Default3D = Predefined::Default3D;
	};

	static_assert(sizeof(SamplerState) == sizeof(SamplerState::DataType), "");
}

template<>
struct std::hash<s3d::SamplerState>
{
	size_t operator()(const s3d::SamplerState& keyVal) const
	{
		return std::hash<s3d::SamplerState::DataType>()(keyVal._data);
	}
};
