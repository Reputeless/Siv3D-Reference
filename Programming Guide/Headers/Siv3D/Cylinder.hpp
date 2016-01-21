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
# include "Optional.hpp"
# include "PointVector.hpp"
# include "Quaternion.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	/// <summary>
	/// 円柱
	/// </summary>
	struct Cylinder
	{
		Quaternion rotation = Quaternion::Identity();

#pragma warning(disable:4201)
		union
		{
			struct { double x, y, z, r, h; };
			struct { Vec3 center; double r, h; };
		};
#pragma warning(default:4201)

		Cylinder() = default;

		Cylinder(double _r, double _h, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(0.0)
			, y(0.0)
			, z(0.0)
			, r(_r)
			, h(_h) {}

		Cylinder(double _x, double _y, double _z, double _r, double _h, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, r(_r)
			, h(_h) {}

		Cylinder(const Vec3& pos, double _r, double _h, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, r(_r)
			, h(_h) {}

		Cylinder(const Vec3& from, const Vec3& to, double _r);

		Cylinder& setPos(double _x, double _y, double _z) { return setPos({ _x, _y, _z }); }

		Cylinder& setPos(const Vec3& _pos) { center.set(_pos); return *this; }

		Cylinder& setSize(double _r, double _h) { r = _r; h = _h;  return *this; }

		Cylinder& moveBy(double _x, double _y, double _z) { return moveBy({ _x, _y, _z }); }

		Cylinder& moveBy(const Vec3& v) { center.moveBy(v); return *this; }


		Cylinder movedBy(double _x, double _y, double _z) const { return movedBy({ _x, _y, _z }); }

		Cylinder movedBy(const Vec3& v) const { return{ center.movedBy(v), r, h, rotation }; }


		Cylinder rollPitchYaw(double roll, double pitch, double yaw) const { return{ center, r, h, rotation.rollPitchYaw(roll, pitch, yaw) }; }

		Cylinder rollPitchYaw(const Quaternion& _rotation) const { return{ center, r, h, rotation * _rotation }; }

		Mat4x4 XM_CALLCONV getMatrix() const { return Mat4x4::AffineTransform({ r, h, r }, rotation, center); }

		TransformedMesh asMesh() const;


		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;
		
		void drawForward(const ColorF& color = Palette::White) const;

		void drawForward(const Texture& texture, const ColorF& color = Palette::White) const;
	};
}
