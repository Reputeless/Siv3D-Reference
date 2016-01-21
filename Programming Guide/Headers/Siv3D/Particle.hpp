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
# include "Array.hpp"
# include "PointVector.hpp"
# include "DirectXMathUtility.hpp"

namespace s3d
{
	/// <summary>
	/// パーティクル
	/// </summary>
	struct alignas(16) Particle
	{
		Float4 pos;

		Float4 scaling;

		Float4 color;

		Particle() = default;

		constexpr Particle(const Vec3& _pos, double _scaling, const ColorF& _color = ColorF(1.0))
			: pos(_pos, 1.0f)
			, scaling(_scaling, _scaling, 1.0f, 0.0f)
			, color(_color.r, _color.g, _color.b, _color.a) {}

		constexpr Particle(const Vec3& _pos, const Vec2& _scaling, const ColorF& _color = ColorF(1.0))
			: pos(_pos, 1.0f)
			, scaling(_scaling, 1.0f, 0.0f)
			, color(_color.r, _color.g, _color.b, _color.a) {}
	};

	namespace Graphics3D
	{
		/// <summary>
		/// パーティクルを Forward レンダラ―で描画します。
		/// </summary>
		/// <param name="particles">
		/// パーティクル
		/// </param>
		/// <param name="texture">
		/// 使用するテクスチャ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>

		void DrawParticlesForward(const Array<Particle>& particles);

		void DrawParticlesForward(const Array<Particle>& particles, const Texture& texture);

		void DrawParticlesForward(const Array<Particle>& particles, size_t offset, size_t count);

		void DrawParticlesForward(const Array<Particle>& particles, size_t offset, size_t count, const Texture& texture);
	}
}
