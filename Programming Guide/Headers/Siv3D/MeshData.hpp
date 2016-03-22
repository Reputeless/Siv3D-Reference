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
# include "PointVector.hpp"
# include "Box.hpp"

namespace s3d
{
	struct MeshVertex
	{
		Float3 position;

		Float3 normal;

		Float2 texcoord;
	};

	enum class PlaneFace
	{
		XZ,

		XY,

		YZ,
	};

	namespace Geometry3D
	{
		static constexpr Float2 Box6DefaultUV[24] =
		{
			{ 0.0f,		0.0f },
			{ 1/3.0f,	0.0f },
			{ 0.0f,		0.5f },
			{ 1/3.0f,	0.5f },

			{ 1 / 3.0f,	0.0f },
			{ 2 / 3.0f,	0.0f },
			{ 1 / 3.0f,	0.5f },
			{ 2 / 3.0f,	0.5f },

			{ 2 / 3.0f,	0.0f },
			{ 1.0f,		0.0f },
			{ 2 / 3.0f,	0.5f },
			{ 1.0f,		0.5f },

			{ 0.0f,		0.5f },
			{ 1/3.0f,	0.5f },
			{ 0.0f,		1.0f },
			{ 1/3.0f,	1.0f },

			{ 1 / 3.0f,	0.5f },
			{ 2 / 3.0f,	0.5f },
			{ 1 / 3.0f,	1.0f },
			{ 2 / 3.0f,	1.0f },

			{ 2 / 3.0f,	0.5f },
			{ 1.0f,		0.5f },
			{ 2 / 3.0f,	1.0f },
			{ 1.0f,		1.0f },
		};
	}

	struct MeshData
	{
		Array<MeshVertex> vertices;

		Array<uint32> indices;

		MeshData() = default;

		MeshData(uint32 vertexSize, uint32 indexSize)
			: vertices(vertexSize)
			, indices(indexSize) {}

		MeshData(Array<MeshVertex> _vertices, Array<uint32> _indices)
			: vertices(std::move(_vertices))
			, indices(std::move(_indices)) {}

		/// <summary>
		/// 法線を生成します。
		/// </summary>
		/// <returns>
		/// 法線の生成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool computeNormals();

		/// <summary>
		/// バウンディングボックスを計算します。
		/// </summary>
		/// <returns>
		/// バウンディングボックス
		/// </returns>
		Box computeBoundingBox() const;

		static MeshData Plane(double size = 1.0, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 }, PlaneFace face = PlaneFace::XZ)
		{
			return Plane({ size, size }, uvScale, uvOffset, face);
		}

