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
# include "PointVector.hpp"
# include "Vector3D.hpp"
# include "Vector4D.hpp"
# include "Color.hpp"

namespace s3d
{
	struct has_lerp_impl
	{
		template <class Type>
		static auto check(int) -> decltype(std::declval<const Type&>().lerp(std::declval<const Type&>(), 0.0), std::true_type());

		template <class Type>
		static auto check(...)->std::false_type;
	};

	template <class Type>
	struct has_lerp
		: decltype(has_lerp_impl::check<Type>(0)) {};

	namespace Math
	{
		/// <summary>
		/// 線形補間した結果を返します。
		/// </summary>
		template <class T, class U, class V, typename std::enable_if<has_lerp<T>::value>::type* = nullptr>
		constexpr auto Lerp(const T& v1, const U& v2, V f)
		{
			return v1.lerp(v2, f);
		}

		/// <summary>
		/// 線形補間した結果を返します。
		/// </summary>
		template <class T, class U, class V, typename std::enable_if<!has_lerp<T>::value>::type* = nullptr>
		constexpr auto Lerp(const T& v1, const U& v2, V f)
		{
			return v1 + (v2 - v1) * f;
		}
	}
}
