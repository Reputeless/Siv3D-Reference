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
# include <memory>
# include <initializer_list>
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Triangle.hpp"
# include "PropertyMacro.hpp"

namespace s3d
{
	class PolygonHoles
	{
	private:

		const Array<Vec2>* m_begin;

		const Array<Vec2>* m_end;

	public:

		PolygonHoles(const Array<Vec2>* _begin, const Array<Vec2>* _end)
			: m_begin(_begin)
			, m_end(_end) {}

		bool empty() const
		{
			return !m_begin;
		}

		size_t size() const
		{
			return m_end - m_begin;
		}

		const Array<Vec2>& operator[](unsigned index) const
		{
			return m_begin[index];
		}

		const Array<Vec2>* begin() const
		{
			return m_begin;
		}

		const Array<Vec2>* end() const
		{
			return m_end;
		}
	};

	/// <summary>
	/// 多角形
	/// </summary>
	class Polygon
	{
	private:

		struct PolygonDetail;

		std::shared_ptr<PolygonDetail> m_detail;

		Polygon(PolygonDetail&& detail);

	public:

		Polygon();

		explicit Polygon(const String& pts)
		{
			std::wistringstream(pts.str()) >> *this;
		}

		explicit Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes = {});

		explicit Polygon(const Vec2* outer, size_t size, const Array<Array<Vec2>>& holes = {});

		Polygon(std::initializer_list<Vec2> outer)
			: Polygon(outer.begin(), outer.size()) {}

		Polygon(const Array<Vec2>& outer, const Array<Array<Vec2>>& holes, const Array<uint32>& indices, const RectF& bound);

		explicit operator bool() const { return !isEmpty; }

		Property_Get(bool, isEmpty) const;

		Polygon clone() const;

		Polygon movedBy(double x, double y) const { return movedBy({ x, y }); }

		Polygon movedBy(const Vec2& v) const;

		Polygon& moveBy(double x, double y) { return moveBy({ x, y }); }

		Polygon& moveBy(const Vec2& v);

		Polygon scaled(double s) const { return scaled({ s, s }); }

		Polygon scaled(double sx, double sy) const { return scaled({ sx, sy }); }

		Polygon scaled(const Vec2& s) const;

		Polygon& scale(double s) { return scale({ s, s }); }

		Polygon& scale(double sx, double sy) { return scale({ sx, sy }); }

		Polygon& scale(const Vec2& s);

		Polygon& addHole(const Array<Vec2>& hole);

		Polygon& addHoles(const Array<Array<Vec2>>& holes);

		Polygon operator + (const Vec2& v) const;

		Polygon operator - (const Vec2& v) const { return *this + (-v); }

		Polygon rotated(double angle) const { return rotatedAt({ 0, 0 }, angle); }

		Polygon rotatedAt(const Vec2& pos, double angle) const;

		double area() const;

		double perimeter() const;

		Vec2 centroid() const;

		Property_Get(size_t, num_vertices) const;

		Property_Get(size_t, num_indices) const;

		Property_Get(size_t, num_triangles) const { return num_indices / 3; }

		Property_Get(size_t, num_holes) const;

		bool hasHoles() const;

		const Array<Vec2>& outer() const;

		Array<Array<Vec2>> inners() const;

		PolygonHoles holes() const;

		PolygonTriangles triangles() const;

		Vec2 vertex(size_t index) const;

		uint32 index(size_t index) const;

		Array<uint32> indices() const;

		Triangle triangle(size_t index) const;

		Property_Get(RectF, boundingRect) const;

		Polygon computeConvexHull() const;

		/// <summary>
		/// ポリゴンの頂点数を削減します。
		/// </summary>
		/// <param name="maxDistance">
		/// 
		/// </param>
		/// <returns>
		/// 頂点数が削減されたポリゴン
		/// </returns>
		Polygon simplified(double maxDistance = 2.0) const;

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
		/// 多角形が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 多角形がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 多角形の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 多角形が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 多角形がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 多角形の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 多角形の上にマウスカーソルがあるかを示します。
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

		void draw(const Array<Color>& colors) const;

		void draw(double x, double y, const Color& color = Palette::White) const;
		
		void draw(double x, double y, const Array<Color>& colors) const;

		void draw(const Vec2& pos, const Color& color = Palette::White) const;

		void draw(const Vec2& pos, const Array<Color>& colors) const;

		void drawFrame(double thickness = 1.0, const Color& color = Palette::White) const;

		void drawFrame(double x, double y, double thickness = 1.0, const Color& color = Palette::White) const;

		void drawFrame(const Vec2& pos, double thickness = 1.0, const Color& color = Palette::White) const;

		void drawWireframe(double thickness = 1.0, const Color& color = Palette::White) const;

		void drawWireframe(double x, double y, double thickness = 1.0, const Color& color = Palette::White) const;

		void drawWireframe(const Vec2& pos, double thickness = 1.0, const Color& color = Palette::White) const;

