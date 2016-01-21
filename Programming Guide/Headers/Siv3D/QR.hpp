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
# include "Unspecified.hpp"
# include "String.hpp"
# include "ByteArray.hpp"
# include "Image.hpp"
# include "Quad.hpp"

namespace s3d
{
	/// <summary>
	/// QR のエンコーディングモード
	/// </summary>
	enum class QREncodingMode
	{
		Numeric,

		/// <remarks>
		/// 0-9, A-Z, $ % * + - . / : と半角スペース
		/// 小文字と大文字は区別されない
		/// </remarks>
		Alnum,

		Binary,

		Kanji,

		Unknown,
	};

	/// <summary>
	/// QR のエラー訂正レベル
	/// </summary>
	enum class QRECLevel
	{
		Low,

		Medium,

		Quartile,

		High,
	};

	struct QRData
	{
		/// <summary>
		/// フレーム画像内のマーカーの領域
		/// </summary>
		Quad quad;

		String text;

		ByteArray data;

		QREncodingMode mode;

		int32 version;

		QRECLevel ecLevel;
	};

	namespace QR
	{
		Optional<int32> MinimumVersion(const String& string, QREncodingMode mode = QREncodingMode::Binary, QRECLevel ec = QRECLevel::Low);

		Optional<int32> MinimumVersion(const void* data, size_t size, QRECLevel ec = QRECLevel::Low);

		inline Optional<int32> MinimumVersion(const ByteArray& data, QRECLevel ec = QRECLevel::Low)
		{
			return MinimumVersion(data.data(), static_cast<size_t>(data.size()), ec);
		}

		Image Encode(const String& string, QREncodingMode mode = QREncodingMode::Binary, QRECLevel ec = QRECLevel::Low, const Optional<int32>& version = unspecified);

		Image Encode(const void* data, size_t size, QRECLevel ec = QRECLevel::Low, const Optional<int32>& version = unspecified);

		inline Image Encode(const ByteArray& data, QRECLevel ec = QRECLevel::Low, const Optional<int32>& version = unspecified)
		{
			return Encode(data.data(), static_cast<size_t>(data.size()), ec, version);
		}

		bool Decode(const Image& image, QRData& data);
	}
}
