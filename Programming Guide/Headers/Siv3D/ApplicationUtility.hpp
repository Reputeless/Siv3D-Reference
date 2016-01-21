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
# include "Format.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 画面にテキストを表示します。
	/// </summary>
	/// <param name="text">
	/// テキスト
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	void Print(const String& text);

	/// <summary>
	/// 画面にテキストを表示し、改行します。
	/// </summary>
	/// <param name="text">
	/// テキスト
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	void Println(const String& text);

	/// <summary>
	/// 画面にデータを表示します。
	/// </summary>
	/// <param name="args">
	/// テキスト
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	template <class ... Args>
	inline void Print(const Args& ... args)
	{
		Print(Format(args...));
	}

	/// <summary>
	/// 画面にデータを表示し、改行します。
	/// </summary>
	/// <param name="args">
	/// テキスト
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	template <class ... Args>
	inline void Println(const Args& ... args)
	{
		Println(Format(args...));
	}

	/// <summary>
	/// 画面に表示したデータを消去します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	void ClearPrint();

	class PutText
	{
	private:

		String m_text;

		Vec2 m_pos{ 0, 0 };

		bool m_at = false;

	public:

		template <class ... Args>
		explicit PutText(Args&& ... args)
			: m_text(Format(std::forward<Args>(args)...)) {}

		~PutText();

		void from(const Vec2& pos);

		void from(double x, double y);

		void at(const Vec2& pos);

		void at(double x, double y);
	};

	/// <summary>
	/// 何らかのキーが入力されるまで待機します。
	/// </summary>
	/// <remarks>
	/// 待機の間、GUI は更新されません。
	/// </remarks>
	void WaitKey();
}
