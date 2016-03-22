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

# ifndef _WIN64
#	include "AlignedAllocator.hpp"
#endif

namespace s3d
{
# ifdef _WIN64
	/// <summary>
	/// 動的配列
	/// </summary>
	/// <remark>
	/// std::vector&lt;bool&gt; の特殊化を回避しています。
	/// </remark>
	template <class Type>
	using Array = typename std::conditional_t<std::is_same<Type, bool>::value, BoolArray, std::vector<Type>>;
# else
	/// <summary>
	/// アライメントを考慮した std::vector
	/// </summary>
	template <class Type>
	using aligned_vector = std::vector<Type, AlignedAllocator<Type>>;

	/// <summary>
	/// アライメントを考慮した std::vector
	/// </summary>
	template <class Type, size_t Alignment = alignof(Type)>
	using Array = typename std::conditional_t<(Alignment >= 16), aligned_vector<Type>, typename std::conditional_t<std::is_same<Type, bool>::value, BoolArray, std::vector<Type>>>;
# endif
}
