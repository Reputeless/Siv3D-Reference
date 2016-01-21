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
# include "MeshData.hpp"
# include "Model.hpp"

namespace s3d
{
	namespace ModelLoader
	{
		Array<MeshData> LoadMeshDataFromOBJ(const FilePath& path);

		Array<ModelNode> LoadModelNodesFromOBJ(const FilePath& path);
	}
}
