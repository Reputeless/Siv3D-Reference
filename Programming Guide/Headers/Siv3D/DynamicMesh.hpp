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
# include "Array.hpp"
# include "Mesh.hpp"

namespace s3d
{
	/// <summary>
	/// 動的メッシュ
	/// </summary>
	class DynamicMesh : public Mesh
	{
	public:

		DynamicMesh();

		DynamicMesh(const MeshData& meshData);

		bool fill(const MeshData& meshData);

		bool fillVertices(const Array<MeshVertex>& vertices);

		bool fillIndices(const Array<uint32>& indices);

		bool tryFillVertices(const Array<MeshVertex>& vertices);

		bool tryFillIndices(const Array<uint32>& indices);
	};
}
