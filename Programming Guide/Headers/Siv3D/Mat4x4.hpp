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
# include "Quaternion.hpp"

namespace s3d
{
	/// <summary>
	/// 4x4 行列
	/// </summary>
	struct Mat4x4 : Matrix
	{
		Mat4x4() = default;

		Mat4x4(const Matrix& mat)
			: Matrix(mat) {}

		static Mat4x4 XM_CALLCONV Identity()
		{
			return DirectX::XMMatrixIdentity();
		}

		static Mat4x4 XM_CALLCONV Translate(double x, double y, double z)
		{
			return DirectX::XMMatrixTranslation(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		}

		static Mat4x4 XM_CALLCONV Translate(const Vec3& pos)
		{
			return DirectX::XMMatrixTranslation(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
		}

		static Mat4x4 XM_CALLCONV Scale(double scale)
		{
			return DirectX::XMMatrixScaling(static_cast<float>(scale), static_cast<float>(scale), static_cast<float>(scale));
		}

		static Mat4x4 XM_CALLCONV Scale(double xs, double ys, double zs)
		{
			return DirectX::XMMatrixScaling(static_cast<float>(xs), static_cast<float>(ys), static_cast<float>(zs));
		}

		static Mat4x4 XM_CALLCONV Scale(const Vec3& scale)
		{
			return DirectX::XMMatrixScaling(static_cast<float>(scale.x), static_cast<float>(scale.y), static_cast<float>(scale.z));
		}

		static Mat4x4 XM_CALLCONV Rotate(double pitch, double yaw, double roll)
		{
			return DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll));
		}

		static Mat4x4 XM_CALLCONV Rotate(const Vec3& pitchYawRoll)
		{
			return DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(pitchYawRoll.x), static_cast<float>(pitchYawRoll.y), static_cast<float>(pitchYawRoll.z));
		}

		static Mat4x4 XM_CALLCONV Rotate(const Quaternion& quaternion)
		{
			return quaternion.toMatrix();
		}

		static Mat4x4 XM_CALLCONV AffineTransform(const Vec3& scaling, const Vec3& rotation, const Vec3& translation)
		{
			const DirectX::XMVECTOR scale = ToVector(scaling, 1.0f);
			const DirectX::XMVECTOR rotationOrigin = DirectX::g_XMZero;
			const DirectX::XMVECTOR rotate = DirectX::XMQuaternionRotationRollPitchYaw(
				static_cast<float>(rotation.x),
				static_cast<float>(rotation.y),
				static_cast<float>(rotation.z));
			const DirectX::XMVECTOR translate = ToVector(translation, 0.0f);

			return DirectX::XMMatrixAffineTransformation(scale, rotationOrigin, rotate, translate);
		}

		static Mat4x4 XM_CALLCONV AffineTransform(const Vec3& scaling, const Quaternion& rotation, const Vec3& translation)
		{
			const DirectX::XMVECTOR scale = ToVector(scaling, 1.0f);
			const DirectX::XMVECTOR rotationOrigin = DirectX::g_XMZero;
			const DirectX::XMVECTOR translate = ToVector(translation, 0.0f);

			return DirectX::XMMatrixAffineTransformation(scale, rotationOrigin, rotation.component, translate);
		}

		static Mat4x4 XM_CALLCONV AffineTransform(double scaling, const Quaternion& rotation, const Vec3& translation)
		{
			const float sf = static_cast<float>(scaling);
			const DirectX::XMVECTOR scale = DirectX::XMVectorSet(sf, sf, sf, 0.0f);
			const DirectX::XMVECTOR rotationOrigin = DirectX::g_XMZero;
			const DirectX::XMVECTOR translate = ToVector(translation, 0.0f);

			return DirectX::XMMatrixAffineTransformation(scale, rotationOrigin, rotation.component, translate);
		}

		Mat4x4 XM_CALLCONV translated(double x, double y, double z) const
		{
			return *this * DirectX::XMMatrixTranslation(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		}

		Mat4x4 XM_CALLCONV translated(const Vec3& pos) const
		{
			return *this * DirectX::XMMatrixTranslation(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
		}

		Mat4x4 XM_CALLCONV scaled(double scale) const
		{
			return *this * DirectX::XMMatrixScaling(static_cast<float>(scale), static_cast<float>(scale), static_cast<float>(scale));
		}

		Mat4x4 XM_CALLCONV scaled(double xs, double ys, double zs) const
		{
			return *this * DirectX::XMMatrixScaling(static_cast<float>(xs), static_cast<float>(ys), static_cast<float>(zs));
		}

		Mat4x4 XM_CALLCONV scaled(const Vec3& scale) const
		{
			return *this * DirectX::XMMatrixScaling(static_cast<float>(scale.x), static_cast<float>(scale.y), static_cast<float>(scale.z));
		}

		Mat4x4 XM_CALLCONV rotated(double pitch, double yaw, double roll) const
		{
			return *this * DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(pitch), static_cast<float>(yaw), static_cast<float>(roll));
		}

		Mat4x4 XM_CALLCONV rotated(const Vec3& pitchYawRoll) const
		{
			return *this * DirectX::XMMatrixRotationRollPitchYaw(static_cast<float>(pitchYawRoll.x), static_cast<float>(pitchYawRoll.y), static_cast<float>(pitchYawRoll.z));
		}

		Mat4x4 XM_CALLCONV rotated(const Quaternion& quaternion) const
		{
			return *this * quaternion.toMatrix();
		}

		bool decompose(Vec3& scale, Quaternion& rotation, Vec3& transform) const;

		double determinant() const;

		Mat4x4 inverse() const;

		Mat4x4 inverse(double& determinant) const;

		Mat4x4 transposed() const;

		Vec3 transform(const Vec3& v)
		{
			ToVec3(DirectX::XMVector3Transform(ToVector(v, 0.0f), *this));
		}

		Vec4 transform(const Vec4& v)
		{
			ToVec4(DirectX::XMVector4Transform(ToVector(v), *this));
		}
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Mat4x4& mat)
	{
		return os << CharType('(')
			<< mat.r[0] << CharType(',')
			<< mat.r[1] << CharType(',')
			<< mat.r[2] << CharType(',')
			<< mat.r[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Mat4x4& mat)
	{
		CharType unused;

		return	is >> unused
			>> mat.r[0] >> unused
			>> mat.r[1] >> unused
			>> mat.r[2] >> unused
			>> mat.r[3] >> unused;
	}
}