		static MeshData Plane(double sizeX, double sizeZ, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 }, PlaneFace face = PlaneFace::XZ)
		{
			return Plane({ sizeX, sizeZ }, uvScale, uvOffset, face);
		}

		static MeshData	Plane(const Vec2& size, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 }, PlaneFace face = PlaneFace::XZ);

		static MeshData PlaneXZ(double size = 1.0, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return PlaneXZ({ size, size }, uvScale, uvOffset);
		}

		static MeshData PlaneXZ(double sizeX, double sizeZ, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return PlaneXZ({ sizeX, sizeZ }, uvScale, uvOffset);
		}

		static MeshData PlaneXZ(const Vec2& size, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return Plane(size, uvScale, uvOffset, PlaneFace::XZ);
		}

		static MeshData PlaneXY(double size = 1.0, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return PlaneXY({ size, size }, uvScale, uvOffset);
		}

		static MeshData PlaneXY(double sizeX, double sizeY, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return PlaneXY({ sizeX, sizeY }, uvScale, uvOffset);
		}

		static MeshData PlaneXY(const Vec2& size, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return Plane(size, uvScale, uvOffset, PlaneFace::XY);
		}

		static MeshData PlaneYZ(double size = 1.0, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return PlaneYZ({ size, size }, uvScale, uvOffset);
		}

		static MeshData PlaneYZ(double sizeY, double sizeZ, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return PlaneYZ({ sizeY, sizeZ }, uvScale, uvOffset);
		}

		static MeshData PlaneYZ(const Vec2& size, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return MeshData::Plane(size, uvScale, uvOffset, PlaneFace::YZ);
		}

		static MeshData Box(double size = 1.0, bool flipNormals = false)
		{
			return Box({ size, size, size }, flipNormals);
		}

		static MeshData Box(double sizeX, double sizeY, double sizeZ, bool flipNormals = false)
		{
			return Box({ sizeX, sizeY, sizeZ }, flipNormals);
		}

		static MeshData Box(const Vec3& size, bool flipNormals = false);

		static MeshData Box6(double size = 1.0, const Float2(&uv)[24] = Geometry3D::Box6DefaultUV, bool flipNormals = false)
		{
			return Box6({ size, size, size }, uv, flipNormals);
		}

		static MeshData Box6(double sizeX, double sizeY, double sizeZ, const Float2(&uv)[24] = Geometry3D::Box6DefaultUV, bool flipNormals = false)
		{
			return Box6({ sizeX, sizeY, sizeZ }, uv, flipNormals);
		}

		static MeshData Box6(const Vec3& size, const Float2(&uv)[24] = Geometry3D::Box6DefaultUV, bool flipNormals = false);

		static MeshData Sphere(double r = 1.0, uint32 quality = 24, bool flipNormals = false);

		static MeshData Disc(double r = 1.0, PlaneFace face = PlaneFace::XZ, uint32 quality = 63);

		static MeshData Cylinder(double r = 1.0, double h = 1.0, uint32 quality = 63);

		static MeshData Cone(double r = 1.0, double h = 1.0, uint32 quality = 63);

		static MeshData Pyramid(double wd = 1.0, double h = 1.0)
		{
			return Pyramid(wd, wd, h);
		}

		static MeshData Pyramid(double w, double d, double h);

		static MeshData Bipyramid(double wd = 1.0, double h = 1.0)
		{
			return Bipyramid(wd, wd, h);
		}

		static MeshData Bipyramid(double w, double d, double h);

		static MeshData Polygon(const s3d::Polygon& polygon, const Vec2& uvScale, const Vec2& uvOffset);

		/// <summary>
		/// Polygon に厚みを持たせて MeshData を作成します。
		/// </summary>
		/// <param name="polygon">
		/// Polygon
		/// </param>
		/// <param name="height">
		/// 厚み
		/// </param>
		/// <param name="uvScale">
		/// UV マップスケール
		/// </param>
		/// <param name="uvOffset">
		/// UV マップオフセット
		/// </param>
		/// <param name="uvY">
		/// 厚み部分の UV マップパラメータ
		/// </param>
		/// <returns>
		/// 作成された MeshData
		/// </returns>
		static MeshData Polygon(const s3d::Polygon& polygon, double height, const Vec2& uvScale, const Vec2& uvOffset, const Vec2& uvY = { 1.0, 1.0 });
	

		static MeshData Torus(double size, double tubeRadius, int32 slices = 32, int32 stacks = 32);

		static MeshData Hemisphere(double radius, int32 slices = 20, int32 stacks = 20);

		static MeshData Dodecahedron(double size);

		static MeshData Tetrahedron(double size);

		static MeshData Icosahedron(double size);

		static MeshData Rock(double size, uint32 seed, int32 nsubdivisions = 2);


		static MeshData Grid(double size, int32 grid, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 })
		{
			return Grid({ size, size }, grid, grid, uvScale, uvOffset);
		}

		static MeshData Grid(const Vec2& size, int32 gridX, int32 gridY, const Vec2& uvScale = { 1, 1 }, const Vec2& uvOffset = { 0, 0 });

		static MeshData TerrainBase(double size, int32 grid = 64, bool skirt = false);
	};
}