		const PolygonDetail* _detail() const;
	};

	class Polygon_triangle_iterator
		: public std::iterator<std::input_iterator_tag, Triangle>
	{
	private:

		const Polygon* m_pPolygon = nullptr;

		size_t m_index;

	public:

		Polygon_triangle_iterator(
			const Polygon* pPolygon,
			size_t index = 0
			)
			: m_pPolygon(pPolygon)
			, m_index(index) {}

		Polygon_triangle_iterator& operator++()
		{
			++m_index;

			return *this;
		}

		Triangle operator * () const
		{
			return m_pPolygon->triangle(m_index);
		}

		bool operator == (const Polygon_triangle_iterator& iterator)
		{
			return  m_pPolygon == iterator.m_pPolygon && m_index == iterator.m_index;
		}

		bool operator != (const Polygon_triangle_iterator& iterator)
		{
			return !(m_index == iterator.m_index);
		}
	};

	class PolygonTriangles
	{
	private:

		const Polygon* m_pPolygon = nullptr;

	public:

		PolygonTriangles(const Polygon* pPolygon)
			: m_pPolygon(pPolygon) {}

		const Polygon_triangle_iterator begin() const
		{
			return Polygon_triangle_iterator(m_pPolygon, 0);
		}

		const Polygon_triangle_iterator end() const
		{
			return Polygon_triangle_iterator(m_pPolygon, m_pPolygon->num_triangles);
		}
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Polygon& polygon)
	{
		os << CharType('(');

		os << CharType('(');

		bool b = false;

		for (const auto& point : polygon.outer())
		{
			if (std::exchange(b, true))
			{
				os << CharType(',');
			}

			os << point;
		}

		os << CharType(')');

		if (!polygon.holes().empty())
		{
			os << CharType(',');

			os << CharType('(');

			b = false;

			for (const auto& hole : polygon.holes())
			{
				if (std::exchange(b, true))
				{
					os << CharType(',');

					os << CharType('(');
				}

				bool b2 = false;

				for (const auto& point : hole)
				{
					if (std::exchange(b2, true))
					{
						os << CharType(',');
					}

					os << point;
				}

				os << CharType(')');
			}
		}

		return os << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Polygon& polygon)
	{
		CharType unused;

		is >> unused >> unused;

		Array<Vec2> pts;

		for (;;)
		{
			Vec2 v;

			is >> v;

			if (!is)
			{
				break;
			}

			is >> unused;

			pts.push_back(v);

			if (unused == CharType(')'))
			{
				break;
			}
		}

		is >> unused;

		if (unused != CharType(','))
		{
			polygon = Polygon(pts);

			return is;
		}

		Array<Array<Vec2>> holes;

		is >> unused;

		for (;;)
		{
			Array<Vec2> hole;

			for (;;)
			{
				Vec2 v;

				is >> v;

				if (!is)
				{
					break;
				}

				is >> unused;

				hole.push_back(v);

				if (unused == CharType(')'))
				{
					holes.push_back(std::move(hole));

					break;
				}
			}

			if (!is)
			{
				break;
			}

			is >> unused;

			if (unused != CharType(','))
			{
				polygon = Polygon(pts, holes);

				return is;
			}
			else
			{
				is >> unused;
			}
		}

		return is;
	}

	namespace Geometry2D
	{
		/// <summary>
		/// 十字形の Polygon を返します。
		/// </summary>
		/// <param name="r">
		/// 一番離れた辺から中心点までの距離
		/// </param>
		/// <param name="width">
		/// 十字形を構成する 2 線分の太さ
		/// </param>
		/// <param name="center">
		/// 十字形の中心座標
		/// </param>
		/// <returns>
		/// 十字形の頂点配列
		/// </returns>
		Polygon CreatePlus(double r, double width, const Vec2& center = Vec2(0, 0));

		/// <summary>
		/// 正 N 角形の Polygon を返します。
		/// </summary>
		/// <param name="n">
		/// 頂点の数
		/// </param>
		/// <param name="r">
		/// 外接円の半径
		/// </param>
		/// <param name="angle">
		/// 時計方向への回転角度[ラジアン], 0 のとき頂点が 12 時の位置と重なる
		/// </param>
		/// <param name="center">
		/// 正 N 角形の中心座標
		/// </param>
		/// <returns>
		/// 正 N 角形の Polygon, n &lt; 3 の場合は空の Polygon
		/// </returns>
		Polygon CreateNgon(uint32 n, double r, double angle = 0.0, const Vec2& center = { 0,0 });

		/// <summary>
		/// 五光星 (☆) の Polygon を返します。
		/// </summary>
		/// <param name="r">
		/// 外接円の半径
		/// </param>
		/// <param name="angle">
		/// 時計方向への回転角度[ラジアン], 0 のとき頂点が 12 時の位置と重なる
		/// </param>
		/// <param name="center">
		/// 五光星の中心座標
		/// </param>
		/// <returns>
		/// 五光星の Polygon
		/// </returns>
		Polygon CreateStar(double r, double angle = 0.0, const Vec2& center = { 0,0 });

		/// <summary>
		/// 星形図形の Polygon を返します。
		/// </summary>
		/// <param name="n">
		/// 光の数（五光星 ☆ の場合、5）
		/// </param>
		/// <param name="rOuter">
		/// 中心から外側の頂点までの距離
		/// </param>
		/// <param name="rInner">
		/// 中心から内側の頂点までの距離
		/// </param>
		/// <param name="angle">
		/// 時計方向への回転角度[ラジアン], 0 のとき頂点が 12 時の位置と重なる
		/// </param>
		/// <param name="center">
		/// 図形の中心座標
		/// </param>
		/// <returns>
		/// 星形図形の Polygon, n &lt; 2 の場合は空の Polygon
		/// </returns>
		Polygon CreateNStar(uint32 n, double rOuter, double rInner, double angle = 0.0, const Vec2& center = { 0,0 });

		/// <summary>
		/// 多角形を太らせます。
		/// </summary>
		/// <param name="polygon">
		/// 太らせる多角形
		/// </param>
		/// <param name="distance">
		/// 太らせる幅 [&gt;0.0]
		/// </param>
		/// <param name="round">
		/// 角を丸くするかのフラグ
		/// </param>
		/// <returns>
		/// 太らせた多角形の Polygon
		/// </returns>
		Polygon Buffer(const Polygon& polygon, double distance, bool round = true);
	}
}
