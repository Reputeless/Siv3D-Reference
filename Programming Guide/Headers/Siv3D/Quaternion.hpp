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
# include "DirectXMathUtility.hpp"

namespace s3d
{
	/// <summary>
	/// クォータニオン
	/// </summary>
	struct Quaternion
	{
		__m128 component = { 0.0f, 0.0f, 0.0f, 1.0f };

		constexpr Quaternion() = default;

		constexpr Quaternion(float x, float y, float z, float w)
			: component{ x, y, z, w } {}

		Quaternion(const Vec3& normalizedAxis, double angle)
			: component(DirectX::XMQuaternionRotationNormal(ToVector(normalizedAxis, 0.0f), static_cast<float>(angle))) {}

		constexpr Quaternion(__m128 _v)
			: component(_v) {}

		Quaternion XM_CALLCONV operator * (const Quaternion& q) const
		{
			return DirectX::XMQuaternionMultiply(component, q.component);
		}

		Quaternion& operator *= (const Quaternion& q)
		{
			component = DirectX::XMQuaternionMultiply(component, q.component);
			return *this;
		}

		Vec3 operator * (const Vec3& v) const
		{
			return ToVec3(DirectX::XMVector3Rotate(ToVector(v, 0.0f), component));
		}

		static constexpr Quaternion XM_CALLCONV Identity()
		{
			return Quaternion();
		}

		static Quaternion XM_CALLCONV Roll(double angle)
		{
			return DirectX::XMQuaternionRotationRollPitchYaw(0.0f, 0.0f, static_cast<float>(angle));
		}

		static Quaternion XM_CALLCONV Pitch(double angle)
		{
			return DirectX::XMQuaternionRotationRollPitchYaw(static_cast<float>(angle), 0.0f, 0.0f);
		}

		static Quaternion XM_CALLCONV Yaw(double angle)
		{
			return DirectX::XMQuaternionRotationRollPitchYaw(0.0f, static_cast<float>(angle), 0.0f);
		}

		static Quaternion XM_CALLCONV RollPitchYaw(double roll, double pitch, double yaw)
		{
			return DirectX::XMQuaternionRotationRollPitchYaw(static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll));
		}

		static Quaternion XM_CALLCONV RotationArc(const Vec3& v1, const Vec3& v2, const Vec3& fallbackAxis = Vec3::Zero);

		Quaternion XM_CALLCONV roll(double angle) const;

		Quaternion XM_CALLCONV pitch(double angle) const;

		Quaternion XM_CALLCONV yaw(double angle) const;

		Quaternion XM_CALLCONV rollPitchYaw(double roll, double pitch, double yaw) const;

		Quaternion& rotateRoll(double angle);

		Quaternion& rotatePitch(double angle);

		Quaternion& rotateYaw(double angle);

		Quaternion& rotateRollPitchYaw(double roll, double pitch, double yaw);

		Quaternion XM_CALLCONV normalized() const
		{
			return DirectX::XMQuaternionNormalize(component);
		}

		Quaternion& normalize()
		{
			component = DirectX::XMQuaternionNormalize(component);
		}

		Mat4x4 XM_CALLCONV toMatrix() const;

		bool isIdentity() const
		{
			return DirectX::XMQuaternionIsIdentity(component);
		}
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Quaternion& q)
	{
		return os << q.component;
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Quaternion& q)
	{
		return is >> q.component;
	}

	namespace Math
	{
		inline Quaternion XM_CALLCONV Slerp(const Quaternion& q1, const Quaternion& q2, double f)
		{
			return DirectX::XMQuaternionSlerp(q1.component, q2.component, static_cast<float>(f));
		}
	}
}
