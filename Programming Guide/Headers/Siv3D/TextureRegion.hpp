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
# include "Texture.hpp"
# include "FloatShape.hpp"

namespace s3d
{
	struct TextureRegion
	{
		TextureRegion() = default;

		TextureRegion(const Texture& _texture)
			: texture(_texture)
			, uvRect(0.0f, 0.0f, 1.0f, 1.0f)
			, size(_texture.size) {}

		TextureRegion(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			double sx,
			double sy
			)
			: texture(_texture)
			, uvRect(l, t, r, b)
			, size(sx, sy) {}

		TextureRegion(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Vec2& _size
			)
			: texture(_texture)
			, uvRect(l, t, r, b)
			, size(_size) {}

		TextureRegion(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Vec2& _size
			)
			: texture(_texture)
			, uvRect(_uvRect)
			, size(_size) {}

		Texture texture;

		FloatRect uvRect;

		Vec2 size;

		/// <summary>
		/// テクスチャを描きます。
		/// </summary>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF draw(const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 描画開始位置の X 座標
		/// </param>
		/// <param name="y">
		/// 描画開始位置の Y 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF draw(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 描画開始位置
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="y">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 中心位置の座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const;

		const TextureRegion mirror() const;

		const TextureRegion flip() const;

		const TextureRegion scale(double scaling) const;

		const TextureRegion scale(double xScaling, double yScaling) const;

		const TextureRegion scale(const Vec2& scaling) const;

		const TextureRegion resize(double width, double height) const;

		const TextureRegion resize(const Vec2& _size) const;

		const TexturedQuad rotate(double radian) const;

		const TexturedQuad rotateAt(double x, double y, double radian) const;

		const TexturedQuad rotateAt(const Vec2& pos, double radian) const;
	};
}
