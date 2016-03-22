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

namespace s3d
{
	/// <summary>
	/// 線分
	/// </summary>
	struct LineInt
	{
#pragma warning(disable:4201)
		union
		{
			struct { Point begin, end; };
			struct { Point p[2]; };
		};
#pragma warning(default:4201)

		LineInt() = default;

		constexpr LineInt(int32 x0, int32 y0, int32 x1, int32 y1)
			: begin(x0, y0)
			, end(x1, y1) {}

		constexpr LineInt(const Point& p0, int32 x1, int32 y1)
			: begin(p0)
			, end(x1, y1) {}

		constexpr LineInt(int32 x0, int32 y0, const Point& p1) 
			: begin(x0, y0)
			, end(p1) {}

		constexpr LineInt(const Point& p0, const Point& p1)
			: begin(p0)
			, end(p1) {}

		constexpr bool operator == (const LineInt& line) const;

		constexpr bool operator != (const LineInt& line) const;

		LineInt& set(int32 x0, int32 y0, int32 x1, int32 y1);

		LineInt& set(const Point& p0, int32 x1, int32 y1);

		LineInt& set(int32 x0, int32 y0, const Point& p1);

		LineInt& set(const Point& p0, const Point& p1);

		LineInt& set(const LineInt& line);

		constexpr LineInt movedBy(int32 x, int32 y) const;

		constexpr LineInt movedBy(const Point& v) const;

		LineInt& moveBy(int32 x, int32 y);

		LineInt& moveBy(const Point& v);

		constexpr LineInt operator + (const Point& v) const;

		constexpr LineInt operator - (const Point& v) const;

		constexpr Point vector() const;

		constexpr LineInt reversed() const;

		double length() const;

		constexpr double lengthSq() const;

		Vec2 closest(const Vec2& pos) const;

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

		Optional<Vec2> intersectsAt(const LineInt& other) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void write(Image& image, int thickness = 1, const Color& color = Palette::Black) const;

		void writeArrow(Image& image, double thickness = 1, const Vec2& headSize = Vec2(5.0, 5.0), const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, int32 thickness = 1, const Color& color = Palette::Black) const;

		void overwriteArrow(Image& image, double thickness = 1, const Vec2& headSize = Vec2(5.0, 5.0), const Color& color = Palette::Black) const;

		const LineInt& draw(const Color& color = Palette::White) const;

		const LineInt& draw(const Color(&colors)[2]) const;

		const LineInt& draw(int32 thickness, const Color& color = Palette::White) const;

		const LineInt& draw(int32 thickness, const Color(&colors)[2]) const;

		const LineInt& drawArrow(double thickness = 1, const Vec2& headSize = Vec2(5.0, 5.0), const Color& color = Palette::White) const;

		Polygon asPolygon(double thickness = 1.0) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const LineInt& line)
	{
		return os << CharType('(') << line.p[0] << CharType(',') << line.p[1] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, LineInt& line)
	{
		CharType unused;
		return is >> unused >> line.p[0] >> unused >> line.p[1] >> unused;
	}

	/// <summary>
	/// 線分
	/// </summary>
	struct Line
	{
#pragma warning(disable:4201)
		union
		{
			struct { Vec2 begin, end; };
			struct { Vec2 p[2]; };
		};
#pragma warning(default:4201)

		Line() = default;

		constexpr Line(double x0, double y0, double x1, double y1)
			: begin(x0, y0)
			, end(x1, y1) {}

		constexpr Line(const Vec2& p0, double x1, double y1)
			: begin(p0)
			, end(x1, y1) {}

		constexpr Line(double x0, double y0, const Vec2& p1)
			: begin(x0, y0)
			, end(p1) {}

		constexpr Line(const Vec2& p0, const Vec2& p1) 
			: begin(p0)
			, end(p1) {}

		constexpr Line(const LineInt& line)
			: begin(line.begin)
			, end(line.end) {}

		Line& set(double x0, double y0, double x1, double y1);

		Line& set(const Vec2& p0, double x1, double y1);

		Line& set(double x0, double y0, const Vec2& p1);

		Line& set(const Vec2& p0, const Vec2& p1);

		Line& set(const Line& line);

		constexpr Line movedBy(double x, double y) const;

		constexpr Line movedBy(const Vec2& v) const;

		Line& moveBy(double x, double y);

		Line& moveBy(const Vec2& v);

		constexpr Line operator + (const Vec2& v) const;

		constexpr Line operator - (const Vec2& v) const;

		constexpr Vec2 vector() const;

		constexpr Line reversed() const;

		double length() const;

		constexpr double lengthSq() const;

		Vec2 closest(const Vec2& pos) const;

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

		Optional<Vec2> intersectsAt(const Line& other) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void write(Image& image, int thickness, const Color& color = Palette::Black) const;

		void writeArrow(Image& image, double thickness = 1, const Vec2& headSize = Vec2(5.0, 5.0), const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, int thickness, const Color& color = Palette::Black) const;

		void overwriteArrow(Image& image, double thickness = 1, const Vec2& headSize = Vec2(5.0, 5.0), const Color& color = Palette::Black) const;

		const Line& draw(const Color& color = Palette::White) const;

		const Line& draw(const Color(&colors)[2]) const;

		const Line& draw(double thickness, const Color& color = Palette::White) const;

		const Line& draw(double thickness, const Color(&colors)[2]) const;

		const Line& drawArrow(double thickness = 1, const Vec2& headSize = Vec2(5.0, 5.0), const Color& color = Palette::White) const;

		Polygon asPolygon(double thickness = 1.0) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Line& line)
	{
		return os << CharType('(') << line.p[0] << CharType(',') << line.p[1] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Line& line)
	{
		CharType unused;
		return is >> unused >> line.p[0] >> unused >> line.p[1] >> unused;
	}
}

# include "Line.inl"
