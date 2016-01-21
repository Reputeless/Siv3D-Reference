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
	struct TexturedQuad
	{
		TexturedQuad(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Quad& _quad,
			const Vec2& _center
			)
			: texture(_texture)
			, uvRect(l, t, r, b)
			, quad(_quad)
			, center(_center) {}

		TexturedQuad(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Quad& _quad,
			const Vec2& _center
			)
			: texture(_texture)
			, uvRect(_uvRect)
			, quad(_quad)
			, center(_center) {}

		Texture texture;

		FloatRect uvRect;

		Quad quad;

		Vec2 center;

		const Quad& draw(const Color& diffuse = Palette::White) const;

		const Quad draw(double x, double y, const Color& diffuse = Palette::White) const;

		const Quad draw(const Vec2& pos, const Color& diffuse = Palette::White) const;

		const Quad drawAt(const Color& diffuse = Palette::White) const;

		const Quad drawAt(double x, double y, const Color& diffuse = Palette::White) const;

		const Quad drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const;
	};
}
