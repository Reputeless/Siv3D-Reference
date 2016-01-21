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
# include <memory>
# include "Fwd.hpp"
# include "Handle.hpp"
# include "Color.hpp"
# include "PropertyMacro.hpp"
# include "Texture.hpp"

namespace s3d
{
	/// <summary>
	/// メッシュ
	/// </summary>
	class Mesh
	{
	protected:

		class Handle{};

		using MeshHandle = Siv3DHandle<Handle>;

		std::shared_ptr<MeshHandle> m_handle;

		struct _modeDyanmic{};

		explicit Mesh(const MeshData& meshData, const _modeDyanmic&);

	public:

		Mesh();

		explicit Mesh(const MeshData& meshData);

		virtual ~Mesh();

		void release();

		explicit operator bool() const;

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const Mesh& mesh) const;

		bool operator != (const Mesh& mesh) const;

		Property_Get(size_t, num_vertices) const;

		Property_Get(size_t, num_indices) const;

		Property_Get(Box, boundingBox) const;

		void draw(const ColorF& color = Palette::White) const;

		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& matrix, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& matrix, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(size_t startIndex, size_t indexCount, const ColorF& color = Palette::White) const;

		void drawSubset(size_t startIndex, size_t indexCount, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(size_t startIndex, size_t indexCount, const Mat4x4& matrix, const ColorF& color = Palette::White) const;

		void drawSubset(size_t startIndex, size_t indexCount, const Mat4x4& matrix, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawForward(const ColorF& color = Palette::White) const;

		void drawForward(const Texture& texture, const ColorF& color = Palette::White) const;

		void drawForward(const Mat4x4& matrix, const ColorF& color = Palette::White) const;

		void drawForward(const Mat4x4& matrix, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubsetForward(size_t startIndex, size_t indexCount, const ColorF& color = Palette::White) const;

		void drawSubsetForward(size_t startIndex, size_t indexCount, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubsetForward(size_t startIndex, size_t indexCount, const Mat4x4& matrix, const ColorF& color = Palette::White) const;

		void drawSubsetForward(size_t startIndex, size_t indexCount, const Mat4x4& matrix, const Texture& texture, const ColorF& color = Palette::White) const;

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
