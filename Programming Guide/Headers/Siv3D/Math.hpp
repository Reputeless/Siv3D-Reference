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

# ifndef S3D_MATH_DEFINED
#	define S3D_MATH_DEFINED
# endif

# include <cfloat>
# include <emmintrin.h>
# include "MathConstants.hpp"
# include "PointVector.hpp"
# include "Utility.hpp"

# define S3D_GENERIC_MATH1(F)\
	inline float F(float v)\
	{\
		return static_cast<float>(F(static_cast<double>(v))); \
	}\
	template <class Type>\
	inline typename std::enable_if<std::is_integral<Type>::value, double>::type F(Type v)\
	{\
		return F(static_cast<double>(v));\
	}\
	\
	template <class Type>\
	inline Vector2D<Type> F(const Vector2D<Type>& v)\
	{\
		return Vector2D<Type>(F(v.x), F(v.y)); \
	}\
	\
	template <class Type>\
	inline Vector3D<Type> F(const Vector3D<Type>& v)\
	{\
		return Vector3D<Type>(F(v.x), F(v.y), F(v.z)); \
	}\
	\
	template <class Type>\
	inline Vector4D<Type> F(const Vector4D<Type>& v)\
	{\
		return Vector4D<Type>(F(v.x), F(v.y), F(v.z), F(v.w)); \
	}

# define S3D_GENERIC_MATH2(F)\
	inline float F(float v0, float v1)\
	{\
		return static_cast<float>(F(static_cast<double>(v0), static_cast<double>(v1))); \
	}\
	\
	template <class Type>\
	inline Vector2D<Type> F(const Vector2D<Type>& v0, const Vector2D<Type>& v1)\
	{\
		return Vector2D<Type>(F(v0.x, v1.x), F(v0.y, v1.y)); \
	}\
	\
	template <class Type>\
	inline Vector3D<Type> F(const Vector3D<Type>& v0, const Vector3D<Type>& v1)\
	{\
		return Vector3D<Type>(F(v0.x, v1.x), F(v0.y, v1.y), F(v0.z, v1.z)); \
	}\
	\
	template <class Type>\
	inline Vector4D<Type> F(const Vector4D<Type>& v0, const Vector4D<Type>& v1)\
	{\
		return Vector4D<Type>(F(v0.x, v1.x), F(v0.y, v1.y), F(v0.z, v1.z), F(v0.w, v1.w)); \
	}

# define S3D_GENERIC_MATH2R(F)\
	inline float F(float v0, float& v1)\
	{\
		double tmp; \
		float result = static_cast<float>(F(static_cast<double>(v0), tmp)); \
		v1 = static_cast<float>(tmp); \
		return result; \
	}\
	\
	template <class Type>\
	inline Vector2D<Type> F(const Vector2D<Type>& v0, Vector2D<Type>& v1)\
	{\
		return Vector2D<Type>(F(v0.x, v1.x), F(v0.y, v1.y)); \
	}\
	\
	template <class Type>\
	inline Vector3D<Type> F(const Vector3D<Type>& v0, Vector3D<Type>& v1)\
	{\
		return Vector3D<Type>(F(v0.x, v1.x), F(v0.y, v1.y), F(v0.z, v1.z)); \
	}\
	\
	template <class Type>\
	inline Vector4D<Type> F(const Vector4D<Type>& v0, Vector4D<Type>& v1)\
	{\
		return Vector4D<Type>(F(v0.x, v1.x), F(v0.y, v1.y), F(v0.z, v1.z), F(v0.w, v1.w)); \
	}

# define RADIANS    (0.01745329251994329577)
# define DEGREES    (57.2957795130823208768)
const __m128d  m128dD0 = _mm_set1_pd(0.0);
const __m128d  m128dD05 = _mm_set1_pd(0.5);
const __m128d  m128dD1 = _mm_set1_pd(1.0);
const __m128d  m128dD3 = _mm_set1_pd(3.0);

