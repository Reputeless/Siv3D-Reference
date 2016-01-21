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

namespace s3d
{
	namespace Geometry3D
	{
		bool Intersect(const Vec3& a, const Sphere& b);
		bool Intersect(const Vec3& a, const Box& b);

		bool Intersect(const Sphere& a, const Vec3& b);
		bool Intersect(const Sphere& a, const Ray& b);
		bool Intersect(const Sphere& a, const Triangle3D& b);
		bool Intersect(const Sphere& a, const Sphere& b);
		bool Intersect(const Sphere& a, const Box& b);

		bool Intersect(const Box& a, const Vec3& b);
		bool Intersect(const Box& a, const Ray& b);
		bool Intersect(const Box& a, const Triangle3D& b);
		bool Intersect(const Box& a, const Sphere& b);
		bool Intersect(const Box& a, const Box& b);

		bool Intersect(const Ray& a, const Triangle3D& b);
		bool Intersect(const Ray& a, const Plane& b);
		bool Intersect(const Ray& a, const Sphere& b);
		bool Intersect(const Ray& a, const Box& b);
		bool Intersect(const Ray& a, const Disc& b);

		bool Intersect(const Triangle3D& a, const Sphere& b);
		bool Intersect(const Triangle3D& a, const Box& b);
		bool Intersect(const Triangle3D& a, const Ray& b);
		bool Intersect(const Triangle3D& a, const Triangle3D& b);

		bool Intersect(const Plane& a, const Ray& b);
		bool Intersect(const Disc& a, const Ray& b);

		bool Contains(const Sphere& a, const Vec3& b);
		bool Contains(const Sphere& a, const Triangle3D& b);
		bool Contains(const Sphere& a, const Sphere& b);
		bool Contains(const Sphere& a, const Box& b);

		bool Contains(const Box& a, const Vec3& b);
		bool Contains(const Box& a, const Triangle3D& b);
		bool Contains(const Box& a, const Sphere& b);
		bool Contains(const Box& a, const Box& b);
	}
}
