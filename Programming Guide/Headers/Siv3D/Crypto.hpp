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
# include "Array.hpp"
# include "String.hpp"
# include "ByteArray.hpp"

namespace s3d
{
	/// <summary>
	/// AES-128 暗号鍵
	/// </summary>
	union AES128Key
	{
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		AES128Key() = default;

		/// <summary>
		/// AES-128 暗号鍵を定義します。
		/// </summary>
		/// <param name="a">
		/// 8 bit 整数
		/// </param>
		/// <param name="b">
		/// 8 bit 整数
		/// </param>
		/// <param name="c">
		/// 8 bit 整数
		/// </param>
		/// <param name="d">
		/// 8 bit 整数
		/// </param>
		/// <param name="e">
		/// 8 bit 整数
		/// </param>
		/// <param name="f">
		/// 8 bit 整数
		/// </param>
		/// <param name="g">
		/// 8 bit 整数
		/// </param>
		/// <param name="h">
		/// 8 bit 整数
		/// </param>
		/// <param name="i">
		/// 8 bit 整数
		/// </param>
		/// <param name="j">
		/// 8 bit 整数
		/// </param>
		/// <param name="k">
		/// 8 bit 整数
		/// </param>
		/// <param name="l">
		/// 8 bit 整数
		/// </param>
		/// <param name="m">
		/// 8 bit 整数
		/// </param>
		/// <param name="n">
		/// 8 bit 整数
		/// </param>
		/// <param name="o">
		/// 8 bit 整数
		/// </param>
		/// <param name="p">
		/// 8 bit 整数
		/// </param>
		AES128Key(uint8 a, uint8 b, uint8 c, uint8 d, uint8 e, uint8 f, uint8 g, uint8 h
			, uint8 i, uint8 j, uint8 k, uint8 l, uint8 m, uint8 n, uint8 o, uint8 p)
		{
			v8[0] = a;
			v8[1] = b;
			v8[2] = c;
			v8[3] = d;
			v8[4] = e;
			v8[5] = f;
			v8[6] = g;
			v8[7] = h;

			v8[8] = i;
			v8[9] = j;
			v8[10] = k;
			v8[11] = l;
			v8[12] = m;
			v8[13] = n;
			v8[14] = o;
			v8[15] = p;
		}

		/// <summary>
		/// AES-128 暗号鍵を定義します。
		/// </summary>
		/// <param name="a">
		/// 16 bit 整数
		/// </param>
		/// <param name="b">
		/// 16 bit 整数
		/// </param>
		/// <param name="c">
		/// 16 bit 整数
		/// </param>
		/// <param name="d">
		/// 16 bit 整数
		/// </param>
		/// <param name="e">
		/// 16 bit 整数
		/// </param>
		/// <param name="f">
		/// 16 bit 整数
		/// </param>
		/// <param name="g">
		/// 16 bit 整数
		/// </param>
		/// <param name="h">
		/// 16 bit 整数
		/// </param>
		AES128Key(uint16 a, uint16 b, uint16 c, uint16 d, uint16 e, uint16 f, uint16 g, uint16 h)
		{
			v16[0] = a;
			v16[1] = b;
			v16[2] = c;
			v16[3] = d;
			v16[4] = e;
			v16[5] = f;
			v16[6] = g;
			v16[7] = h;
		}

		/// <summary>
		/// AES-128 暗号鍵を定義します。
		/// </summary>
		/// <param name="a">
		/// 32 bit 整数
		/// </param>
		/// <param name="b">
		/// 32 bit 整数
		/// </param>
		/// <param name="c">
		/// 32 bit 整数
		/// </param>
		/// <param name="d">
		/// 32 bit 整数
		/// </param>
		AES128Key(uint32 a, uint32 b, uint32 c, uint32 d)
		{
			v32[0] = a;
			v32[1] = b;
			v32[2] = c;
			v32[3] = d;
		}

		/// <summary>
		/// AES-128 暗号鍵を定義します。
		/// </summary>
		/// <param name="a">
		/// 64 bit 整数
		/// </param>
		/// <param name="b">
		/// 64 bit 整数
		/// </param>
		AES128Key(uint64 a, uint64 b)
		{
			v64[0] = a;
			v64[1] = b;
		}

		uint8 v8[16];

		uint16 v16[8];

