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
# include "Texture.hpp"

namespace s3d
{
	class RenderTexture : public Texture
	{
	protected:

		struct _swapChain {};

		RenderTexture(const _swapChain&);

	public:

		RenderTexture();

		RenderTexture(uint32 width, uint32 height, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, const MultiSampling& multiSampling = MultiSampling(1, 0));

		explicit RenderTexture(const Size& size, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, const MultiSampling& multiSampling = MultiSampling(1, 0));

		RenderTexture(uint32 width, uint32 height, const ColorF& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, const MultiSampling& multiSampling = MultiSampling(1, 0));

		RenderTexture(const Size& size, const ColorF& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, const MultiSampling& multiSampling = MultiSampling(1, 0));

		void clear(const ColorF& color);

		void beginReset();

		bool endReset(const Size& size, TextureFormat format = TextureFormat::R8G8B8A8_Unorm, const MultiSampling& multiSampling = MultiSampling(1, 0));
	
		bool saveDDS(const FilePath& path) const;
	};
}
