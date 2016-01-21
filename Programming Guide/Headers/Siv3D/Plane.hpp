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
	/// 平面
	/// </summary>
	struct Plane
	{
		Quaternion rotation = Quaternion::Identity();

#pragma warning(disable:4201)
		union
		{
			struct { double x, y, z, w, h; };
			struct { Vec3 center; Vec2 size; };

		};
#pragma warning(default:4201)

		Plane() = default;

		explicit Plane(double _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(0.0)
			, y(0.0)
			, z(0.0)
			, w(_size)
			, h(_size) {}

		Plane(double _w, double _h, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(0.0)
			, y(0.0)
			, z(0.0)
			, w(_w)
			, h(_h) {}

		Plane(double _x, double _y, double _z, double _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, w(_size)
			, h(_size) {}

		Plane(const Vec3& pos, double _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, w(_size)
			, h(_size) {}

		Plane(double _x, double _y, double _z, double _w, double _h, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, w(_w)
			, h(_h) {}

		Plane(const Vec3& pos, double _w, double _h, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, w(_w)
			, h(_h) {}

		Plane(double _x, double _y, double _z, const Vec2& _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, w(_size.x)
			, h(_size.y) {}

		Plane(const Vec3& pos, const Vec2& _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, w(_size.x)
			, h(_size.y) {}


		Plane& setPos(double _x, double _y, double _z) { return setPos({ _x, _y, _z }); }

		Plane& setPos(const Vec3& _pos) { center.set(_pos); return *this; }

		Plane& setSize(double _size) { return setSize({ _size, _size }); }

		Plane& setSize(double _w, double _h) { return setSize({ _w, _h }); }

		Plane& setSize(const Vec2& _size) { size.set(_size); return *this; }

		Plane& moveBy(double _x, double _y, double _z) { return moveBy({ _x, _y, _z }); }

		Plane& moveBy(const Vec3& v) { center.moveBy(v); return *this; }


		Plane movedBy(double _x, double _y, double _z) const { return movedBy({ _x, _y, _z }); }

		Plane movedBy(const Vec3& v) const { return{ center.movedBy(v), size, rotation }; }

		Plane stretched(double s) const { return stretched(s, s); }

		Plane stretched(double _x, double _y) const { return{ center, size.movedBy(_x, _y), rotation }; }

		Plane scaled(double s) const { return scaled({ s, s }); }

		Plane scaled(double sx, double sy) const { return scaled({ sx, sy }); }

		Plane scaled(const Vec2& s) const { return{ center, size * s, rotation }; }

		Plane rollPitchYaw(double roll, double pitch, double yaw) const { return{ center, size, rotation.rollPitchYaw(roll, pitch, yaw) }; }

		Plane rollPitchYaw(const Quaternion& _rotation) const { return{ center, size, rotation * _rotation }; }

		Mat4x4 XM_CALLCONV getMatrix() const { return Mat4x4::AffineTransform({ w, 1.0, h }, rotation, center); }

		TransformedMesh asMesh() const;

		template <class Primitive>
		bool intersects(const Primitive& primitive) const
		{
			return Geometry3D::Intersect(*this, primitive);
		}

		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void drawForward(const ColorF& color = Palette::White) const;

		void drawForward(const Texture& texture, const ColorF& color = Palette::White) const;
	};
}
