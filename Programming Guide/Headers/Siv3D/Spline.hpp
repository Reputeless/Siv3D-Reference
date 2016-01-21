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

namespace s3d
{
	/// <summary>
	/// スプライン
	/// </summary>
	namespace Spline
	{
		template <class Type>
		inline constexpr Type CalculateTangent(const Type& p0, const Type& p1, const Type& p2, const double a = 0.0, const double b = 0.0)
		{
			return ((1 - a)*(1 + b)) / 2 * (p1 - p0) + ((1 - a)*(1 - b)) / 2 * (p2 - p1);
		}

		template <class Type>
		inline constexpr Type Hermite(const Type& p0, const Type& p1, const Type& m0, const Type& m1, const double t)
		{
			return (2 * (t*t*t) - 3 * (t*t) + 1)*p0 + ((t*t*t) - 2 * (t*t) + t)*m0 + ((t*t*t) - (t*t))*m1 + (-2 * (t*t*t) + 3 * (t*t))*p1;
		}

		template <class Type>
		inline constexpr Type CatmullRom(const Type& p0, const Type& p1, const Type& p2, const Type& p3, const double t)
		{
			return Hermite(p1, p2, CalculateTangent(p0, p1, p2), CalculateTangent(p1, p2, p3), t);
		}
	}
}
