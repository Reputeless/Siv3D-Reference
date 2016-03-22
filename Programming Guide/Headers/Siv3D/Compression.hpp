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
# include "ByteArray.hpp"

namespace s3d
{
	namespace Compression
	{
		ByteArray Compress(const void* data, size_t size, _Field_range_(1, 9) int32 level = 7);

		inline ByteArray Compress(const ByteArray& data, _Field_range_(1, 9) int32 level = 7)
		{
			return Compress(data.data(), static_cast<size_t>(data.size()), level);
		}

		ByteArray Decompress(const void* data, size_t size);

		inline ByteArray Decompress(const ByteArray& data)
		{
			return Decompress(data.data(), static_cast<size_t>(data.size()));
		}
	}
}
