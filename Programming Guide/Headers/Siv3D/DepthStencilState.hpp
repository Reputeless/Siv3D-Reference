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
	enum class DepthFunc : uint16
	{
		Never			= 1,
		Less			= 2,
		Equal			= 3,
		LessEqual		= 4,
		Greater			= 5,
		NotEqual		= 6,
		GreaterEqual	= 7,
		Always			= 8
	};

	/// <summary>
	/// デプスステート
	/// </summary>
	struct DepthState
	{
		constexpr DepthState(
			bool _enable = true,
			bool _writeEnable = true,
			DepthFunc _func = DepthFunc::GreaterEqual
			)
			: enable(_enable)
			, writeEnable(_writeEnable)
			, func(_func) {}

		using DataType = uint32;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// デプステストの有無
				/// </summary>
				bool enable;

				/// <summary>
				/// デプスの書き込みの有無
				/// </summary>
				bool writeEnable;

				/// <summary>
				/// デプステストの条件
				/// </summary>
				DepthFunc func;
			};

			DataType _data;
		};
#pragma warning(default:4201)

		bool operator == (const DepthState& d) const
		{
			return _data == d._data;
		}

		bool operator != (const DepthState& d) const
		{
			return _data != d._data;
		}

		enum class Predefined
		{
			None,
			TestOnly,
			WriteOnly,
			TestWrite,
			Default2D = None,
			Default3D = TestWrite,
		};

		DepthState(Predefined predefined)
		{
			static constexpr DepthState predefinedStates[4] =
			{
				{ false,	false,	DepthFunc::Always		},	// None
				{ true,		false,	DepthFunc::GreaterEqual },	// TestOnly
				{ true,		true,	DepthFunc::Always		},	// WriteOnly
				{ true,		true,	DepthFunc::GreaterEqual },	// TestWrite
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		/// <summary>
		/// デプステスト無し・デプスの書き込み無し
		/// 
		/// </summary>
		static constexpr Predefined None = Predefined::None;

		/// <summary>
		/// デプステストあり・デプスの書き込み無し
		/// 
		/// </summary>
		static constexpr Predefined TestOnly = Predefined::TestOnly;

		/// <summary>
		/// デプステスト無し・デプスの書き込みあり
		/// 
		/// </summary>
		static constexpr Predefined WriteOnly = Predefined::WriteOnly;

		/// <summary>
		/// デプステストあり・デプスの書き込みあり
		/// 
		/// </summary>
		static constexpr Predefined TestWrite = Predefined::TestWrite;

		/// <summary>
		/// 2D 描画時のデフォルト
		/// DepthState::None
		/// </summary>
		static constexpr Predefined Default2D = Predefined::Default2D;

		/// <summary>
		/// 3D 描画時のデフォルト
		/// DepthState::TestWrite
		/// </summary>
		static constexpr Predefined Default3D = Predefined::Default3D;
	};

	/// <summary>
	/// ステンシルバッファへの操作
	/// </summary>
	enum class StencilOp : uint8
	{
		/// <summary>
		/// 何もしない
		/// </summary>
		Keep		= 1,

		/// <summary>
		/// 0 にする
		/// </summary>
		Zero		= 2,

		/// <summary>
		/// 現在のステンシル値に置き換える
		/// </summary>
		Replace		= 3,

		/// <summary>
		///	254 以下なら 1 加算する
		/// </summary>
		IncrSat		= 4,

		/// <summary>
		/// 1 以上なら 1 減算する
		/// </summary>
		DecrSat		= 5,

		/// <summary>
		/// ビット反転させる
		/// </summary>
		Invert		= 6,

		/// <summary>
		/// 1 加算する
		/// </summary>
		Incr		= 7,

		/// <summary>
		/// 1 減算する
		/// </summary>
		Decr		= 8
	};

	/// <summary>
	/// ステンシルテストの条件
	/// </summary>
	enum class StencilFunc : uint8
	{
        Never			= 1,
        Less			= 2,
        Equal			= 3,
        LessEqual		= 4,
        Greater			= 5,
        NotEqual		= 6,
        GreaterEqual	= 7,
        Always			= 8
	};

	/// <summary>
	/// ステンシルステート
	/// </summary>
	struct StencilState
	{
		constexpr StencilState(
			bool _enable = false,
			bool _stencilWriteOnly = false,
			StencilFunc _func = StencilFunc::Always,
			StencilOp _passOp = StencilOp::Keep,
			StencilOp _failOp = StencilOp::Keep,
			StencilFunc _backFunc = StencilFunc::Always,
			StencilOp _backPassOp = StencilOp::Keep,
			StencilOp _backFailOp = StencilOp::Keep
			)
			: enable(_enable)
			, stencilWriteOnly(_stencilWriteOnly)
			, func(_func)
			, passOp(_passOp)
			, failOp(_failOp)
			, backFunc(_backFunc)
			, backPassOp(_backPassOp)
			, backFailOp(_backFailOp) {}

		constexpr StencilState(
			StencilFunc _func,
			StencilOp _passOp,
			StencilOp _failOp = StencilOp::Keep
			)
			: enable(true)
			, stencilWriteOnly(false)
			, func(_func)
			, passOp(_passOp)
			, failOp(_failOp)
			, backFunc(_func)
			, backPassOp(_passOp)
			, backFailOp(_failOp) {}

		using DataType = uint32;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// ステンシルテストの有無
				/// </summary>
				bool enable : 4;

				bool stencilWriteOnly : 4;

				StencilFunc func : 4;

				StencilOp passOp : 4;

				StencilOp failOp : 4;

				StencilFunc backFunc : 4;

				StencilOp backPassOp : 4;

				StencilOp backFailOp : 4;
			};

			DataType _data;
		};
