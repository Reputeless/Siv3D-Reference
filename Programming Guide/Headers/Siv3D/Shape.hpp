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
# include "PointVector.hpp"
# include "Line.hpp"
# include "Rectangle.hpp"
# include "Circle.hpp"
# include "Ellipse.hpp"
# include "Triangle.hpp"
# include "Quad.hpp"
# include "RoundRect.hpp"
# include "LineString.hpp"
# include "Polygon.hpp"
# include "MultiPolygon.hpp"

namespace s3d
{
	class Shape
	{
	public:

		enum class Type
		{
			Null,
			Point,
			Vec2,
			LineInt,
			Line,
			Rect,
			RectF,
			Circle,
			Ellipse,
			Triangle,
			Quad,
			RoundRect,
			LineString,
			Polygon,
			MultiPolygon,
		};

		union
		{
			Point point;
			Vec2 vec2;
			LineInt lineInt;
			Line line;
			Rect rect;
			RectF rectF;
			Circle circle;
			Ellipse ellipse;
			Triangle triangle;
			Quad* quad;
			RoundRect roundRect;
			LineString* lineString;
			Polygon* polygon;
			MultiPolygon* multiPolygon;
		} storage;

	private:

		Type m_type = Type::Null;

	public:

		Shape() = default;

		Shape(const Shape& shape);

		Shape(Shape&& shape);

		Shape& operator = (const Shape& shape);

		Shape& operator = (Shape&& shape);

		explicit Shape(Type type);

		explicit Shape(const Point& point);

		explicit Shape(const Vec2& vec2);

		explicit Shape(const LineInt& lineInt);

		explicit Shape(const Line& line);

		explicit Shape(const Rect& rect);

		explicit Shape(const RectF& rectF);

		explicit Shape(const Circle& circle);

		explicit Shape(const Ellipse& ellipse);

		explicit Shape(const Triangle& triangle);

		explicit Shape(const Quad& quad);

		explicit Shape(const RoundRect& roundRect);

		explicit Shape(const LineString& lineString);

		explicit Shape(const Polygon& polygon);

		explicit Shape(const MultiPolygon& multiPolygon);

		explicit Shape(LineString&& lineString);

		explicit Shape(Polygon&& polygon);

		explicit Shape(MultiPolygon&& multiPolygon);

		Shape& operator = (const Point& point);

		Shape& operator = (const Vec2& vec2);

		Shape& operator = (const LineInt& lineInt);

		Shape& operator = (const Line& line);

		Shape& operator = (const Rect& rect);

		Shape& operator = (const RectF& rectF);

		Shape& operator = (const Circle& circle);

		Shape& operator = (const Ellipse& ellipse);

		Shape& operator = (const Triangle& triangle);

		Shape& operator = (const Quad& quad);

		Shape& operator = (const RoundRect& roundRect);

		Shape& operator = (const LineString& lineString);

		Shape& operator = (const Polygon& polygon);

		Shape& operator = (const MultiPolygon& multiPolygon);

		Shape& operator = (LineString&& lineString);

		Shape& operator = (Polygon&& polygon);

		Shape& operator = (MultiPolygon&& multiPolygon);

		~Shape();

		Type type() const
		{
			return m_type;
		}

		const String& Shape::typeName() const;

		bool isNull() const
		{
			return m_type == Type::Null;
		}

		void reset();

		Shape movedBy(double x, double y) const
		{
			return movedBy({ x, y });
		}

		Shape movedBy(const Vec2& v) const;

		Shape& moveBy(double x, double y)
		{
			return moveBy({ x, y });
		}

		Shape& moveBy(const Vec2& v);

		Shape operator + (const Vec2& v) const
		{
			return movedBy(v);
		}

		Shape operator - (const Vec2& v) const
		{
			return movedBy(-v);
		}

		double area() const;

		/// <summary>
		/// 図形が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 図形がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 図形の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 図形が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 図形がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 図形の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 図形の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		/// <summary>
		/// 画像に図形をブレンドして書き込みます。
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
		/// 画像に図形を上書きします。
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
		/// 画像に図形の枠をブレンドして書き込みます。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="thickness">
		/// 枠の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void writeFrame(Image& image, int thickness = 1, const Color& color = Palette::Black) const;

		/// <summary>
		/// 画像に図形の枠を上書きします。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="thickness">
		/// 枠の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void overwriteFrame(Image& image, int thickness = 1, const Color& color = Palette::Black) const;

		/// <summary>
		/// 図形を描きます。
		/// </summary>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Shape& draw(const Color& color = Palette::White) const;

		/// <summary>
		/// 長方形の枠を描きます。
		/// </summary>
		/// <param name="hickness">
		/// 枠の太さ
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		const Shape& drawFrame(double thickness = 1.0, const Color& color = Palette::White) const;

		void swap(Shape& rhs) noexcept
		{
			std::swap(m_type, rhs.m_type);
			std::swap(storage, rhs.storage);
		}
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Shape& s)
	{
		switch (s.type())
		{
		case Shape::Type::Point:
			return os << s.storage.point;
		case Shape::Type::Vec2:
			return os << s.storage.vec2;
		case Shape::Type::LineInt:
			return os << s.storage.lineInt;
		case Shape::Type::Line:
			return os << s.storage.line;
		case Shape::Type::Rect:
			return os << s.storage.rect;
		case Shape::Type::RectF:
			return os << s.storage.rectF;
		case Shape::Type::Circle:
			return os << s.storage.circle;
		case Shape::Type::Ellipse:
			return os << s.storage.ellipse;
		case Shape::Type::Triangle:
			return os << s.storage.triangle;
		case Shape::Type::Quad:
			return os << *s.storage.quad;
		case Shape::Type::RoundRect:
			return os << s.storage.roundRect;
		case Shape::Type::LineString:
			return os << *s.storage.lineString;
		case Shape::Type::Polygon:
			return os << *s.storage.polygon;
		case Shape::Type::MultiPolygon:
			return os << *s.storage.multiPolygon;
		default:
			return os;
		}
	}
}

namespace std
{
	template <class Type>
	void swap(s3d::Shape& x, s3d::Shape& y) noexcept(noexcept(x.swap(y)))
	{
		x.swap(y);
	}
}
