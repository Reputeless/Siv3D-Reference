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

namespace s3d
{
	/// <summary>
	/// SSE のバージョン
	/// </summary>
	enum class SSE
	{
		/// <summary>
		/// SSE2
		/// </summary>
		SSE2 = 20,
		
		/// <summary>
		/// SSE3
		/// </summary>
		SSE3 = 30,
		
		/// <summary>
		/// SSE4.1
		/// </summary>
		SSE4_1 = 41,
		
		/// <summary>
		/// SSE4.2
		/// </summary>
		SSE4_2 = 42
	};

	/// <summary>
	/// SIMD
	/// </summary>
	namespace SIMD
	{
		/// <summary>
		/// サポートされている最大の SSE のバージョンを返します。
		/// </summary>
		/// <returns>
		/// サポートされている最大の SSE のバージョン
		/// </returns>
		SSE SupportedSSE();

		/// <summary>
		/// 使用する SSE のバージョンを変更します。
		/// </summary>
		/// <param name="sse">
		/// 使用する SSE のバージョン
		/// </param>
		/// <remarks>
		/// デフォルトでは SupportedSSE() が設定されています。
		/// </remarks>
		/// <returns>
		/// 変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool SetSSE(SSE sse);
	}
}
