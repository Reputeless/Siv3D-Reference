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
# include "Quad.hpp"

namespace s3d
{
	struct FloatRect
	{
		float left, top, right, bottom;

		FloatRect() = default;

		constexpr FloatRect(float l, float t, float r, float b)
			: left(l)
			, top(t)
			, right(r)
			, bottom(b) {}

		constexpr FloatRect(int32 l, int32 t, int32 r, int32 b)
			: left(static_cast<float>(l))
			, top(static_cast<float>(t))
			, right(static_cast<float>(r))
			, bottom(static_cast<float>(b)) {}

		constexpr FloatRect(double l, double t, double r, double b)
			: left(static_cast<float>(l))
			, top(static_cast<float>(t))
			, right(static_cast<float>(r))
			, bottom(static_cast<float>(b)) {}
	};

	struct FloatQuad
	{
		Float2 tl, tr, br, bl;

		FloatQuad() = default;

		constexpr FloatQuad(const Vec2& _tl, const Vec2& _tr, const Vec2& _br, const Vec2& _bl)
			: tl(_tl)
			, tr(_tr)
			, br(_br)
			, bl(_bl) {}

		constexpr FloatQuad(const Quad& q)
			: tl(q.tl)
			, tr(q.tr)
			, br(q.br)
			, bl(q.bl) {}
	};
}
