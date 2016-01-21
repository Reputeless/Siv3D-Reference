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
# include "Array.hpp"
# include "Format.hpp"
# include "IReader.hpp"

namespace s3d
{
	/// <summary>
	/// 読み込み用バッファ
	/// </summary>
	class ByteArray : public IReader
	{
	private:

		class CByteArray;

		std::shared_ptr<CByteArray> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		ByteArray();

		explicit ByteArray(const FilePath& path);

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="ptr">
		/// コピーするデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// コピーするデータのサイズ（バイト）
		/// </param>
		ByteArray(const void* ptr, int64 size);

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// コピーするデータ
		/// </param>
		explicit ByteArray(const Array<uint8>& data);

		/// <summary>
		/// データをムーブして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// ムーブするデータ
		/// </param>
		explicit ByteArray(Array<uint8>&& data);

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="ptr">
		/// コピーするデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// コピーするデータのサイズ（バイト）
		/// </param>
		/// <returns>
		/// バッファの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool create(const void* ptr, int64 size);

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// コピーするデータ
		/// </param>
		/// <returns>
		/// バッファの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool create(const Array<uint8>& data);

		/// <summary>
		/// データをムーブして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// ムーブするデータ
		/// </param>
		/// <returns>
		/// バッファの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool create(Array<uint8>&& data);

		/// <summary>
		/// 読み込みバッファを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// 読み込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// 使用可能な場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const override;

		/// <summary>
		/// 読み込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// 使用可能な場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 読み込み用バッファのサイズを返します。
		/// </summary>
		/// <returns>
		/// 読み込み用バッファのサイズ（バイト）
		/// </returns>
		int64 size() const override;

		/// <summary>
		/// 現在の読み込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の読み込み位置（バイト）
		/// </returns>
		int64 getPos() const override;

		/// <summary>
		/// 読み込み位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しい読み込み位置（バイト）
		/// </param>
		/// <returns>
		/// 読み込み位置の変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool setPos(int64 pos) override;

		/// <summary>
		/// バッファを読み飛ばし、読み込み位置を変更します。
		/// </summary>
		/// <param name="offset">
		/// 読み飛ばすサイズ（バイト）
		/// </param>
		/// <returns>
		/// 新しい読み込み位置
		/// </returns>
		int64 skip(int64 offset) override;

		/// <summary>
		/// 読み込みバッファの先頭ポインタを返します。
		/// </summary>
		/// <remarks>
		/// 現在の読み込み位置に関係なく、バッファの先頭のポインタを返します。
		/// </remarks>
		/// <returns>
		/// 読み込みバッファの先頭ポインタ
		/// </returns>
		const uint8* data() const;

		/// <summary>
		/// 読み込みバッファの参照を返します。
		/// </summary>
		/// <remarks>
		/// 現在の読み込み位置に関係なく、バッファの全体の参照を返します。
		/// </remarks>
		/// <returns>
		/// 読み込みバッファの参照
		/// </returns>
		const Array<uint8>& asArray() const;

		/// <summary>
		/// バッファからデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 read(_Out_writes_bytes_all_(size) void* buffer, int64 size) override;

		/// <summary>
		/// バッファからデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="pos">
		/// 先頭から数えた読み込み開始位置（バイト）
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 read(_Out_writes_bytes_all_(size) void* buffer, int64 pos, int64 size) override;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="to">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type>
		_Check_return_ bool read(Type& to)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "ByteArray::read(): Type must be trivially copyable");

			return IReader::read(to);
		}

		/// <summary>
		/// 読み込み位置を変更しないデータ読み込みをサポートしているかを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		bool supportsLookahead() const override { return true; }

		/// <summary>
		/// 読み込み位置を変更しないでデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 lookahead(_Out_writes_bytes_all_(size) void* buffer, int64 size) const override;

		/// <summary>
		/// 読み込み位置を変更しないでデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="pos">
		/// 先頭から数えた読み込み開始位置（バイト）
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 lookahead(_Out_writes_bytes_all_(size) void* buffer, int64 pos, int64 size) const override;

		/// <summary>
		/// 読み込み位置を変更しないでデータを読み込みます。
		/// </summary>
		/// <param name="to">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type>
		_Check_return_ bool lookahead(Type& to)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "ByteArray::lookahead(): Type must be trivially copyable");

			return IReader::lookahead(to);
		}

		/// <summary>
		/// バッファの内容をファイルに保存します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <remarks>
		/// 現在の読み込み位置に関係なく、バッファの内容全てを保存します。
		/// </remarks>
		/// <returns>
		/// 保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool save(const FilePath& path) const;
	};

	inline std::wostream & operator << (std::wostream& os, const ByteArray& data)
	{
		os << L'{';

		bool b = false;

		for (const auto& n : data.asArray())
		{
			if (std::exchange(b, true))
			{
				os << L',';
			}

			if (n <= 0x0F)
			{
				os << L'0';
			}

			os << ToHex(n);
		}

		return os << L'}';
	}
}
