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
# include "Polygon.hpp"

namespace s3d
{
	/// <summary>
	/// 多角形の集合
	/// </summary>
	class MultiPolygon
	{
	private:

		struct MultiPolygonDetail;

		std::shared_ptr<MultiPolygonDetail> m_detail;

		MultiPolygon(MultiPolygonDetail&& detail);

	public:

		using iterator			= Array<Polygon>::iterator;
		using const_iterator	= Array<Polygon>::const_iterator;
		using reverse_iterator	= Array<Polygon>::reverse_iterator;	
		using const_reverse_iterator = Array<Polygon>::const_reverse_iterator;

		MultiPolygon();

		explicit MultiPolygon(const String& pts)
		{
			std::wistringstream(pts.str()) >> *this;
		}

		explicit MultiPolygon(const Array<Polygon>& polygons);

		explicit MultiPolygon(Array<Polygon>&& polygons);

		explicit operator bool() const { return !isEmpty; }

		Property_Get(bool, isEmpty) const;

		MultiPolygon clone() const;

		MultiPolygon operator + (const Vec2& v) const { return movedBy(v); }

		MultiPolygon operator - (const Vec2& v) const { return movedBy(-v); }

		MultiPolygon movedBy(double x, double y) const { return movedBy({ x, y }); }

		MultiPolygon movedBy(const Vec2& v) const;

		MultiPolygon& moveBy(double x, double y) { return moveBy({ x, y }); }

		MultiPolygon& moveBy(const Vec2& v);

		MultiPolygon rotated(double angle) const { return rotatedAt({ 0, 0 }, angle); }

		MultiPolygon rotatedAt(const Vec2& pos, double angle) const;

		double area() const;

		double perimeter() const;

		// 未実装
		//Vec2 centroid() const;

		Property_Get(size_t, num_polygons) const;

		const Array<Polygon>& polygons() const;

		const Polygon& polygon(size_t index) const;

		Property_Get(RectF, boundingRect) const;

		// 未実装
		//Polygon computeConvexHull() const;

		MultiPolygon simplified(double maxDistance = 2.0) const;

		const_iterator begin() const;

		const_iterator end() const;

		reverse_iterator rbegin();

		reverse_iterator rend();

		const_reverse_iterator rbegin() const;

		const_reverse_iterator rend() const;

		const_iterator cbegin() const;

		const_iterator cend() const;

		const_reverse_iterator crbegin() const;

		const_reverse_iterator crend() const;

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

		void write(Image& image, const Color& color = Palette::Black) const;

		void write(Image& image, int x, int y, const Color& color = Palette::Black) const;

		void write(Image& image, const Point& pos, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, int x, int y, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Point& pos, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, int x, int y, int thickness = 1, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, const Point& pos, int thickness = 1, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, int x, int y, int thickness = 1, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, const Point& pos, int thickness = 1, const Color& color = Palette::Black) const;

		void draw(const Color& color = Palette::White) const;

		void draw(double x, double y, const Color& color = Palette::White) const;

		void draw(const Vec2& pos, const Color& color = Palette::White) const;

		void drawFrame(double thickness = 1.0, const Color& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const Color& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const Color& color = Palette::White) const;

		void drawWireframe(double thickness = 1.0, const Color& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const Color& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const Color& color = Palette::White) const;

		const MultiPolygonDetail* _detail() const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const MultiPolygon& multiPolygon)
	{
		os << CharType('(');

		bool b = false;

		for (const auto& polygon : multiPolygon)
		{
			if (std::exchange(b, true))
			{
				os << CharType(',');
			}

			os << polygon;
		}

		return os << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, MultiPolygon& multiPolygon)
	{
		CharType unused;

		is >> unused;

		Array<Polygon> polygons;

		do
		{
			Polygon polygon;

			is >> polygon;

			is >> unused;

			polygons.push_back(polygon);
		}
		while (is && unused != (')'));

		multiPolygon = MultiPolygon(polygons);

		return is;
	}

	namespace Geometry2D
	{
		/// <summary>
		/// 多角形の集合を太らせます。
		/// </summary>
		/// <param name="polygon">
		/// 太らせる多角形の集合
		/// </param>
		/// <param name="distance">
		/// 太らせる幅 [>0.0]
		/// </param>
		/// <param name="round">
		/// 角を丸くするかのフラグ
		/// </param>
		/// <returns>
		/// 太らせた多角形の集合の MultiPolygon
		/// </returns>
		MultiPolygon Buffer(const MultiPolygon& polygon, double distance, bool round = true);
	}
}
