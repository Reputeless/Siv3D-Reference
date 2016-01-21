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
# include "DirectXMathUtility.hpp"

namespace s3d
{
	struct Triangle3D
	{
#pragma warning(disable:4201)
		union
		{
			struct { Vector p0, p1, p2; };
			struct { Vector p[3]; };
		};
#pragma warning(default:4201)

		Triangle3D() = default;

		Triangle3D(const Vector& _p0, const Vector& _p1, const Vector& _p2)
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		Triangle3D(const Vec3& _p0, const Vec3& _p1, const Vec3& _p2)
			: p0(ToVector(_p0, 0.0f))
			, p1(ToVector(_p1, 0.0f))
			, p2(ToVector(_p2, 0.0f)) {}
	};
}
