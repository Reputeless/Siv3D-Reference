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

namespace s3d
{
	struct Line3D
	{
		Vec3 begin, end;

		Line3D() = default;

		constexpr Line3D(const Vec3& _begin, const Vec3& _end)
			: begin(_begin)
			, end(_end) {}

		Line3D& moveBy(double _x, double _y, double _z) { return moveBy({ _x, _y, _z }); }

		Line3D& moveBy(const Vec3& v) { begin.moveBy(v); end.moveBy(v); return *this; }


		constexpr Line3D movedBy(double _x, double _y, double _z) const { return movedBy({ _x, _y, _z }); }

		constexpr Line3D movedBy(const Vec3& v) const { return{ begin.movedBy(v), end.movedBy(v) }; }

		constexpr Line3D reversed() const { return{ end, begin }; }


		void drawForward(const Color& color = Palette::White) const;

		void drawForward(const Color(&colors)[2]) const;

		double length() const
		{
			return end.distanceFrom(begin);
		}

		constexpr double lengthSq() const
		{
			return end.distanceFromSq(begin);
		}
	};
}
