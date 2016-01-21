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
# include <functional>
# include "PointVector.hpp"

namespace s3d
{
	struct KineticTypography
	{
		KineticTypography() = default;

		KineticTypography(const Vec2& _pos, const Vec2& _origin, int32 _textLength, int32 _index, Color _col, wchar _ch)
			: pos(_pos)
			, origin(_origin)
			, textLength(_textLength)
			, index(_index)
			, col(_col)
			, ch(_ch) {}

		Vec2 pos;

		Vec2 origin;

		int32 textLength;

		int32 index;

		Color col;

		wchar ch;
	};

	using KineticTypographyFunction_t = std::function<void(KineticTypography&)>;
}
