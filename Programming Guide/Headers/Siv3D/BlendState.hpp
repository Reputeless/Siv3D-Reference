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
	//
	// http://msdn.microsoft.com/ja-jp/library/ee416042%28v=vs.85%29.aspx
	//
	enum class Blend : uint8
	{
		Zero			= 1,
		One				= 2,
		SrcColor		= 3,
		InvSrcColor		= 4,
		SrcAlpha		= 5,
		InvSrcAlpha		= 6,
		DestAlpha		= 7,
		InvDestAlpha	= 8,
		DestColor		= 9,
		InvDestColor	= 10,
		SrcAlphaSat		= 11,
		BlendFactor		= 14,
		InvBlendFactor	= 15,
		Src1Color		= 16,
		InvSrc1Color	= 17,
		Src1Alpha		= 18,
		InvSrc1Alpha	= 19
	};

	//
	// http://msdn.microsoft.com/ja-jp/library/ee416044(v=vs.85).aspx
	//
	enum class BlendOp : uint8
	{
		Add			= 1,
		Subtract	= 2,
		RevSubtract	= 3,
		Min			= 4,
		Max			= 5
	};

	/// <summary>
	/// ブレンドステート
	/// </summary>
	struct BlendState
	{
		constexpr BlendState()
			: enable(false)
			, src(Blend::SrcAlpha)
			, dest(Blend::InvSrcAlpha)
			, op(BlendOp::Add)
			, alphaToCoverageEnable(false)
			, srcAlpha(Blend::One)
			, destAlpha(Blend::Zero)
			, opAlpha(BlendOp::Add) {}

		constexpr BlendState(
			bool _enable,
			Blend _src = Blend::SrcAlpha,
			Blend _dest = Blend::InvSrcAlpha,
			BlendOp _op = BlendOp::Add,
			Blend _srcAlpha = Blend::Zero,
			Blend _destAlpha = Blend::One,
			BlendOp _opAlpha = BlendOp::Add,
			bool _alphaToCoverageEnable = false
			)
			: enable(_enable)
			, src(_src)
			, dest(_dest)
			, op(_op)
			, alphaToCoverageEnable(_alphaToCoverageEnable)
			, srcAlpha(_srcAlpha)
			, destAlpha(_destAlpha)
			, opAlpha(_opAlpha) {}

		using DataType = uint32;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				bool enable : 3;

				Blend src : 5;

				Blend dest : 5;

				BlendOp op : 3;

				bool alphaToCoverageEnable : 3;

				Blend srcAlpha : 5;

				Blend destAlpha : 5;

				BlendOp opAlpha : 3;
			};

			DataType _data;
		};
#pragma warning(default:4201)

		constexpr bool operator == (const BlendState& b) const
		{
			return _data == b._data;
		}

		constexpr bool operator != (const BlendState& b) const
		{
			return _data != b._data;
		}

		enum class Predefined
		{
			NonPremultiplied,
			Opaque,
			Additive,
			Subtractive,
			Multiplicative,
			Multiplicative2X,
			Default = NonPremultiplied,
		};

		BlendState(Predefined predefined)
		{
			static constexpr BlendState predefinedStates[6] =
			{
				{ true	},																	// NonPremultiplied
				{ false },																	// Opaque
				{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::Add			},	// Additive
				{ true, Blend::SrcAlpha,	Blend::One,			BlendOp::RevSubtract	},	// Subtractive
				{ true, Blend::Zero,		Blend::SrcColor,	BlendOp::Add			},	// Multiplicative
				{ true, Blend::DestColor,	Blend::SrcColor,	BlendOp::Add			},	// Multiplicative2X
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		/// <summary>
		/// デフォルトのブレンド
		/// BlendState{ true }
		/// </summary>
		static constexpr Predefined NonPremultiplied = Predefined::NonPremultiplied;

		/// <summary>
		/// 不透明
		/// BlendState{ false }
		/// </summary>
		static constexpr Predefined Opaque = Predefined::Opaque;

		/// <summary>
		/// 加算ブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Additive = Predefined::Additive;

		/// <summary>
		/// 減算ブレンド
		/// BlendState{ true, Blend::SrcAlpha, Blend::One, BlendOp::RevSubtract }
		/// </summary>
		static constexpr Predefined Subtractive = Predefined::Subtractive;

		/// <summary>
		/// 乗算ブレンド
		/// BlendState{ true, Blend::Zero, Blend::SrcColor, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Multiplicative = Predefined::Multiplicative;

		/// <summary>
		/// 2X 乗算ブレンド
		/// BlendState{ true, Blend::DestColor, Blend::SrcColor, BlendOp::Add }
		/// </summary>
		static constexpr Predefined Multiplicative2X = Predefined::Multiplicative2X;

		/// <summary>
		/// デフォルトのブレンド
		/// BlendState{ true }
		/// </summary>
		static constexpr Predefined Default = Predefined::Default;
	};

	static_assert(sizeof(BlendState) == sizeof(BlendState::DataType), "");
}

template<>
struct std::hash<s3d::BlendState>
{
	size_t operator()(const s3d::BlendState& keyVal) const
	{
		return std::hash<s3d::BlendState::DataType>()(keyVal._data);
	}
};
