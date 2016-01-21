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
# include <iostream>
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// レイ
	/// </summary>
	struct Ray
	{
		/// <summary>
		/// レイの始点
		/// </summary>
		Vec3 origin;

		/// <summary>
		/// レイの方向ベクトル
		/// </summary>
		Vec3 direction;

		Ray() = default;

		constexpr Ray(const Vec3& _origin, const Vec3& _direction)
			: origin(_origin)
			, direction(_direction) {}

		template <class Primitive>
		bool intersects(const Primitive& primitive) const
		{
			return Geometry3D::Intersect(*this, primitive);
		}

		bool test(const Sphere& sphere, double& distance) const;

		bool test(const Box& box, double& distance) const;

		bool test(const Triangle3D& triangle, double& distance) const;

		bool test(const Plane& plane, double& distance) const;


		Optional<Vec3> intersectsAt(const Sphere& sphere) const;

		Optional<Vec3> intersectsAt(const Box& box) const;

		Optional<Vec3> intersectsAt(const Triangle3D& triangle) const;

		Optional<Vec3> intersectsAt(const Plane& plane) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Ray& ray)
	{
		return	os << CharType('(') << ray.origin << CharType(',') << ray.direction << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Ray& ray)
	{
		CharType unused;
		return	is >> unused >> ray.origin >> unused >> ray.direction >> unused;
	}
}
