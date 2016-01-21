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
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// フォグ
	/// </summary>
	struct Fog
	{
		/// <summary>
		/// フォグの色
		/// </summary>
		ColorF color = ColorF(0.0);

		/// <summary>
		/// 内部で使用するパラメータ
		/// </summary>
		Vec4 param = { 0, 0, 0, 0 };
		
		/// <summary>
		/// フォグの種類
		/// </summary>
		enum class Type
		{
			/// <summary>
			/// フォグ無し
			/// </summary>
			None,

			/// <summary>
			/// 線形フォグ
			/// </summary>
			Linear,

			/// <summary>
			/// 指数フォグ
			/// </summary>
			Exponential,

			/// <summary>
			/// 平方指数フォグ
			/// </summary>
			SquaredExponential,

			/// <summary>
			/// 高さフォグ
			/// </summary>
			Height,

		} type = Type::None;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr Fog() = default;

		constexpr Fog(const ColorF& _color, const Vec4& _param, Type _type)
			: color(_color)
			, param(_param)
			, type(_type) {}

		/// <summary>
		/// フォグをオフにします。
		/// </summary>
		/// <returns>
		/// フォグ無し
		/// </returns>
		static constexpr Fog None()
		{
			return Fog();
		}

		/// <summary>
		/// 線形フォグを作成します。
		/// </summary>
		/// <param name="_color">
		/// フォグの色
		/// </param>
		/// <param name="begin">
		/// フォグがかかりはじめる距離
		/// </param>
		/// <param name="end">
		/// 完全にフォグがかかる距離
		/// </param>
		/// <returns>
		/// 線形フォグ
		/// </returns>
		static Fog Linear(const ColorF& _color, double begin, double end)
		{
			const double invDistance = 1.0 / (end - begin);

			const double invDistanceMulEnd = invDistance * end;

			return Fog(_color, { invDistanceMulEnd, invDistance, 0.0, 0.0 }, Type::Linear);
		}

		/// <summary>
		/// 指数フォグを作成します。
		/// </summary>
		/// <param name="_color">
		/// フォグの色
		/// </param>
		/// <param name="density">
		/// フォグの濃度
		/// </param>
		/// <returns>
		/// 指数フォグ
		/// </returns>
		static constexpr Fog Exponential(const ColorF& _color, double density)
		{
			return Fog(_color, { density, 0.0, 0.0, 0.0 }, Type::Exponential);
		}

		/// <summary>
		/// 平方指数フォグを作成します。
		/// </summary>
		/// <param name="_color">
		/// フォグの色
		/// </param>
		/// <param name="density">
		/// フォグの濃度
		/// </param>
		/// <returns>
		/// 平方指数フォグ
		/// </returns>
		static constexpr Fog SquaredExponential(const ColorF& _color, double density)
		{
			return Fog(_color, { density, 0.0, 0.0, 0.0 }, Type::SquaredExponential);
		}

		/// <summary>
		/// 高さフォグを作成します。
		/// </summary>
		/// <param name="_color">
		/// フォグの色
		/// </param>
		/// <param name="density">
		/// フォグの濃度
		/// </param>
		/// <param name="intensity">
		/// フォグのスケール
		/// </param>
		/// <returns>
		/// 高さフォグ
		/// </returns>
		static constexpr Fog Height(const ColorF& _color, double density, double intensity)
		{
			return Fog(_color, { density, intensity, 0.0, 0.0 }, Type::Height);
		}
	};
}