		uint32 v32[4];

		uint64 v64[2];
	};

	/// <summary>
	/// AES-128 初期化ベクトル
	/// </summary>
	union AESIV
	{
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		AESIV() = default;

		/// <summary>
		/// AES-128 初期化ベクトルを定義します。
		/// </summary>
		/// <param name="a">
		/// 8 bit 整数
		/// </param>
		/// <param name="b">
		/// 8 bit 整数
		/// </param>
		/// <param name="c">
		/// 8 bit 整数
		/// </param>
		/// <param name="d">
		/// 8 bit 整数
		/// </param>
		/// <param name="e">
		/// 8 bit 整数
		/// </param>
		/// <param name="f">
		/// 8 bit 整数
		/// </param>
		/// <param name="g">
		/// 8 bit 整数
		/// </param>
		/// <param name="h">
		/// 8 bit 整数
		/// </param>
		/// <param name="i">
		/// 8 bit 整数
		/// </param>
		/// <param name="j">
		/// 8 bit 整数
		/// </param>
		/// <param name="k">
		/// 8 bit 整数
		/// </param>
		/// <param name="l">
		/// 8 bit 整数
		/// </param>
		/// <param name="m">
		/// 8 bit 整数
		/// </param>
		/// <param name="n">
		/// 8 bit 整数
		/// </param>
		/// <param name="o">
		/// 8 bit 整数
		/// </param>
		/// <param name="p">
		/// 8 bit 整数
		/// </param>
		AESIV(uint8 a, uint8 b, uint8 c, uint8 d, uint8 e, uint8 f, uint8 g, uint8 h
			, uint8 i, uint8 j, uint8 k, uint8 l, uint8 m, uint8 n, uint8 o, uint8 p)
		{
			v8[0] = a;
			v8[1] = b;
			v8[2] = c;
			v8[3] = d;
			v8[4] = e;
			v8[5] = f;
			v8[6] = g;
			v8[7] = h;

			v8[8] = i;
			v8[9] = j;
			v8[10] = k;
			v8[11] = l;
			v8[12] = m;
			v8[13] = n;
			v8[14] = o;
			v8[15] = p;
		}

		/// <summary>
		/// AES-128 初期化ベクトルを定義します。
		/// </summary>
		/// <param name="a">
		/// 16 bit 整数
		/// </param>
		/// <param name="b">
		/// 16 bit 整数
		/// </param>
		/// <param name="c">
		/// 16 bit 整数
		/// </param>
		/// <param name="d">
		/// 16 bit 整数
		/// </param>
		/// <param name="e">
		/// 16 bit 整数
		/// </param>
		/// <param name="f">
		/// 16 bit 整数
		/// </param>
		/// <param name="g">
		/// 16 bit 整数
		/// </param>
		/// <param name="h">
		/// 16 bit 整数
		/// </param>
		AESIV(uint16 a, uint16 b, uint16 c, uint16 d, uint16 e, uint16 f, uint16 g, uint16 h)
		{
			v16[0] = a;
			v16[1] = b;
			v16[2] = c;
			v16[3] = d;
			v16[4] = e;
			v16[5] = f;
			v16[6] = g;
			v16[7] = h;
		}

		/// <summary>
		/// AES-128 初期化ベクトルを定義します。
		/// </summary>
		/// <param name="a">
		/// 32 bit 整数
		/// </param>
		/// <param name="b">
		/// 32 bit 整数
		/// </param>
		/// <param name="c">
		/// 32 bit 整数
		/// </param>
		/// <param name="d">
		/// 32 bit 整数
		/// </param>
		AESIV(uint32 a, uint32 b, uint32 c, uint32 d)
		{
			v32[0] = a;
			v32[1] = b;
			v32[2] = c;
			v32[3] = d;
		}

		/// <summary>
		/// AES-128 初期化ベクトルを定義します。
		/// </summary>
		/// <param name="a">
		/// 64 bit 整数
		/// </param>
		/// <param name="b">
		/// 64 bit 整数
		/// </param>
		AESIV(uint64 a, uint64 b)
		{
			v64[0] = a;
			v64[1] = b;
		}

		uint8 v8[16];

		uint16 v16[8];

		uint32 v32[4];

		uint64 v64[2];

