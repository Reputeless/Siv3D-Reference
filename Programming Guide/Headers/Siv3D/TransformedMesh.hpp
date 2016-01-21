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
# include "Mesh.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	struct TransformedMesh
	{
		Mat4x4 matrix;

		Mesh mesh;

		TransformedMesh() = default;

		TransformedMesh(const Mat4x4& _matrix, const Mesh& _mesh)
			: matrix(_matrix)
			, mesh(_mesh) {}

		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(size_t startIndex, size_t indexCount, const ColorF& color = Palette::White) const;

		void drawSubset(size_t startIndex, size_t indexCount, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawForward(const ColorF& color = Palette::White) const;

		void drawForward(const Texture& texture, const ColorF& color = Palette::White) const;

		void drawForwardSubset(size_t startIndex, size_t indexCount, const ColorF& color = Palette::White) const;

		void drawForwardSubset(size_t startIndex, size_t indexCount, const Texture& texture, const ColorF& color = Palette::White) const;

		TransformedMesh translated(double x, double y, double z) const;

		TransformedMesh translated(const Vec3& translation) const;

		TransformedMesh scaled(double s) const;

		TransformedMesh scaled(double sx, double sy, double sz) const;

		TransformedMesh scaled(const Vec3& scaling) const;

		TransformedMesh rotated(double pitch, double yaw, double roll) const;

		TransformedMesh rotated(const Vec3& pitchYawRoll) const;

		TransformedMesh rotated(const Quaternion& rotation) const;
	};
}
