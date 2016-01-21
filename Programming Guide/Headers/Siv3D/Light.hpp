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
# include "Color.hpp"

namespace s3d
{
	/// <summary>
	/// ライト
	/// </summary>
	struct Light
	{
		/// <summary>
		/// ディフューズカラー
		/// </summary>
		ColorF diffuse = { 0.0, 0.0 };

		/// <summary>
		/// 点光源の減衰
		/// </summary>
		Vec3 attenuaion = { 0.0, 0.0, 0.0 };

		/// <summary>
		/// 平行光源の方向
		/// </summary>
		Vec3 direction = { 0.0, 0.0, 0.0 };

		/// <summary>
		/// 点光源の位置
		/// </summary>
		Vec3 position = { 0.0, 0.0, 0.0 };

		/// <summary>
		/// 光源の種類
		/// </summary>
		enum class Type
		{
			/// <summary>
			/// 光源無し
			/// </summary>
			None,

			/// <summary>
			/// 平行光源
			/// </summary>
			Directional,

			/// <summary>
			/// 点光源
			/// </summary>
			Point,

		} type = Type::None;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr Light() = default;

		constexpr Light(
			const ColorF& _diffuse,
			const Vec3& _attenuaion,
			const Vec3& _direction,
			const Vec3& _position,
			Type _type
			)
			: diffuse(_diffuse)
			, attenuaion(_attenuaion)
			, direction(_direction)
			, position(_position)
			, type(_type) {}

		/// <summary>
		/// 光源をオフにします。
		/// </summary>
		/// <returns>
		/// 光源無し
		/// </returns>
		static constexpr Light None()
		{
			return Light();
		}

		/// <summary>
		/// デフォルトの平行光源を作成します。
		/// </summary>
		/// <returns>
		/// デフォルトの平行光源
		/// </returns>
		static constexpr Light Default()
		{
			return Directional({ 0.1, 0.5, -0.9 }, { 1.0, 1.0, 1.0 });
		}

		/// <summary>
		/// 平行光源を作成します。
		/// </summary>
		/// <param name="_direction">
		/// 光源の方向
		/// </param>
		/// <param name="_diffuse">
		/// ライトの色
		/// </param>
		/// <returns>
		/// 平行光源
		/// </returns>
		static constexpr Light Directional(const Vec3& _direction, const ColorF& _diffuse = { 1.0, 1.0, 1.0 })
		{
			return{ _diffuse, { 0.0, 0.0, 0.0 }, _direction, { 0.0, 0.0, 0.0 }, Type::Directional };
		}

		/// <summary>
		/// 点光源を作成します。
		/// </summary>
		/// <param name="_position">
		/// 光源の位置
		/// </param>
		/// <param name="r">
		/// 光源の強さ
		/// </param>
		/// <param name="_diffuse">
		/// ライトの色
		/// </param>
		/// <returns>
		/// 点光源
		/// </returns>
		static constexpr Light Point(const Vec3& _position, double r, const ColorF& _diffuse = { 1.0, 1.0, 1.0 })
		{
			return{ _diffuse, { 1.0, 2.0 / r, 1.0 / (r*r) }, { 0.0, 0.0, 0.0 }, _position, Type::Point };
		}
	};
}
