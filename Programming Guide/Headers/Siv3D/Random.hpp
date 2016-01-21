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
# include <type_traits>
# include <random>
# include <initializer_list>
# include "Array.hpp"
# include "MathConstants.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Color.hpp"
# include "HSV.hpp"
# include "RNG.hpp"
# include "Distribution.hpp"
# include "Circle.hpp"

namespace s3d
{
	/// <summary>
	/// グローバルな乱数エンジンにアクセスします。
	/// </summary>
	/// <returns>
	/// グローバルな乱数エンジンへの参照
	/// </returns>
	RNG& DefaultRNG();

	/// <summary>
	/// グローバルな乱数エンジンのシードを再設定します。
	/// </summary>
	/// <param name="seed">
	/// シード
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	inline void Reseed(uint32 seed)
	{
		DefaultRNG().seed(seed);
	}

	/// <summary>
	/// [0.0-1.0] の範囲の乱数を返します。
	/// </summary>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// [0.0-1.0] の範囲の乱数
	/// </returns>
	double Random();

	/// <summary>
	/// 指定した型と範囲の乱数を返します。
	/// </summary>
	/// <param name="min">
	/// 生成したい乱数の最小値
	/// </param>
	/// <param name="max">
	/// 生成したい乱数の最大値
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// 指定した型と範囲の乱数
	/// </returns>
	template <class Type>
	inline Type Random(Type min, Type max)
	{
		return UniformDistribution<Type>(min, max)(DefaultRNG());
	}

	/// <summary>
	/// 0 から、指定した範囲までの乱数を返します。
	/// </summary>
	/// <param name="max">
	/// 生成したい乱数の最大値
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// 0 以上 max 以下の乱数
	/// </returns>
	template <class Type>
	inline Type Random(Type max)
	{
		return Random<Type>(0, max);
	}

	/// <summary>
	/// 指定した型と範囲の乱数を返します。
	/// </summary>
	/// <param name="min">
	/// 生成したい乱数の最小値
	/// </param>
	/// <param name="max">
	/// 生成したい乱数の最大値
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// 指定した型と範囲の乱数
	/// </returns>
	template <>
	inline wchar Random<wchar>(wchar min, wchar max)
	{
		return static_cast<wchar>(UniformDistribution<uint32>(min, max)(DefaultRNG()));
	}

	/// <summary>
	/// 2 値の乱数を返します。
	/// </summary>
	/// <param name="p">
	/// true を返す確率 [0.0, 1.0]
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// 確率 p でtrue, 確率 (1-p) で false
	/// </returns>
	inline bool RandomBool(double p)
	{
		return std::bernoulli_distribution(p)(DefaultRNG());
	}

	/// <summary>
	/// リストの中からランダムに値を選択します。
	/// </summary>
	/// <param name="ilist">
	/// 値のリスト
	/// </param>
	/// <remarks>
	/// グローバルな乱数エンジンを使用します。
	/// </remarks>
	/// <returns>
	/// リストの中からランダムに選択された値
	/// </returns>
	template <class Iterator>
	inline auto RandomSelect(Iterator begin, Iterator end)
	{
		assert(begin != end);
		std::advance(begin, Random(std::distance(begin, end) - 1));
		return *begin;
	}

	template <class Range>
	inline auto RandomSelect(Range&& range)
	{
		return RandomSelect(std::begin(std::forward<Range>(range)), std::end(std::forward<Range>(range)));
	}

	template <class Type>
	inline Type RandomSelect(std::initializer_list<Type> ilist)
	{
		return RandomSelect(std::begin(ilist), std::end(ilist));
	}

	/// <summary>
	/// コンテナの中身をシャッフルします。
	/// </summary>
	/// <param name="c">
	/// コンテナ
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	template <class Container>
	inline void Shuffle(Container& c)
	{
		std::shuffle(c.begin(), c.end(), RNG{});
	}

	/// <summary>
	/// 指定した範囲の値をシャッフルします。
	/// </summary>
	/// <param name="first">
	/// 範囲の開始位置
	/// </param>
	/// <param name="last">
	/// 範囲の終了位置
	/// </param>
	/// <returns>
	/// なし
	/// </returns>
	template <class RandomIt>
	inline void Shuffle(RandomIt first, RandomIt last)
	{
		std::shuffle(first, last, RNG{});
	}

	inline Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax)
	{
		Point p;
		p.x = Random(xMinMax.first, xMinMax.second);
		p.y = Random(yMinMax.first, yMinMax.second);
		return p;
	}

	inline Point RandomPoint(const Rect& rect)
	{
		Point p;
		p.x = Random(rect.x, rect.x + rect.w);
		p.y = Random(rect.y, rect.y + rect.h);
		return p;
	}

	inline Point RandomPoint(int32 xMax, int32 yMax)
	{
		return RandomPoint({ 0, xMax }, { 0, yMax });
	}

	inline Vec2 RandomVec2()
	{
		const double theta = Random(Math::TwoPi);
		return{ std::cos(theta), std::sin(theta) };
	}

	inline Vec2 RandomVec2(double length)
	{
		return RandomVec2() * length;
	}

	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax)
	{
		Vec2 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		return v;
	}

	inline Vec2 RandomVec2(double xMax, double yMax)
	{
		return RandomVec2({ 0.0, xMax }, { 0.0, yMax });
	}

	inline Vec2 RandomVec2(const Circle& circle)
	{
		const double r = sqrt(Random()) * circle.r;
		const double theta = Random(Math::TwoPi);
		return circle.center.movedBy(std::cos(theta)*r, std::sin(theta)*r);
	}

	inline Vec2 RandomVec2(const RectF& rect)
	{
		Vec2 p;
		p.x = Random(rect.x, rect.x + rect.w);
		p.y = Random(rect.y, rect.y + rect.h);
		return p;
	}

	inline Vec3 RandomVec3()
	{
		const double theta = Random(Math::Pi);
		const double phi = Random(Math::TwoPi);
		const double s = std::sin(theta);
		return{ s * std::cos(phi), s * std::sin(phi), std::cos(theta) };
	}

	inline Vec3 RandomVec3(double length)
	{
		return RandomVec3() * length;
	}

	inline Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax
		)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	inline Vec3 RandomVec3(double xMax, double yMax, double zMax)
	{
		return RandomVec3({ 0.0, xMax }, { 0.0, yMax }, { 0.0, zMax });
	}

	inline Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax
		)
	{
		Vec4 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		v.w = Random(wMinMax.first, wMinMax.second);
		return v;
	}

	inline Vec4 RandomVec4(double xMax, double yMax, double zMax, double wMax)
	{
		return RandomVec4({ 0.0, xMax }, { 0.0, yMax }, { 0.0, zMax }, { 0.0, wMax });
	}

	inline Color RandomColor()
	{
		return HueToColor(Random(360.0));
	}

	inline Color RandomColorH(double s, double v)
	{
		return HSV(Random(360.0), s, v);
	}

	inline Color RandomColorS(double h, double v)
	{
		return HSV(h, Random(), v);
	}

	inline Color RandomColorV(double h, double s)
	{
		return HSV(h, s, Random());
	}
}
