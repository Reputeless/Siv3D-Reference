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
# include "Array.hpp"
# include "String.hpp"
# include "Optional.hpp"

namespace s3d
{
	/// <summary>
	/// シリアル通信
	/// </summary>
	class Serial
	{
	private:

		class CSerial;

		std::shared_ptr<CSerial> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Serial();

		/// <summary>
		/// シリアルポートを開きます。
		/// </summary>
		/// <param name="port">
		/// COM ポート番号
		/// </param>
		/// <param name="baudRate">
		/// 転送レート
		/// </param>
		explicit Serial(int32 port, int32 baudRate = 9600);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Serial();

		/// <summary>
		/// シリアルポートを開きます。
		/// </summary>
		/// <param name="port">
		/// COM ポート番号
		/// </param>
		/// <param name="baudRate">
		/// 転送レート
		/// </param>
		/// <returns>
		/// ポートのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool setup(int32 port, int32 baudRate = 9600);

		/// <summary>
		/// シリアルデバイスに接続されているかを返します。
		/// </summary>
		/// <returns>
		/// 接続されている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// シリアルデバイスに接続されているかを返します。
		/// </summary>
		/// <returns>
		/// 接続されている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		bool hasError() const;

		/// <summary>
		/// シリアルポートから読み込めるデータのサイズを取得します。
		/// </summary>
		/// <returns>
		/// シリアルポートから読み込めるデータのサイズ（バイト）
		/// </returns>
		size_t available();

		/// <summary>
		/// シリアルの読み込みバッファの内容を消去します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clearInput();

		/// <summary>
		/// シリアルの書き込みバッファの内容を消去します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clearOutput();

		/// <summary>
		/// シリアルのバッファの内容を消去します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear();
		
		bool lookahead(_Out_writes_bytes_all_(size) void* dst, size_t size);

		bool lookahead(_Out_writes_bytes_all_(size) void* dst, size_t offset, size_t size);

		template <class Type>
		_Check_return_ bool lookahead(Type& to) const
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return lookahead(std::addressof(to), sizeof(Type));
		}

		/// <summary>
		/// シリアルデバイスから指定したサイズのデータを読み込みます。
		/// </summary>
		/// <param name="dst">
		/// 読み込み先
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合は true, size が available() 未満、もしくは読み込みに失敗した場合は false
		/// </returns>
		bool read(_Out_writes_bytes_all_(size) void* dst, size_t size);

		/// <summary>
		/// シリアルデバイスからデータを読み込みます。
		/// </summary>
		/// <param name="dst">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功した場合は true, 読み込みに失敗した場合は false
		/// </returns>
		template <class Type>
		_Check_return_ bool read(Type& to)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return read(std::addressof(to), sizeof(Type));
		}

		bool skip(size_t size);

		/// <summary>
		/// シリアルデバイスにデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <param name="size">
		/// 書き込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 書き込みに成功したら true, それ以外の場合は false
		/// </returns>
		bool write(_In_reads_bytes_(size) const void* src, size_t size);

		/// <summary>
		/// シリアルデバイスにデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 書き込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type>
		uint32 write(const Type& src)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return write(std::addressof(src), sizeof(Type));
		}

		/// <summary>
		/// シリアルデバイスに文字列を書き込みます。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <remarks>
		/// 文字列は UTF-8 エンコードされます。
		/// </remarks>
		/// <returns>
		/// 書き込みに成功したら true, それ以外の場合は false
		/// </returns>
		bool write(const String& str);

		/// <summary>
		/// シリアルデバイスに文字列と改行を書き込みます。
		/// </summary>
		/// <param name="str">
		/// 書き込む文字列
		/// </param>
		/// <remarks>
		/// 文字列は UTF-8 エンコードされます。
		/// </remarks>
		/// <returns>
		/// 書き込みに成功したら true, それ以外の場合は false
		/// </returns>
		bool writeln(const String& str);

		/// <summary>
		/// シリアルデバイスとの接続を終了します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();
	};

	/// <summary>
	/// シリアルデバイスの情報
	/// </summary>
	struct SerialDeveiceInfo
	{
		/// <summary>
		/// シリアルデバイスの名前
		/// </summary>
		String name;

		/// <summary>
		/// COM ポート番号
		/// </summary>
		int32 port = 0;
	};

	/// <summary>
	/// シリアル通信
	/// </summary>
	/// <remarks>
	/// シリアル通信の機能を提供します。
	/// </remarks>
	namespace SerialManager
	{
		/// <summary>
		/// PC に接続されているシリアルデバイスの一覧を取得します。
		/// </summary>
		/// <returns>
		/// PC に接続されているシリアルデバイスの一覧
		/// </returns>
		Array<SerialDeveiceInfo> Enumerate();
	}
}
