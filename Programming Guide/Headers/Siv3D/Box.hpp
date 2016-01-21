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
	/// 直方体
	/// </summary>
	struct Box
	{
		Quaternion rotation = Quaternion::Identity();

#pragma warning(disable:4201)
		union
		{
			struct { double x, y, z, w, h, d; };
			struct { Vec3 center; Vec3 size; };
		};
#pragma warning(default:4201)

		Box() = default;

		explicit Box(double _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(0.0)
			, y(0.0)
			, z(0.0)
			, w(_size)
			, h(_size)
			, d(_size) {}

		Box(double _x, double _y, double _z, double _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, w(_size)
			, h(_size)
			, d(_size) {}

		Box(const Vec3& pos, double _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, w(_size)
			, h(_size)
			, d(_size) {}

		Box(double _x, double _y, double _z, double _w, double _h, double _d, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, w(_w)
			, h(_h)
			, d(_d) {}

		Box(const Vec3& pos, double _w, double _h, double _d, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, w(_w)
			, h(_h)
			, d(_d) {}

		Box(double _x, double _y, double _z, const Vec3& _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(_x)
			, y(_y)
			, z(_z)
			, w(_size.x)
			, h(_size.y)
			, d(_size.z) {}

		Box(const Vec3& pos, const Vec3& _size, const Quaternion& _rotation = Quaternion::Identity())
			: rotation(_rotation)
			, x(pos.x)
			, y(pos.y)
			, z(pos.z)
			, w(_size.x)
			, h(_size.y)
			, d(_size.z) {}

		Box(const Vec3& from, const Vec3& to, double width);


		Box& setPos(double _x, double _y, double _z) { return setPos({ _x, _y, _z }); }

		Box& setPos(const Vec3& _pos) { center.set(_pos); return *this; }

		Box& setSize(double _size) { return setSize({ _size, _size, _size }); }

		Box& setSize(double _w, double _h, double _d) { return setSize({ _w, _h, _d }); }

		Box& setSize(const Vec3& _size) { size.set(_size); return *this; }

		Box& moveBy(double _x, double _y, double _z) { return moveBy({ _x, _y, _z }); }

		Box& moveBy(const Vec3& v) { center.moveBy(v); return *this; }


		Box movedBy(double _x, double _y, double _z) const { return movedBy({ _x, _y, _z }); }

		Box movedBy(const Vec3& v) const { return{ center.movedBy(v), size, rotation }; }

		Box stretched(double s) const { return stretched(s, s, s); }

		Box stretched(double _x, double _y, double _z) const { return{ center, size.movedBy(_x, _y, _z), rotation }; }

		Box scaled(double s) const { return scaled({ s, s, s }); }

		Box scaled(double sx, double sy, double sz) const { return scaled({ sx, sy, sz }); }

		Box scaled(const Vec3& s) const { return{ center, size * s, rotation }; }

		Box rollPitchYaw(double roll, double pitch, double yaw) const { return{ center, size, rotation.rollPitchYaw(roll, pitch, yaw) }; }

		Box rollPitchYaw(const Quaternion& _rotation) const { return{ center, size, rotation * _rotation }; }

		Mat4x4 XM_CALLCONV getMatrix() const { return Mat4x4::AffineTransform(size, rotation, center); }

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