#pragma warning(default:4201)

		bool operator == (const StencilState& s) const
		{
			return _data == s._data;
		}

		bool operator != (const StencilState& s) const
		{
			return _data != s._data;
		}

		enum class Predefined
		{
			None,
			Increment,
			Decrement,
			Replace,
			Default = None,
		};

		StencilState(Predefined predefined)
		{
			static const StencilState predefinedStates[4] =
			{
				{ false,	false																														},	// None
				{ true,		true, StencilFunc::Always, StencilOp::Incr,		StencilOp::Keep, StencilFunc::Always, StencilOp::Incr,		StencilOp::Keep	},	// Increment
				{ true,		true, StencilFunc::Always, StencilOp::Decr,		StencilOp::Keep, StencilFunc::Always, StencilOp::Decr,		StencilOp::Keep	},	// Decrement
				{ true,		true, StencilFunc::Always, StencilOp::Replace,	StencilOp::Keep, StencilFunc::Always, StencilOp::Replace,	StencilOp::Keep	},	// Replace
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined None = Predefined::None;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined Increment = Predefined::Increment;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined Decrement = Predefined::Decrement;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined Replace = Predefined::Replace;

		/// <summary>
		/// 
		/// 
		/// </summary>
		static constexpr Predefined Default = Predefined::Default;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_func">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		static constexpr StencilState Test(StencilFunc _func)
		{
			return{ _func, StencilOp::Keep };
		}
	};

	/// <summary>
	/// デプスステンシルステート
	/// </summary>
	struct DepthStencilState
	{
		DepthStencilState(
			const DepthState& _depth = DepthState::Default2D,
			const StencilState& _stencil = StencilState::Default
			)
			: depth(_depth)
			, stencil(_stencil) {}

		using DataType = unsigned __int64;

#pragma warning(disable:4201)
		union
		{
			struct
			{
				DepthState depth;

				StencilState stencil;
			};

			DataType _data;
		};
#pragma warning(default:4201)

		bool operator == (const DepthStencilState& d) const
		{
			return _data == d._data;
		}

		bool operator != (const DepthStencilState& d) const
		{
			return _data != d._data;
		}

		enum class Predefined
		{
			Default2D,
			Default3D,
		};

		DepthStencilState(Predefined predefined)
		{
			static const DepthStencilState predefinedStates[2] =
			{
				{ DepthState::Default2D, StencilState::Default },
				{ DepthState::Default3D, StencilState::Default },
			};

			*this = predefinedStates[static_cast<size_t>(predefined)];
		}

		static constexpr Predefined Default2D = Predefined::Default2D;

		static constexpr Predefined Default3D = Predefined::Default3D;
	};

	static_assert(sizeof(DepthState) == sizeof(DepthState::DataType), "");
	static_assert(sizeof(StencilState) == sizeof(StencilState::DataType), "");
	static_assert(sizeof(DepthStencilState) == sizeof(DepthStencilState::DataType), "");
}

template<>
struct std::hash<s3d::DepthState>
{
	size_t operator()(const s3d::DepthState& keyVal) const
	{
		return std::hash<s3d::DepthState::DataType>()(keyVal._data);
	}
};

template<>
struct std::hash<s3d::StencilState>
{
	size_t operator()(const s3d::StencilState& keyVal) const
	{
		return std::hash<s3d::StencilState::DataType>()(keyVal._data);
	}
};

template<>
struct std::hash<s3d::DepthStencilState>
{
	size_t operator()(const s3d::DepthStencilState& keyVal) const
	{
		return std::hash<s3d::DepthStencilState::DataType>()(keyVal._data);
	}
};