namespace s3d
{
	namespace Math
	{
		/// <summary>
		/// 剰余を計算します。
		/// </summary>
		inline double Fmod(double x, double y)
		{
			return std::fmod(x, y);
		}

		/// <summary>
		/// 小数部分 [0.0,1.0) を返します。
		/// </summary>
		inline double Fraction(double x)
		{
			return (x - std::floor(x));
		}

		/// <summary>
		/// 仮数部と指数部の取得します。
		/// </summary>
		inline double Frexp(double x, double& exp)
		{
			int e;
			const double tmp = std::frexp(x, &e);
			exp = static_cast<double>(e);
			return tmp;
		}

		/// <summary>
		/// x * 2^exp を計算します。
		/// </summary>
		inline double Ldexp(double x, double exp)
		{
			return x * std::pow(2.0, exp);
		}

		/// <summary>
		/// e を底とする対数を計算します。
		/// </summary>
		inline double Log(double x)
		{
			return std::log(x);
		}

		/// <summary>
		/// 2 を底とする対数を計算します。
		/// </summary>
		inline double Log2(double x)
		{
			return std::log2(x);
		}

		/// <summary>
		/// 10 を底とする対数を計算します。
		/// </summary>
		inline double Log10(double x)
		{
			return std::log10(x);
		}

