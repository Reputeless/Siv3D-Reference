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
	/// ピクセルシェーダ
	/// </summary>
	/// <remarks>
	/// 将来のバージョンの Siv3D で使用されます。
	/// </remarks>
	class PixelShader
	{
	private:

		class Handle{};

		using PixelShaderHandle = Siv3DHandle<Handle>;

		std::shared_ptr<PixelShaderHandle> m_handle;

	public:

		PixelShader();

		explicit PixelShader(const FilePath& path, bool preloadShader = false);

		~PixelShader();

		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const PixelShader& pixelShader) const;

		bool operator != (const PixelShader& pixelShader) const;
	};
}
