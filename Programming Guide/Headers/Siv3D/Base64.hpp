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
	/// <summary>
	/// Base64
	/// </summary>
	/// <remarks>
	/// Base64 エンコード/デコードの機能を提供します。
	/// </remarks>
	namespace Base64
	{
		/// <summary>
		/// データを Base64 エンコードします。
		/// </summary>
		/// <param name="data">
		/// エンコードするデータ
		/// </param>
		/// <returns>
		/// エンコードされたテキストデータ、エンコードに失敗した場合空の文字列
		/// </returns>
		String Encode(const ByteArray& data);

		/// <summary>
		/// データを Base64 エンコードします。
		/// </summary>
		/// <param name="data">
		/// エンコードするデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// エンコードするデータのサイズ（バイト）
		/// </param>
		/// <returns>
		/// エンコードされたテキストデータ、エンコードに失敗した場合空の文字列
		/// </returns>
		String Encode(_In_reads_bytes_(size) const void* const data, size_t size);

		/// <summary>
		/// テキストを Base64 でデコードします。
		/// </summary>
		/// <param name="src">
		/// デコードするテキスト
		/// </param>
		/// <returns>
		/// デコードされたバイナリデータ、デコードに失敗した場合空のバイナリデータ
		/// </returns>
		ByteArray Decode(const String& src);
	};
}

