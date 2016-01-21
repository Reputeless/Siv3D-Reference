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
# include "PropertyMacro.hpp"
# include "PointVector.hpp"
# include "Color.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// 円
	/// </summary>
	struct Circle
	{
#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// 円の中心の X 座標
				/// </summary>
				double x;

				/// <summary>
				/// 円の中心の Y 座標
				/// </summary>
				double y;

				/// <summary>
				/// 円の半径
				/// </summary>
				double r;
			};

			struct
			{
				/// <summary>
				/// 円の中心
				/// </summary>
				Vec2 center;

				/// <summary>
				/// 円の半径
				/// </summary>
				double r;
			};
		};

#pragma warning(default:4201)

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Circle() = default;

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		explicit constexpr Circle(double _r)
			: x(0.0)
			, y(0.0)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_x">
		/// 円の中心の X 座標
		/// </param>
		/// <param name="_y">
		/// 円の中心の Y 座標
		/// </param>
		constexpr Circle(double _x, double _y)
			: x(_x)
			, y(_y)
			, r(0.0) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="_x">
		/// 円の中心の X 座標
		/// </param>
		/// <param name="_y">
		/// 円の中心の Y 座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(double _x, double _y, double _r)
			: x(_x)
			, y(_y)
			, r(_r) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="p">
		/// 円の中心の座標
		/// </param>
		explicit constexpr Circle(const Vec2& p)
			: x(p.x)
			, y(p.y)
			, r(0.0) {}

		/// <summary>
		/// 円を作成します。
		/// </summary>
		/// <param name="p">
		/// 円の中心の座標
		/// </param>
		/// <param name="_r">
		/// 円の半径
		/// </param>
		constexpr Circle(const Vec2& p, double _r)
			: x(p.x)
			, y(p.y)
			, r(_r) {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Circle& setPos(double _x, double _y) { x = _x; y = _y; return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Circle& setPos(const Vec2& _pos) { center = _pos; return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Circle& setSize(double _r) { r = _r; return *this; }

		Circle& set(double _x, double _y, double _r) { x = _x; y = _y; r = _r;  return *this; }

		Circle& set(const Vec2& _pos, double _r) { center = _pos; r = _r;  return *this; }

		Circle& set(const Circle& circle) { return *this = circle; }

		/// <summary>
		/// 移動した円を返します。
		/// </summary>
		/// <param name="_x">
		/// X 方向の移動量
		/// </param>
		/// <param name="_y">
		/// Y 方向の移動量
		/// </param>
		/// <returns>
		/// 移動した円
		/// </returns>
		constexpr Circle movedBy(double _x, double _y) const { return{ center.movedBy(_x, _y), r }; }

		/// <summary>
		/// 移動した円を返します。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// 移動した円
		/// </returns>
		constexpr Circle movedBy(const Vec2& v) const { return{ center.movedBy(v), r }; }

		/// <summary>
		/// 円を移動させます。
		/// </summary>
		/// <param name="_x">
		/// X 方向の移動量
		/// </param>
		/// <param name="_y">
		/// Y 方向の移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Circle& moveBy(double _x, double _y) { center.moveBy(_x, _y); return *this; }

		/// <summary>
		/// 円を移動させます。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Circle& moveBy(const Vec2& v) { center.moveBy(v); return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		constexpr Circle operator + (const Vec2& v) const { return{ center + v, r }; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		constexpr Circle operator - (const Vec2& v) const { return{ center - v, r }; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		constexpr Circle stretched(double s) const { return{ center, r + s }; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		constexpr Circle scaled(double s) const { return{ center, r * s }; }

		/// <summary>
		/// 円の面積を返します。
		/// </summary>
		/// <returns>
		/// 円の面積
		/// </returns>
		constexpr double area() const { return r * r * Math::Pi; }

		/// <summary>
		/// 円周の長さを返します。
		/// </summary>
		/// <returns>
		/// 円周の長さ
		/// </returns>
		constexpr double perimeter() const { return r * 2 * Math::Pi; }

		/// <summary>
		/// 他の図形と交差しているかを調べます。
		/// </summary>
		/// <param name="shape">
		/// 他の図形
		/// </param>
		/// <returns>
		/// 交差している場合 true, それ以外の場合は false
		/// </returns>
		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		/// <summary>
		/// 他の図形を包括しているかを調べます。
		/// </summary>
		/// <param name="shape">
		/// 他の図形
		/// </param>
		/// <returns>
		/// 包括している場合 true, それ以外の場合は false
		/// </returns>
		template <class Shape>
		bool contains(const Shape& shape) const
		{
			return Geometry2D::Within(shape, *this);
		}

		/// <summary>
		/// 円が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 円がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 円の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 円が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 円がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 円の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 円の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		/// <summary>
		/// 画像に円をブレンドして書き込みます。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void write(Image& image, const Color& color = Palette::Black) const;

		/// <summary>
		/// 画像に円を上書きします。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void overwrite(Image& image, const Color& color = Palette::Black) const;

		/// <summary>
		/// 画像に円の枠をブレンドして書き込みます。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeFrame(Image& image, int32 innerThickness = 1, int32 outerThickness = 0, const Color& color = Palette::Black) const;

		/// <summary>
		/// 画像に円の枠を上書きします。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void overwriteFrame(Image& image, int32 innerThickness = 1, int32 outerThickness = 0, const Color& color = Palette::Black) const;

		// 未実装
		//void writePie(Image& image, double startAngle, double angle, const Color& color = Palette::Black) const;

		/// <summary>
		/// 画像に円の扇形を上書きします。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="startAngle">
		/// 開始角度
		/// </param>
		/// <param name="angle">
		/// 角度
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void overwritePie(Image& image, double startAngle, double angle, const Color& color = Palette::Black) const;

		/// <summary>
		/// 円を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& draw(const Color& color = Palette::White) const;

		/// <summary>
		/// 円を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawAsTexture(const Color& color = Palette::White) const;

		/// <summary>
		/// 円を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawAsPolygon(const Color& color = Palette::White) const;

		/// <summary>
		/// 円の枠を描きます。
		/// </summary>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Circle& drawFrame(double innerThickness = 1.0, double outerThickness = 0.0, const Color& color = Palette::White) const;
		
		/// <summary>
		/// 扇形を描きます。
		/// </summary>
		/// <param name="startAngle">
		/// 開始角度
		/// </param>
		/// <param name="angle">
		/// 角度
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void drawPie(double startAngle, double angle, const Color& color = Palette::White) const;

		/// <summary>
		/// 弧を描きます。
		/// </summary>
		/// <param name="startAngle">
		/// 開始角度
		/// </param>
		/// <param name="angle">
		/// 角度
		/// </param>
		/// <param name="innerThickness">
		/// 内側の太さ
		/// </param>
		/// <param name="outerThickness">
		/// 外側の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void drawArc(double startAngle, double angle, double innerThickness = 1.0, double outerThickness = 0.0, const Color& color = Palette::White) const;

		/// <summary>
		/// 円の影を描きます。
		/// </summary>
		/// <param name="offset">
		/// 影の移動量（ピクセル）
		/// </param>
		/// <param name="blurRadius">
		/// 影のぼかしの大きさ（ピクセル）
		/// </param>
		/// <param name="spread">
		/// 長方形の広がり（ピクセル）
		/// </param>
		/// <param name="color">
		/// 影の色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void drawShadow(const Vec2& offset, double blurRadius, double spread = 0.0, const ColorF& color = ColorF(0.0, 0.5)) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Circle& c)
	{
		return os << CharType('(') << c.x << CharType(',') << c.y << CharType(',') << c.r << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Circle& c)
	{
		CharType unused;
		return is >> unused >> c.x >> unused >> c.y >> unused >> c.r >> unused;
	}
}
