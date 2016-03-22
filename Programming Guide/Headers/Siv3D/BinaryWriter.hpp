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
# include <array>
# include "Fwd.hpp"
# include "IWriter.hpp"
# include "Array.hpp"
# include "ByteArray.hpp"
# include "FileSystem.hpp"

namespace s3d
{
	/// <summary>
	/// 書き込み用バイナリファイル
	/// </summary>
	class BinaryWriter : public IWriter
	{
	private:

		class CBinaryWriter;

		std::shared_ptr<CBinaryWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		BinaryWriter();

		/// <summary>
		/// 書き込み用のバイナリファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="mode">
		/// オープンモード
		/// </param>
		explicit BinaryWriter(const FilePath& path, OpenMode mode = OpenMode::Trunc);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~BinaryWriter() = default;

		/// <summary>
		/// 書き込み用のバイナリファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="mode">
		/// オープンモード
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, OpenMode mode = OpenMode::Trunc);

		/// <summary>
		/// バイナリファイルの書き込みバッファをフラッシュします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void flush();

		/// <summary>
		/// バイナリファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// バイナリファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const override;

		/// <summary>
		/// バイナリファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 現在開いているファイルの内容を消去し、書き込み位置を先頭に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear();

		/// <summary>
		/// バイナリファイルのサイズを返します。
		/// </summary>
		/// <returns>
		/// バイナリファイルのサイズ（バイト）
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
		/// 書き込み位置を終端に移動します。
		/// </summary>
		/// <returns>
		/// 新しい書き込み位置（バイト）
		/// </returns>
		int64 seekEnd();

		/// <summary>
		/// ファイルにデータを書き込みます。
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
		/// ファイルにデータを書き込みます。
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
		/// ファイルにデータを書き込みます。
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
		/// ファイルにデータを書き込みます。
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
		/// ファイルにデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		size_t write(const ByteArray& src)
		{
			return src.size() ? write(src.data(), static_cast<size_t>(src.size())) : 0;
		}

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		FilePath path() const;
	};
}
