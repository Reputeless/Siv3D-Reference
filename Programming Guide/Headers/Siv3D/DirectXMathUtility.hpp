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
# include <DirectXMath.h>
# include "PointVector.hpp"

namespace s3d
{
	using Vector = DirectX::XMVECTOR;
	using Matrix = DirectX::XMMATRIX;

	inline constexpr Vector XM_CALLCONV ToVector(float x, float y, float z, float w)
	{
		return{ x, y, z, w };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const Float3& xyz, float w)
	{
		return{ xyz.x, xyz.y, xyz.z, w };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const Float4& v)
	{
		return{ v.x, v.y, v.z, v.w };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const Vec3& xyz, float w)
	{
		return{ static_cast<float>(xyz.x), static_cast<float>(xyz.y), static_cast<float>(xyz.z), w };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const Vec3& xyz, double w)
	{
		return{ static_cast<float>(xyz.x), static_cast<float>(xyz.y), static_cast<float>(xyz.z), static_cast<float>(w) };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const Vec4& v)
	{
		return{ static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w) };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const ColorF& c)
	{
		return{ static_cast<float>(c.r), static_cast<float>(c.g), static_cast<float>(c.b), static_cast<float>(c.a) };
	}

	inline constexpr Vector XM_CALLCONV ToVector(const ColorF& c, float a)
	{
		return{ static_cast<float>(c.r), static_cast<float>(c.g), static_cast<float>(c.b), a };
	}

	inline constexpr Vec3 ToVec3(const Vector& v)
	{
		return Vec3(v.m128_f32[0], v.m128_f32[1], v.m128_f32[2]);
	}

	inline constexpr Vec4 ToVec4(const Vector& v)
	{
		return Vec4(v.m128_f32[0], v.m128_f32[1], v.m128_f32[2], v.m128_f32[3]);
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Vector& v)
	{
		return os << CharType('(') << v.m128_f32[0] << CharType(',') << v.m128_f32[1] << CharType(',') << v.m128_f32[2] << CharType(',') << v.m128_f32[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Vector& v)
	{
		CharType unused;
		return is >> unused >> v.m128_f32[0] >> unused >> v.m128_f32[1] >> unused >> v.m128_f32[2] >> unused >> v.m128_f32[3] >> unused;
	}
}
