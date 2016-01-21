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
# include <vector>
# include "BoolArray.hpp"

namespace s3d
{
	/// <summary>
	/// 動的配列
	/// </summary>
	/// <remark>
	/// std::vector&lt;bool&gt; の特殊化を回避しています。
	/// </remark>
	template <class Type>
	using Array = typename std::conditional_t<std::is_same<Type, bool>::value, BoolArray, std::vector<Type>>;
}
