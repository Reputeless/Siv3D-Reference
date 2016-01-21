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
# include "Grid.hpp"
# include "CustomColor.hpp"
# include "Image.hpp"
# include "TextureFormat.hpp"

namespace s3d
{
	template <class Type>
	class CustomImage : public Grid<Type>
	{
	public:

		using ColorType = Type;

		static constexpr TextureFormat Format = Type::Format;

		CustomImage() = default;

		CustomImage(int32 width, int32 height)
			: Grid(width, height) {}

		CustomImage(const Size& size)
			: Grid(size.x, size.y) {}

		CustomImage(int32 width, int32 height, const Type& value)
			: Grid(width, height, value) {}

		CustomImage(const Size& size, const Type& value)
			: Grid(size.x, size.y, value) {}

		CustomImage(const FilePath& path);

		CustomImage(const Image& image)
		{
			fromImage(image);
		}

		/// <summary>
		/// 画像が空ではないかを返します。
		/// </summary>
		/// <returns>
		/// 画像が空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return !isEmpty;
		}

		/// <summary>
		/// 画像の幅（ピクセル）
		/// </summary>
		Property_Get(int32, width) const { return static_cast<int32>(Grid::width); }

		/// <summary>
		/// 画像の高さ（ピクセル）
		/// </summary>
		Property_Get(int32, height) const { return static_cast<int32>(Grid::height); }

		/// <summary>
		/// 画像の幅と高さ（ピクセル）
		/// </summary>
		Property_Get(Size, size) const { return{ width, height }; }

		/// <summary>
		/// 画像の各行のデータサイズ
		/// </summary>
		Property_Get(uint32, stride) const { return static_cast<uint32>(width * sizeof(Type)); }

		/// <summary>
		/// 画像のピクセル数
		/// </summary>
		Property_Get(uint32, num_pixels) const { return static_cast<uint32>(width * height); }

		/// <summary>
		/// 画像のデータサイズ
		/// </summary>
		uint32 memorySize() const { return static_cast<uint32>(stride * height); }

		Image toImage() const
		{
			if (isEmpty)
			{
				return Image();
			}

			Image image(static_cast<uint32>(width), static_cast<uint32>(height));
			Color* pDst = image[0];
			const Color* pDstEnd = pDst + image.num_pixels;
			const Type* pSrc = data();
			
			while (pDst != pDstEnd)
			{
				(*pDst++) = (pSrc++)->toColor();
			}

			return image;
		}

		void fromImage(const Image& image)
		{
			resize(image.width, image.height);

			if (!image)
			{
				return;
			}

			const Color* pSrc = image[0];
			const Color* pSrcEnd = pSrc + image.num_pixels;
			Type* pDst = data();

			while (pSrc != pSrcEnd)
			{
				(*pDst++) = Type(*pSrc++);
			}
		}

		bool saveDDS(const FilePath& path) const;

		ByteArray encodeDDS() const;
	};

	using ImageR32F		= CustomImage<R32F>;
	using ImageRGBA16F	= CustomImage<RGBA16F>;
	using ImageRGBA32F	= CustomImage<RGBA32F>;
	using ImageR16F		= CustomImage<R16F>;
	using ImageRG16F	= CustomImage<RG16F>;
	using ImageRG32F	= CustomImage<RG32F>;
}
