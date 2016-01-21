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
# include "Color.hpp"
# include "PointVector.hpp"
# include "Line.hpp"
# include "Geometry2D.hpp"

namespace s3d
{
	/// <summary>
	/// 長方形
	/// </summary>
	template <class SizeType, class ElementType>
	struct Rectangle
	{
#pragma warning(disable:4201)
		union
		{
			struct
			{
				/// <summary>
				/// 長方形の左上の点の X 座標
				/// </summary>
				ElementType x;

				/// <summary>
				/// 長方形の左上の点の Y 座標
				/// </summary>
				ElementType y;

				/// <summary>
				/// 長方形の幅
				/// </summary>
				ElementType w;

				/// <summary>
				/// 長方形の高さ
				/// </summary>
				ElementType h;
			};

			struct
			{
				/// <summary>
				/// 長方形の左上の点の位置
				/// </summary>
				SizeType pos;

				/// <summary>
				/// 長方形のサイズ
				/// </summary>
				SizeType size;
			};
		};

#pragma warning(default:4201)

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Rectangle() = default;

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_size">
		/// 長方形の幅と高さ
		/// </param>
		explicit constexpr Rectangle(ElementType _size)
			: x(0)
			, y(0)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(ElementType _w, ElementType _h)
			: x(0)
			, y(0)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		explicit constexpr Rectangle(SizeType _size)
			: x(0)
			, y(0)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の左上の点の X 座標
		/// </param>
		/// <param name="_h">
		/// 長方形の左上の点の Y 座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(ElementType _x, ElementType _y, ElementType _w, ElementType _h)
			: x(_x)
			, y(_y)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の左上の点の X 座標
		/// </param>
		/// <param name="_h">
		/// 長方形の左上の点の Y 座標
		/// </param>
		/// <param name="_size">
		/// 長方形の縦横の大きさ
		/// </param>
		constexpr Rectangle(ElementType _x, ElementType _y, ElementType _size)
			: x(_x)
			, y(_y)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_w">
		/// 長方形の左上の点の X 座標
		/// </param>
		/// <param name="_h">
		/// 長方形の左上の点の Y 座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(ElementType _x, ElementType _y, SizeType _size)
			: x(_x)
			, y(_y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(SizeType _pos, ElementType _size)
			: x(_pos.x)
			, y(_pos.y)
			, w(_size)
			, h(_size) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_w">
		/// 長方形の幅
		/// </param>
		/// <param name="_h">
		/// 長方形の高さ
		/// </param>
		constexpr Rectangle(SizeType _pos, ElementType _w, ElementType _h)
			: x(_pos.x)
			, y(_pos.y)
			, w(_w)
			, h(_h) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="_pos">
		/// 長方形の左上の点の座標
		/// </param>
		/// <param name="_size">
		/// 長方形の大きさ
		/// </param>
		constexpr Rectangle(SizeType _pos, SizeType _size)
			: x(_pos.x)
			, y(_pos.y)
			, w(_size.x)
			, h(_size.y) {}

		/// <summary>
		/// 長方形を作成します。
		/// </summary>
		/// <param name="r">
		/// 長方形
		/// </param>
		template <class T, class U>
		constexpr Rectangle(const Rectangle<T, U>& r)
			: x(static_cast<ElementType>(r.x))
			, y(static_cast<ElementType>(r.y))
			, w(static_cast<ElementType>(r.w))
			, h(static_cast<ElementType>(r.h)) {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Rectangle& operator *= (ElementType s) { size *= s; return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Rectangle& operator /= (ElementType s) { size /= s; return *this; }

		bool operator == (const Rectangle& r) const
		{
			return pos  == r.pos
				&& size == r.size;
		}

		bool operator != (const Rectangle& r) const
		{
			return !(*this == r);
		}

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 左上の点の新しい X 座標
		/// </param>
		/// <param name="_y">
		/// 左上の点の新しい Y 座標
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setPos(ElementType _x, ElementType _y) { pos.set(_x, _y); return *this; }

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 左上の点の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setPos(const SizeType& _pos) { pos.set(_pos); return *this; }

		/// <summary>
		/// 長方形の大きさを変更します。
		/// </summary>
		/// <param name="_w">
		/// 新しい幅
		/// </param>
		/// <param name="_h">
		/// 新しい高さ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setSize(ElementType _w, ElementType _h) { size.set(_w, _h); return *this; }

		/// <summary>
		/// 長方形の大きさを変更します。
		/// </summary>
		/// <param name="_size">
		/// 新しい大きさ
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setSize(const SizeType& _size) { size.set(_size); return *this; }

		Rectangle& set(ElementType _x, ElementType _y, ElementType _w, ElementType _h) { pos.set(_x, _y); size.set(_w, _h); return *this; }

		Rectangle& set(const SizeType& _pos, ElementType _w, ElementType _h) { pos.set(_pos); size.set(_w, _h); return *this; }

		Rectangle& set(ElementType _x, ElementType _y, const SizeType& _size) { pos.set(_x, _y); size.set(_size); return *this; }

		Rectangle& set(const SizeType& _pos, const SizeType& _size) { pos.set(_pos); size.set(_size); return *this; }

		Rectangle& set(const Rectangle& rect) { return *this = rect; }

		/// <summary>
		/// 中心位置を指定して長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 長方形の中心の新しい X 座標
		/// </param>
		/// <param name="_y">
		/// 長方形の中心の新しい Y 座標
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setCenter(ElementType _x, ElementType _y) { pos.set(_x - w / 2, _y - h / 2); return *this; }

		/// <summary>
		/// 中心位置を指定して長方形を移動させます。
		/// </summary>
		/// <param name="_x">
		/// 長方形の中心の新しい位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& setCenter(const SizeType& _pos) { pos.set(_pos - size / 2); return *this; }

		/// <summary>
		/// 移動した長方形を返します。
		/// </summary>
		/// <param name="_x">
		/// X 方向の移動量
		/// </param>
		/// <param name="_y">
		/// Y 方向の移動量
		/// </param>
		/// <returns>
		/// 移動した長方形
		/// </returns>
		constexpr Rectangle movedBy(ElementType _x, ElementType _y) const { return{ pos.movedBy(_x, _y), size }; }

		/// <summary>
		/// 移動した長方形を返します。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// 移動した長方形
		/// </returns>
		constexpr Rectangle movedBy(const SizeType& v) const { return{ pos.movedBy(v), size }; }

		/// <summary>
		/// 長方形を移動させます。
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
		Rectangle& moveBy(ElementType _x, ElementType _y) { pos.moveBy(_x, _y); return *this; }

		/// <summary>
		/// 長方形を移動させます。
		/// </summary>
		/// <param name="v">
		/// 移動量
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Rectangle& moveBy(const SizeType& v) { pos.moveBy(v); return *this; }

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="xy">
		/// 上下左右方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(ElementType xy) const
		{
			return stretched({ xy, xy });
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="_x">
		/// 左右方向の伸縮
		/// </param>
		/// <param name="_y">
		/// 上下方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(ElementType _x, ElementType _y) const
		{
			return stretched({ _x, _y });
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="xy">
		/// 左右方向と上下方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(const SizeType& xy) const
		{
			return{ pos - xy, size + xy * 2 };
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="top">
		/// 上方向の伸縮
		/// </param>
		/// <param name="right">
		/// 右方向の伸縮
		/// </param>
		/// <param name="bottom">
		/// 下方向の伸縮
		/// </param>
		/// <param name="left">
		/// 左方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle stretched(ElementType top, ElementType right, ElementType bottom, ElementType left) const
		{
			return{ pos.x - left, pos.y - top, size.x + left + right, size.y + top + bottom };
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="s">
		/// 上下左右方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr RectF scaled(double s) const
		{
			return RectF(x + w*0.5, y + h*0.5, w*s, h*s);
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="sx">
		/// 左右方向の伸縮
		/// </param>
		/// <param name="sy">
		/// 上下方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle scaled(ElementType sx, ElementType sy) const
		{
			return RectF(x + w*0.5, y + h*0.5, w*sx, h*sy);
		}

		/// <summary>
		/// 伸縮した長方形を返します。
		/// </summary>
		/// <param name="s">
		/// 左右方向と上下方向の伸縮
		/// </param>
		/// <returns>
		/// 伸縮した長方形
		/// </returns>
		constexpr Rectangle scaled(const SizeType& s) const
		{
			return RectF(x + w*0.5, y + h*0.5, w*s.x, h*s.y);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		constexpr Rectangle operator + (const SizeType& v) const { return movedBy(v); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		constexpr Rectangle operator - (const SizeType& v) const { return movedBy(-v); }

		/// <summary>
		/// 
		/// </summary>
		Property_Get(SizeType, tl) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(SizeType, tr) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(SizeType, bl) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(SizeType, br) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(SizeType, center) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(Line, top) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(Line, right) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(Line, bottom) const;

		/// <summary>
		/// 
		/// </summary>
		Property_Get(Line, left) const;

		/// <summary>
		/// 長方形の面積を返します。
		/// </summary>
		/// <returns>
		/// 長方形の面積
		/// </returns>
		constexpr ElementType area() const { return w*h; }

		/// <summary>
		/// 長方形の周の長さを返します。
		/// </summary>
		/// <returns>
		/// 長方形の周の長さ
		/// </returns>
		constexpr ElementType perimeter() const { return (w+h)*2; }

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
		/// 長方形が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 長方形がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 長方形の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 長方形が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 長方形がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 長方形の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 長方形の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		/// <summary>
		/// 画像に長方形をブレンドして書き込みます。
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
		/// 画像に長方形を上書きします。
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
		/// 画像に長方形の枠をブレンドして書き込みます。
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
		void writeFrame(Image& image, int innerThickness = 1, int outerThickness = 0, const Color& color = Palette::Black) const;

		/// <summary>
		/// 画像に長方形の枠を上書きします。
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
		void overwriteFrame(Image& image, int innerThickness = 1, int outerThickness = 0, const Color& color = Palette::Black) const;

		/// <summary>
		/// 長方形を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Rectangle& draw(const Color& color = Palette::White) const;

		/// <summary>
		/// 長方形を描きます。
		/// </summary>
		/// <param name="colors">
		/// 各頂点の色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Rectangle& draw(const Color(&colors)[4]) const;

		/// <summary>
		/// 長方形の枠を描きます。
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
		const Rectangle& drawFrame(double innerThickness = 1.0, double outerThickness = 0.0, const Color& color = Palette::White) const;

		/// <summary>
		/// 長方形の影を描きます。
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

		/// <summary>
		/// 長方形を回転させた図形を返します。
		/// </summary>
		/// <param name="angle">
		/// 回転角度（ラジアン）
		/// </param>
		/// <returns>
		/// 回転した四角形
		/// </returns>
		Quad rotated(double angle) const;

		/// <summary>
		/// 長方形を回転させた図形を返します。
		/// </summary>
		/// <param name="x">
		/// 回転軸の X 座標
		/// </param>
		/// <param name="y">
		/// 回転軸の Y 座標
		/// </param>
		/// <param name="angle">
		/// 回転角度（ラジアン）
		/// </param>
		/// <returns>
		/// 回転した四角形
		/// </returns>
		Quad rotatedAt(double _x, double _y, double angle) const;

		/// <summary>
		/// 長方形を回転させた図形を返します。
		/// </summary>
		/// <param name="pos">
		/// 回転軸の位置
		/// </param>
		/// <param name="angle">
		/// 回転角度（ラジアン）
		/// </param>
		/// <returns>
		/// 回転した四角形
		/// </returns>
		Quad rotatedAt(const Vec2& _pos, double angle) const;

		Quad shearedX(double vx) const;

		Quad shearedY(double vy) const;

		/// <summary>
		/// 長方形に Texture を貼り付けた TexturedQuad を返します。
		/// </summary>
		/// <param name="texture">
		/// 貼り付ける Texture
		/// </param>
		/// <returns>
		/// TexturedQuad
		/// </returns>
		TexturedQuad operator()(const Texture& texture) const;

		/// <summary>
		/// 長方形に TextureRegion を貼り付けた TexturedQuad を返します。
		/// </summary>
		/// <param name="textureRegion">
		/// 貼り付ける TextureRegion
		/// </param>
		/// <returns>
		/// TexturedQuad
		/// </returns>
		TexturedQuad operator()(const TextureRegion& textureRegion) const;

		/// <summary>
		/// 長方形を Polygon に変換します。
		/// </summary>
		/// <returns>
		/// 変換した Polygon
		/// </returns>
		Polygon asPolygon() const;
	};

	template <class CharType, class SizeType, class ElementType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Rectangle<SizeType, ElementType>& r)
	{
		return os << CharType('(')
			<< r.x << CharType(',')
			<< r.y << CharType(',')
			<< r.w << CharType(',')
			<< r.h << CharType(')');
	}

	template <class CharType, class SizeType, class ElementType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Rectangle<SizeType, ElementType>& r)
	{
		CharType unused;
		return is >> unused
			>> r.x >> unused
			>> r.y >> unused
			>> r.w >> unused
			>> r.h >> unused;
	}

	/// <summary>
	/// 長方形（要素が int 型）
	/// </summary>
	using Rect	= Rectangle<Point, int32>;
	
	/// <summary>
	/// 長方形（要素が double 型）
	/// </summary>
	using RectF	= Rectangle<Vec2, double>;
}

# include "Rectangle.inl"
