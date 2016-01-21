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
	/// 球
	/// </summary>
	struct Sphere
	{
		Quaternion rotation = Quaternion::Identity();

#pragma warning(disable:4201)
		union
		{
			struct { double x, y, z, r; };
			struct { Vec3 center; double r; };
		};
#pragma warning(default:4201)

		Sphere() = default;

		explicit Sphere(double _r, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(0.0)
			, y(0.0)
			, z(0.0)
			, r(_r) {}

		Sphere(double _x, double _y, double _z, double _r, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, r(_r) {}

		Sphere(const Vec3& pos, double _r, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, r(_r) {}


		Sphere& setPos(double _x, double _y, double _z) { return setPos({ _x, _y, _z }); }

		Sphere& setPos(const Vec3& _pos) { center.set(_pos); return *this; }

		Sphere& setSize(double _r) { r = _r; return *this; }

		Sphere& moveBy(double _x, double _y, double _z) { return moveBy({ _x, _y, _z }); }

		Sphere& moveBy(const Vec3& v) { center.moveBy(v); return *this; }


		Sphere movedBy(double _x, double _y, double _z) const { return movedBy({ _x, _y, _z }); }

		Sphere movedBy(const Vec3& v) const { return{ center.movedBy(v), r, rotation }; }

		Sphere stretched(double s) const { return{ center, r + s, rotation }; }

		Sphere scaled(double s) const { return{ center, r * s, rotation }; }

		Sphere rollPitchYaw(double roll, double pitch, double yaw) const { return{ center, r, rotation.rollPitchYaw(roll, pitch, yaw) }; }

		Sphere rollPitchYaw(const Quaternion& _rotation) const { return{ center, r, rotation * _rotation }; }

		Mat4x4 XM_CALLCONV getMatrix() const { return Mat4x4::AffineTransform(r, rotation, center); }

		TransformedMesh asMesh() const;

		template <class Primitive>
		bool intersects(const Primitive& primitive) const
		{
			return Geometry3D::Intersect(*this, primitive);
		}

		template <class Primitive>
		bool contains(const Primitive& primitive) const
		{
			return Geometry3D::Contains(*this, primitive);
		}

		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void drawForward(const ColorF& color = Palette::White) const;

		void drawForward(const Texture& texture, const ColorF& color = Palette::White) const;
	};
}