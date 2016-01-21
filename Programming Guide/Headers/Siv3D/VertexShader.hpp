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

namespace s3d
{
	/// <summary>
	/// 頂点シェーダ
	/// </summary>
	/// <remarks>
	/// 将来のバージョンの Siv3D で使用されます。
	/// </remarks>
	class VertexShader
	{
	private:

		class Handle{};

		using VertexShaderHandle = Siv3DHandle<Handle>;

		std::shared_ptr<VertexShaderHandle> m_handle;

	public:

		VertexShader();

		explicit VertexShader(const FilePath& path, bool preloadShader = false);

		~VertexShader();

		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const VertexShader& vertexShader) const;

		bool operator != (const VertexShader& vertexShader) const;

		const ByteArray& getBinary() const;
	};
}
