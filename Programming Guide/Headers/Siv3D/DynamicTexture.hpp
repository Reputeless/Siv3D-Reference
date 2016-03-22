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
# include "Texture.hpp"

namespace s3d
{
	/// <summary>
	/// 動的テクスチャ
	/// </summary>
	/// <remarks>
	/// 描画可能な画像です。
	/// Texture と異なり、メモリを再確保することなく内容を更新できます。
	/// </remarks>
	class DynamicTexture : public Texture
	{
	private:

		bool fill(uint32 width, uint32 height, const void* src, uint32 srcSize, uint32 stride, TextureFormat format, bool wait);

	public:

		DynamicTexture();

		DynamicTexture(uint32 width, uint32 height, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		DynamicTexture(uint32 width, uint32 height, const Color& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		explicit DynamicTexture(const Size& size, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		DynamicTexture(const Size& size, const Color& color, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		explicit DynamicTexture(const Image& image, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);

		template <class Type>
		explicit DynamicTexture(const CustomImage<Type>& image)
			: Texture(image.width, image.height, image.data(), image.memorySize(), image.stride, CustomImage<Type>::Format, Texture::_dyanmic()) {}

		bool fill(const Color& color);

		bool fill(const Color& color, const Rect& rect);

		/// <summary>
		/// 動的テクスチャの中身を同じ大きさの画像で更新します。
		/// 動的テクスチャが空の場合は新しい動的テクスチャを画像から作成します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <returns>
		/// 動的テクスチャの更新か作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool fill(const Image& image);

		template <class Type>
		bool fill(const CustomImage<Type>& image)
		{
			return fill(image.width, image.height, image.data(), image.memorySize(), image.stride, CustomImage<Type>::Format, true);
		}

		bool fill(const Image& image, const Rect& rect);

		bool tryFill(const Color& color);

		bool tryFill(const Color& color, const Rect& rect);

		/// <summary>
		/// 動的テクスチャの中身を同じ大きさの画像で更新します。
		/// 動的テクスチャが空の場合は新しい動的テクスチャを画像から作成します。
		/// fill() と異なり、テクスチャがビジー状態の時は更新を回避し、パフォーマンスの低下を防ぎます。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <returns>
		/// 動的テクスチャの更新か作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool tryFill(const Image& image);

		template <class Type>
		bool tryFill(const CustomImage<Type>& image)
		{
			return fill(image.width, image.height, image.data(), image.memorySize(), image.stride, CustomImage<Type>::Format, false);
		}

		bool tryFill(const Image& image, const Rect& rect);
	};
}
