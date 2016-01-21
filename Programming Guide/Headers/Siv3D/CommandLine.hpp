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

namespace s3d
{
	/// <summary>
	/// コマンドライン
	/// </summary>
	/// <remarks>
	/// コマンドライン入力を取得する機能を提供します。
	/// </remarks>
	namespace CommandLine
	{
		/// <summary>
		/// コマンドライン入力を取得します。
		/// </summary>
		/// <returns>
		/// コマンドライン入力
		/// </returns>
		const Array<String>& Get();
	}
}
