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
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// MD5 ハッシュ値
	/// </summary>
	struct MD5Value
	{
		uint8 value[16];

		String asString() const;

		bool operator == (const MD5Value& other) const;

		bool operator != (const MD5Value& other) const;
	};

	/// <summary>
	/// MD5
	/// </summary>
	/// <remarks>
	/// データから MD5 ハッシュ値を計算する機能を提供します。
	/// </remarks>
	namespace MD5
	{
		/// <summary>
		/// データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="data">
		/// MD5 ハッシュ値を計算するデータ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		MD5Value Encrypt(const ByteArray& data);

		/// <summary>
		/// データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="data">
		/// MD5 ハッシュ値を計算するデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// MD5 ハッシュ値を計算するデータのサイズ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		MD5Value Encrypt(_In_reads_bytes_(size) const void* const data, size_t size);

		/// <summary>
		/// 文字列データから MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="str">
		/// MD5 ハッシュ値を計算する文字列データ
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		MD5Value EncryptFromString(StringView str);

		/// <summary>
		/// 文字列から MD5 ハッシュを計算します。
		/// </summary>
		/// <param name="str">
		/// MD5 ハッシュ値を計算する文字列
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		MD5Value EncryptFromString(const std::string& str);

		/// <summary>
		/// 指定したファイルの MD5 ハッシュ値を計算します。
		/// </summary>
		/// <param name="path">
		/// MD5 ハッシュ値を計算するファイルのパス
		/// </param>
		/// <returns>
		/// MD5 ハッシュ値
		/// </returns>
		MD5Value EncryptFromFile(const FilePath& path);
	};
}
