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
# include "Rectangle.hpp"
# include "Polygon.hpp"

namespace s3d
{
	/// <summary>
	/// 角丸長方形
	/// </summary>
	struct RoundRect
	{
#pragma warning(disable:4201)
		union
		{
			struct { RectF rect; double r; };
			struct { double x, y, w, h, r; };
		};
#pragma warning(default:4201)

		RoundRect() = default;

		explicit RoundRect(const String& str)
		{
			std::wistringstream(str.str()) >> *this;
		}

		RoundRect(double _x, double _y, double _w, double _h, double _r)
			: rect(_x, _y, _w, _h)
			, r(_r) {}

		RoundRect(const Vec2& pos, const Vec2& size, double _r)
			: rect(pos, size)
			, r(_r) {}

		RoundRect(const RectF& _rect, double _r)
			: rect(_rect)
			, r(_r) {}

		Property_Get(Vec2, center) const
		{
			return rect.center;
		}

		RoundRect& set(double _x, double _y, double _w, double _h, double _r)
		{
			rect.set(_x, _y, _w, _h);
			r = _r;
			return *this;
		}

		RoundRect& set(const Vec2& pos, const Vec2& size, double _r)
		{
			rect.set(pos, size);
			r = _r;
			return *this;
		}

		RoundRect& set(const RectF& _rect, double _r)
		{
			rect.set(_rect);
			r = _r;
			return *this;
		}

		RoundRect& set(const RoundRect& roundRect)
		{
			return *this = roundRect;
		}

		RoundRect& setPos(double _x, double _y) { rect.setPos(_x, _y); return *this; }

		RoundRect& setPos(const Vec2& _pos) { rect.setPos(_pos); return *this; }

		RoundRect& setSize(double _w, double _h) { rect.setSize(_w, _h); return *this; }

		RoundRect& setSize(const Vec2& _size) { rect.setSize(_size); return *this; }

		RoundRect& setCenter(double _x, double _y) { rect.setCenter(_x, _y); return *this; }

		RoundRect& setCenter(const Vec2& _pos) { rect.setCenter(_pos); return *this; }

		RoundRect movedBy(double _x, double _y) const { return movedBy({ _x, _y }); }

		RoundRect movedBy(const Vec2& v) const
		{
			return{ rect.movedBy(v), r };
		}

		RoundRect& moveBy(double _x, double _y) { return moveBy({ _x, _y }); }

		RoundRect& moveBy(const Vec2& v)
		{
			rect.moveBy(v);

			return *this;
		}

		RoundRect stretched(double xy) const { return{ rect.stretched(xy), r }; }

		RoundRect stretched(double _x, double _y) const { return{ rect.stretched(_x, _y), r }; }

		RoundRect stretched(const Vec2& xy) const { return{ rect.stretched(xy), r }; }

		RoundRect operator + (const Vec2& v) const { return movedBy(v); }

		RoundRect operator - (const Vec2& v) const { return movedBy(-v); }

		double area() const;

		double perimeter() const;

		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape>
		bool contains(const Shape& shape) const
		{
			return Geometry2D::Within(shape, *this);
		}

		/// <summary>
		/// 角丸長方形が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 角丸長方形がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 角丸長方形の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 角丸長方形が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 角丸長方形がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 角丸長方形の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 角丸長方形の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		const RoundRect& draw(const Color& color = Palette::White) const;

		void drawFlatBottom(const Color& color = Palette::White) const;

		const RoundRect& drawFrame(double innerThickness = 1.0, double outerThickness = 0.0, const Color& color = Palette::White) const;

		/// <summary>
		/// 角丸長方形の影を描きます。
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

		Polygon asPolygon() const;

		Polygon asPolygonFlatBottom() const;

		Array<Vec2> getOuterVertices(double offset = 0.0) const;

		Array<Vec2> getOuterVerticesFlatBottom(double offset = 0.0) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const RoundRect& roundRect)
	{
		return	os << CharType('(')
			<< roundRect.x << CharType(',')
			<< roundRect.y << CharType(',')
			<< roundRect.w << CharType(',')
			<< roundRect.h << CharType(',')
			<< roundRect.r << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, RoundRect& roundRect)
	{
		CharType unused;
		return	is >> unused
			>> roundRect.x >> unused
			>> roundRect.y >> unused
			>> roundRect.w >> unused
			>> roundRect.h >> unused
			>> roundRect.r >> unused;
	}
}