		/// <summary>
		/// デフォルトの AES-128 初期化ベクトルを返します。
		/// </summary>
		/// <return>
		/// デフォルトの AES-128 初期化ベクトル
		/// </return>
		static AESIV Default()
		{
			return AESIV(0, 0, 0, 0);
		}
	};

	namespace Crypto2
	{
		bool IsEncrypted(const ByteArray& data);

		bool IsEncrypted(const void* data, size_t size);

		bool IsEncryptedFile(const FilePath& path);

		//////////////////////////////////////////////////////
		//
		//	オリジナルデータ(ポインタ) -> 暗号化データ
		//
		ByteArray Encrypt(const void* src, size_t srcSize, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool useMD5Check = true);

		//////////////////////////////////////////////////////
		//
		//	オリジナルデータ(ByteArray) -> 暗号化データ
		//
		ByteArray Encrypt(const ByteArray& src, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool useMD5Check = true);

		//////////////////////////////////////////////////////
		//
		//	オリジナルデータ -> 暗号化データ
		//
		template <class Type>
		inline ByteArray Encrypt(const Type& from, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool useMD5Check = true)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return Encrypt(std::addressof(from), sizeof(Type), key, iv, useMD5Check);
		}

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ポインタ) -> オリジナルデータ(ByteArray)
		//
		Optional<ByteArray> Decrypt(const void* src, size_t srcSize, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ByteArray) -> オリジナルデータ(ByteArray)
		//
		Optional<ByteArray> Decrypt(const ByteArray& src, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ポインタ) -> オリジナルデータ(ポインタ)
		//
		bool Decrypt(const void* src, size_t srcSize, void* dst, size_t dstSize, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);
	
		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ポインタ) -> オリジナルデータ
		//
		template <class Type>
		inline bool Decrypt(const void* src, size_t srcSize, Type& to, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return Decrypt(src, srcSize, std::addressof(to), sizeof(to), key, iv, md5Check);
		}

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ByteArray) -> オリジナルデータ
		//
		template <class Type>
		inline bool Decrypt(const ByteArray& src, Type& to, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return Decrypt(src.data(), src.size(), std::addressof(to), sizeof(to), key, iv, md5Check);
		}

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ポインタ) -> オリジナルデータ
		//
		template <class Type>
		inline Optional<Type> Decrypt(const void* src, size_t srcSize, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			Type result;
			return Decrypt(src, srcSize, result, key, iv, md5Check) ? result : none;
		}

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ByteArray) -> オリジナルデータ
		//
		template <class Type>
		inline Optional<Type> Decrypt(const ByteArray& src, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			
			if (auto data = Decrypt(src.data(), src.size(), key, iv, md5Check))
			{
				if (data->size() != sizeof(Type))
				{
					return none;
				}

				Type to;
				return data->read(to) ? to : Optional<Type>(none);
			}
			else
			{
				return none;
			}
		}

		//////////////////////////////////////////////////////
		//
		//	オリジナル文字列 -> 暗号化データ
		//
		ByteArray EncryptString(const String& str, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool useMD5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ポインタ) -> オリジナル文字列
		//
		bool DecryptString(const void* src, size_t srcSize, String& to, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);
		
		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ByteArray) -> オリジナル文字列
		//
		bool DecryptString(const ByteArray& from, String& to, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ポインタ) -> オリジナル文字列
		//
		Optional<String> DecryptString(const void* src, size_t srcSize, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データ(ByteArray) -> オリジナル文字列
		//
		Optional<String> DecryptString(const ByteArray& from, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);

		//////////////////////////////////////////////////////
		//
		//	オリジナルデータファイル -> 暗号化データ
		//
		ByteArray EncryptFile(const FilePath& from, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool useMD5Check = true);

		//////////////////////////////////////////////////////
		//
		//	オリジナルデータファイル -> 暗号化データファイル
		//
		bool EncryptFile(const FilePath& from, const FilePath& to, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool useMD5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データファイル -> オリジナルデータ(ByteArray)
		//
		Optional<ByteArray> DecryptFile(const FilePath& from, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);

		//////////////////////////////////////////////////////
		//
		//	暗号化データファイル -> オリジナルデータファイル
		//
		bool DecryptFile(const FilePath& from, const FilePath& to, const AES128Key& key, const AESIV& iv = AESIV::Default(), bool md5Check = true);
	}
}
