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
	enum class ShaderType
	{
		VS_4_0,
		
		PS_4_0
	};

	enum class ShaderStage
	{
		Vertex,

		Pixel,
	};

	struct ShaderCompileFlag
	{
		enum Flag
		{
			EnableStrictness	= (1 << 11),

			AvoidFlowControl	= (1 << 9),

			OptimizationLevel3	= (1 << 15),

			WarningsAreErrors	= (1 << 18),
			
			PreferFlowControl	= (1 << 10),

			PackMatrixRowMajor	= (1 << 3),

			PackMatrixColumnMajor	= (1 << 4),

			Default = EnableStrictness | OptimizationLevel3 | WarningsAreErrors,
		};
	};

	namespace Shader
	{
		bool Compile(const FilePath& from, const FilePath& to, ShaderType shaderType, int32 flags = ShaderCompileFlag::Default);

		bool Compile(const FilePath& from, const FilePath& to, ShaderType shaderType, const String& entryPoint, int32 flags = ShaderCompileFlag::Default);


		bool Compile(const FilePath& from, ByteArray& to, ShaderType shaderType, int32 flags = ShaderCompileFlag::Default);

		bool Compile(const FilePath& from, ByteArray& to, ShaderType shaderType, const String& entryPoint, int32 flags = ShaderCompileFlag::Default);
	}
}