		/// <summary>
		/// 小数部と整数部に分割します。
		/// </summary>
		inline double Modf(double x, double& i)
		{
			return std::modf(x, &i);
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class Type1, class Type2>
		inline auto Pow(const Type1& v0, const Type2& v1)
		{
			return std::pow(v0, v1);
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class Type1, class Type2>
		inline Vector2D<Type1> Pow(const Vector2D<Type1>& v0, const Type2& v1)
		{
			return{ std::pow(v0.x, v1), std::pow(v0.y, v1) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class Type1, class Type2>
		inline Vector3D<Type1> Pow(const Vector3D<Type1>& v0, const Type2& v1)
		{
			return{ std::pow(v0.x, v1), std::pow(v0.y, v1), std::pow(v0.z, v1) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		template <class Type1, class Type2>
		inline Vector4D<Type1> Pow(const Vector4D<Type1>& v0, const Type2& v1)
		{
			return{ std::pow(v0.x, v1), std::pow(v0.y, v1), std::pow(v0.z, v1), std::pow(v0.w, v1) };
		}

		/// <summary>
		/// べき乗を計算します。
		/// </summary>
		inline double Pow(double x, double y)
		{
			return std::pow(x, y);
		}

		/// <summary>
		/// 符号を示す値を返します。
		/// </summary>
		inline constexpr double Sign(double x)
		{
			return x < 0.0 ? -1.0 : x > 0.0 ? 1.0 : 0.0;
		}

		/// <summary>
		/// 度数法からラジアンに変換します。
		/// </summary>
		inline constexpr double Radians(double x)
		{
			return x * (Pi / 180);
		}

		/// <summary>
		/// ラジアンから度数法に変換します。
		/// </summary>
		inline constexpr double Degrees(double x)
		{
			return x * (180 / Pi);
		}

		/// <summary>
		/// 絶対値を返します。
		/// </summary>
		template <class Type>
		inline Type Abs(Type x)
		{
			return std::abs(x);
		}

		/// <summary>
		/// 平方を計算します。
		/// </summary>
		template <class Type>
		inline constexpr Type Square(Type x)
		{
			return x * x;
		}

		/// <summary>
		/// e^x を計算します。
		/// </summary>
		inline double Exp(double x)
		{
			return std::exp(x);
		}

		/// <summary>
		/// 2^x を計算します。
		/// </summary>
		inline double Exp2(double x)
		{
			return std::pow(2.0, x);
		}

		/// <summary>
		/// 平方根の逆数を計算します。
		/// </summary>
		inline double Rsqrt(double x)
		{
			const float fx = static_cast<float>(x);
			const __m128d xx = _mm_load_sd(&x);
			__m128d xr = _mm_cvtss_sd(xx, _mm_rsqrt_ss(_mm_load_ss(&fx)));
			__m128d xt;

			xt = _mm_mul_sd(xr, xr);
			xt = _mm_mul_sd(xt, xx);
			xt = _mm_sub_sd(m128dD3, xt);
			xt = _mm_mul_sd(xt, m128dD05);
			xr = _mm_mul_sd(xr, xt);
			_mm_store_sd(&x, xr);

			return x;
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		inline double Sqrt(double x)
		{
			return std::sqrt(x);
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		inline Vec2 Sqrt(const Vec2& v)
		{
			Vec2 t(v);
			_mm_storeu_pd(&t.x, _mm_sqrt_pd(_mm_set_pd(t.y, t.x)));
			return t;
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		inline Vec3 Sqrt(const Vec3& v)
		{
			Vec3 t(v);
			_mm_storeu_pd(&t.x, _mm_sqrt_pd(_mm_set_pd(t.y, t.x)));
			t.z = std::sqrt(t.z);
			return t;
		}

		/// <summary>
		/// 平方根を計算します。
		/// </summary>
		inline Vec4 Sqrt(const Vec4& v)
		{
			Vec4 t(v);
			_mm_storeu_pd(&t.x, _mm_sqrt_pd(_mm_set_pd(t.y, t.x)));
			_mm_storeu_pd(&t.z, _mm_sqrt_pd(_mm_set_pd(t.w, t.z)));
			return t;
		}

		/// <summary>
		/// x 以上の最小の整数を返します。
		/// </summary>
		inline double Ceil(double x)
		{
			return std::ceil(x);
		}

		/// <summary>
		/// x 以下の最大の整数を返します。
		/// </summary>
		inline double Floor(double x)
		{
			return std::floor(x);
		}

		/// <summary>
		/// 四捨五入した値を返します。
		/// </summary>
		inline double Round(double x)
		{
			return std::round(x);
		}

		/// <summary>
		/// 成分を [_min,_max] に制限した値を返します。
		/// </summary>
		inline constexpr Float2 Clamp(const Float2& v, float _min, float _max)
		{
			return{ s3d::Clamp(v.x, _min, _max), s3d::Clamp(v.y, _min, _max) };
		}

		/// <summary>
		/// 成分を [_min,_max] に制限した値を返します。
		/// </summary>
		inline constexpr Float3 Clamp(const Float3& v, float _min, float _max)
		{
			return{ s3d::Clamp(v.x, _min, _max), s3d::Clamp(v.y, _min, _max), s3d::Clamp(v.z, _min, _max) };
		}

		/// <summary>
		/// 成分を [_min,_max] に制限した値を返します。
		/// </summary>
		inline constexpr Float4 Clamp(const Float4& v, float _min, float _max)
		{
			return{ s3d::Clamp(v.x, _min, _max), s3d::Clamp(v.y, _min, _max), s3d::Clamp(v.z, _min, _max), s3d::Clamp(v.w, _min, _max) };
		}

		/// <summary>
		/// 成分を [_min,_max] に制限した値を返します。
		/// </summary>
		inline Vec2 Clamp(const Vec2& v, double _min, double _max)
		{
			const __m128d x0 = _mm_loadu_pd(&v.x);
			const __m128d xmin = _mm_set1_pd(_min);
			const __m128d xmax = _mm_set1_pd(_max);
			Vec2 t;
			_mm_storeu_pd(&t.x, _mm_min_pd(_mm_max_pd(xmin, x0), xmax));
			return t;
		}

		/// <summary>
		/// 成分を [_min,_max] に制限した値を返します。
		/// </summary>
		inline Vec3 Clamp(const Vec3& v, double _min, double _max)
		{
			const __m128d x0 = _mm_loadu_pd(&v.x);
			const __m128d x1 = _mm_set_sd(v.z);
			const __m128d xmin = _mm_set1_pd(_min);
			const __m128d xmax = _mm_set1_pd(_max);
			Vec3 t;
			_mm_storeu_pd(&t.x, _mm_min_pd(_mm_max_pd(xmin, x0), xmax));
			_mm_store_sd(&t.z, _mm_min_sd(_mm_max_sd(xmin, x1), xmax));
			return t;
		}

		/// <summary>
		/// 成分を [_min,_max] に制限した値を返します。
		/// </summary>
		inline Vec4 Clamp(const Vec4& v, double _min, double _max)
		{
			const __m128d x0 = _mm_loadu_pd(&v.x);
			const __m128d x1 = _mm_loadu_pd(&v.z);
			const __m128d xmin = _mm_set1_pd(_min);
			const __m128d xmax = _mm_set1_pd(_max);
			Vec4 t;
			_mm_storeu_pd(&t.x, _mm_min_pd(_mm_max_pd(xmin, x0), xmax));
			_mm_storeu_pd(&t.z, _mm_min_pd(_mm_max_pd(xmin, x1), xmax));
			return t;
		}

		/// <summary>
		/// 成分を [0, 1] に制限した値を返します。
		/// </summary>
		inline constexpr double Saturate(double x)
		{
			return	1.0 < x ? 1.0 : x < 0.0 ? 0.0 : x;
		}

		/// <summary>
		/// 成分を [0, 1] に制限した値を返します。
		/// </summary>
		inline Vec2 Saturate(const Vec2& v)
		{
			const __m128d x0 = _mm_loadu_pd(&v.x);
			Vec2 t;
			_mm_storeu_pd(&t.x, _mm_min_pd(_mm_max_pd(m128dD0, x0), m128dD1));
			return t;
		}

		/// <summary>
		/// 成分を [0, 1] に制限した値を返します。
		/// </summary>
		inline Vec3 Saturate(const Vec3& v)
		{
			const __m128d x0 = _mm_loadu_pd(&v.x);
			const __m128d x1 = _mm_set_sd(v.z);
			Vec3 t;
			_mm_storeu_pd(&t.x, _mm_min_pd(_mm_max_pd(m128dD0, x0), m128dD1));
			_mm_store_sd(&t.z, _mm_min_sd(_mm_max_sd(m128dD0, x1), m128dD1));
			return t;
		}

		/// <summary>
		/// 成分を [0, 1] に制限した値を返します。
		/// </summary>
		inline Vec4 Saturate(const Vec4& v)
		{
			const __m128d x0 = _mm_loadu_pd(&v.x);
			const __m128d x1 = _mm_loadu_pd(&v.z);
			Vec4 t;
			_mm_storeu_pd(&t.x, _mm_min_pd(_mm_max_pd(m128dD0, x0), m128dD1));
			_mm_storeu_pd(&t.z, _mm_min_pd(_mm_max_pd(m128dD0, x1), m128dD1));
			return v;
		}

		/// <summary>
		/// アークコサインを計算します。
		/// </summary>
		inline double Acos(double x)
		{
			return std::acos(x);
		}

		/// <summary>
		/// アークサインを計算します。
		/// </summary>
		inline double Asin(double x)
		{
			return std::asin(x);
		}

		/// <summary>
		/// アークタンジェントを計算します。
		/// </summary>
		inline double Atan(double x)
		{
			return std::atan(x);
		}

		/// <summary>
		/// vy/vx のアークタンジェントを計算します。
		/// </summary>
		inline double Atan2(double vy, double vx)
		{
			return std::atan2(vy, vx);
		}

		/// <summary>
		/// コサインを計算します。
		/// </summary>
		inline double Cos(double x)
		{
			return std::cos(x);
		}

		/// <summary>
		/// ハイパボリックコサインを計算します。
		/// </summary>
		inline double Cosh(double x)
		{
			return std::cosh(x);
		}

		/// <summary>
		/// サインを計算します。
		/// </summary>
		inline double Sin(double x)
		{
			return std::sin(x);
		}

		/// <summary>
		/// ハイパボリックサインを計算します。
		/// </summary>
		inline double Sinh(double x)
		{
			return std::sinh(x);
		}

		/// <summary>
		/// タンジェントを計算します。
		/// </summary>
		inline double Tan(double x)
		{
			return std::tan(x);
		}

		/// <summary>
		/// ハイパボリックタンジェントを計算します。
		/// </summary>
		inline double Tanh(double x)
		{
			return std::tanh(x);
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		inline double Normalize(double x)
		{
			return x ? 1.0 : 0.0;
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		template <class Type>
		inline Vector2D<Type> Normalize(const Vector2D<Type>& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		template <class Type>
		inline Vector3D<Type> Normalize(const Vector3D<Type>& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// 正規化したベクトルを返します。
		/// </summary>
		template <class Type>
		inline Vector4D<Type> Normalize(const Vector4D<Type>& v)
		{
			return v.normalized();
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline float Smoothstep(float min, float max, float x)
		{
			if (x <= min)
			{
				return 0.0f;
			}
			else if (max <= x)
			{
				return 1.0f;
			}

			x = (x - min) / (max - min);

			return x*x*(3.0f - 2.0f*x);
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline double Smoothstep(double min, double max, double x)
		{
			if (x <= min)
			{
				return 0.0;
			}
			else if (max <= x)
			{
				return 1.0;
			}

			x = (x - min) / (max - min);

			return x*x*(3.0 - 2.0*x);
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline float Smoothstep(float x)
		{
			if (x <= 0.0f)
			{
				return 0.0f;
			}
			else if (1.0f <= x)
			{
				return 1.0f;
			}

			return x*x*(3.0f - 2.0f*x);
		}

		/// <summary>
		/// エルミート補間した結果を返します。
		/// </summary>
		inline double Smoothstep(double x)
		{
			if (x <= 0.0)
			{
				return 0.0;
			}
			else if (1.0 <= x)
			{
				return 1.0;
			}

			return x*x*(3.0 - 2.0*x);
		}

		S3D_GENERIC_MATH2(Fmod);
		S3D_GENERIC_MATH1(Fraction);
		S3D_GENERIC_MATH2R(Frexp);
		S3D_GENERIC_MATH2(Ldexp);
		S3D_GENERIC_MATH1(Log);
		S3D_GENERIC_MATH1(Log2);
		S3D_GENERIC_MATH1(Log10);
		S3D_GENERIC_MATH2R(Modf);
		S3D_GENERIC_MATH2(Pow);
		S3D_GENERIC_MATH1(Sign);
		S3D_GENERIC_MATH1(Radians);
		S3D_GENERIC_MATH1(Degrees);
		S3D_GENERIC_MATH1(Exp);
		S3D_GENERIC_MATH1(Exp2);
		S3D_GENERIC_MATH1(Rsqrt);
		S3D_GENERIC_MATH1(Sqrt);
		S3D_GENERIC_MATH1(Ceil);
		S3D_GENERIC_MATH1(Floor);
		S3D_GENERIC_MATH1(Round);
		S3D_GENERIC_MATH1(Saturate);
		S3D_GENERIC_MATH1(Acos);
		S3D_GENERIC_MATH1(Asin);
		S3D_GENERIC_MATH1(Atan);
		S3D_GENERIC_MATH2(Atan2);
		S3D_GENERIC_MATH1(Cos);
		S3D_GENERIC_MATH1(Cosh);
		S3D_GENERIC_MATH1(Sin);
		S3D_GENERIC_MATH1(Sinh);
		S3D_GENERIC_MATH1(Tan);
		S3D_GENERIC_MATH1(Tanh);
	}
}

# undef RADIANS
# undef DEGREES
# undef M_LOG2E
# undef S3D_GENERIC_MATH1
# undef S3D_GENERIC_MATH2
# undef S3D_GENERIC_MATH2R
