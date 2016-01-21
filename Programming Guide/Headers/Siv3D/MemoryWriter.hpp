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
# include "IWriter.hpp"

namespace s3d
{
	/// <summary>
	/// 書き込み用バッファ
	/// </summary>
	class MemoryWriter : public IWriter
	{
	private:

		class CMemoryWriter;

		std::shared_ptr<CMemoryWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		MemoryWriter();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~MemoryWriter() = default;

		/// <summary>
		/// 書き込みバッファを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// 書き込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		bool isOpened() const override { return true; }

		/// <summary>
		/// 書き込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 書き込み用バッファのサイズを返します。
		/// </summary>
		/// <returns>
		/// 書き込み用バッファのサイズ（バイト）
		/// </returns>
		int64 size() const override;

		/// <summary>
		/// 現在の書き込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の書き込み位置（バイト）
		/// </returns>
		int64 getPos() const override;

		/// <summary>
		/// 書き込み位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しい書き込み位置（バイト）
		/// </param>
		/// <returns>
		/// 書き込み位置の変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool setPos(int64 pos) override;

		/// <summary>
		/// バッファにデータを書き込みます。
		/// </summary>
		/// <param name="buffer">
		/// 書き込むデータ
		/// </param>
		/// <param name="size">
		/// 書き込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		size_t write(_In_reads_bytes_(size) const void* buffer, size_t size) override;

		/// <summary>
		/// バッファにデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		template <class Type>
		size_t write(const Type& src)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return write(&src, sizeof(Type));
		}

		/// <summary>
		/// バッファにデータを書き込みます。
		/// </summary>
		/// <param name="ilist">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		template <class Type>
		size_t write(std::initializer_list<Type> ilist)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");

			size_t result = 0;

			for (const auto& elem : ilist)
			{
				result += write(elem);
			}

			return result;
		}

		/// <summary>
		/// バッファにデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		template <class Type>
		size_t write(const std::vector<Type>& src)
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Type must be trivially copyable");
			return src.empty() ? 0 : write(src.data(), src.size()*sizeof(Type));
		}

		/// <summary>
		/// 書き込みバッファの先頭ポインタを返します。
		/// </summary>
		/// <remarks>
		/// 現在の書き込み位置に関係なく、バッファの先頭のポインタを返します。
		/// </remarks>
		/// <returns>
		/// 書き込みバッファの先頭ポインタ
		/// </returns>
		const uint8* data() const;

		/// <summary>
		/// バッファの内容をファイルに保存します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <remarks>
		/// 現在の書き込み位置に関係なく、バッファの内容全てを保存します。
		/// </remarks>
		/// <returns>
		/// 保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool save(const FilePath& path) const;

		/// <summary>
		/// バッファを ByteArray に変換します。
		/// </summary>
		/// <returns>
		/// バッファの内容の ByteArray
		/// </returns>
		ByteArray toByteArray();
	};
}
