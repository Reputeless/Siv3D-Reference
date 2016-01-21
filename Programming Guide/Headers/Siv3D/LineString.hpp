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
# include "Array.hpp"
# include "Utility.hpp"
# include "PointVector.hpp"
# include "Line.hpp"

namespace s3d
{
	/// <summary>
	/// 連続した複数の線分
	/// </summary>
	class LineString
	{
	private:

		Array<Vec2> m_points;

	public:

		using iterator = Array<Vec2>::iterator;
		using const_iterator = Array<Vec2>::const_iterator;
		using reverse_iterator = Array<Vec2>::reverse_iterator;
		using const_reverse_iterator = Array<Vec2>::const_reverse_iterator;

		LineString() = default;

		explicit LineString(const String& pts)
		{
			std::wistringstream(pts.str()) >> *this;
		}

		explicit LineString(const Array<Point>& pts)
		{
			m_points.reserve(pts.size());

			for (const auto& p : pts)
			{
				m_points.push_back(p);
			}
		}

		explicit LineString(const Array<Vec2>& pts)
			: m_points(pts) {}

		explicit LineString(Array<Vec2>&& pts)
			: m_points(std::move(pts)) {}

		LineString(size_t count, const Vec2& value)
			: m_points(count, value) {}

		LineString(const Vec2* pts, size_t size)
			: m_points(pts, pts+size) {}

		template <class InputIt>
		LineString(InputIt first, InputIt last)
			: m_points(first, last) {}

		explicit LineString(std::initializer_list<Vec2> il)
			: LineString(il.begin(), il.size()) {}

		LineString(const LineString& lines)
			: m_points(lines.m_points) {}

		LineString(LineString && lines)
			: m_points(std::move(lines.m_points)) {}

		LineString& operator = (const LineString& lines) { m_points = lines.m_points; return *this; }

		LineString& operator = (LineString && lines) { m_points = std::move(lines.m_points); return *this; }

		void assign(size_t count, const Vec2& value)
		{
			m_points.assign(count, value);
		}

		void assign(const Vec2* pts, size_t size)
		{
			m_points.assign(pts, pts + size);
		}

		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{
			m_points.assign(first, last);
		}

		void clear() { m_points.clear(); }

		void shrink_to_fit() { m_points.shrink_to_fit(); }

		void release() { clear(); shrink_to_fit(); }

		void reserve(size_t size) { m_points.reserve(size); }

		void resize(size_t size) { m_points.resize(size); }

		void resize(size_t size, const Vec2& value) { m_points.resize(size, value); }

		const Vec2& point(size_t index) const
		{
			return m_points[index];
		}

		Vec2& point(size_t index)
		{
			return m_points[index];
		}

		Line line(size_t index) const
		{
			return{ m_points[index], m_points[index + 1] };
		}

		void* data()
		{
			return &m_points[0];
		}

		const void* data() const
		{
			return &m_points[0];
		}

		Array<Vec2>& getArray() { return m_points; }

		const Array<Vec2>& getArray() const { return m_points; }

		iterator begin() { return m_points.begin(); }

		const_iterator begin() const { return m_points.begin(); }

		const_iterator cbegin() const { return m_points.cbegin(); }

		iterator end() { return m_points.end(); }

		const_iterator end() const { return m_points.end(); }

		const_iterator cend() const { return m_points.cend(); }

		reverse_iterator rbegin() { return m_points.rbegin(); }

		const_reverse_iterator rbegin() const { return m_points.rbegin(); }

		const_reverse_iterator crbegin() const { return m_points.crbegin(); }

		reverse_iterator rend() { return m_points.rend(); }

		const_reverse_iterator rend() const { return m_points.rend(); }

		const_reverse_iterator crend() const { return m_points.crend(); }

		iterator insert(const_iterator pos, const Vec2& value)
		{
			return m_points.insert(pos, value);
		}

		iterator insert(const_iterator pos, size_t count, const Vec2& value)
		{
			return m_points.insert(pos, count, value);
		}

		template <class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last)
		{
			return m_points.insert(pos, first, last);
		}

		iterator erase(const_iterator pos)
		{
			return m_points.erase(pos);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			return m_points.erase(first, last);
		}

		void push_back(const Vec2& value)
		{
			m_points.push_back(value);
		}

		void pop_back()
		{
			m_points.pop_back();
		}

		size_t size() const { return m_points.size(); }

		void swap(LineString& lines)
		{
			m_points.swap(lines.m_points);
		}

		LineString clone() const
		{
			return *this;
		}

		LineString movedBy(double x, double y) const { return movedBy({ x, y }); }

		LineString movedBy(const Vec2& v) const;

		LineString& moveBy(double x, double y) { return moveBy({ x, y }); }

		LineString& moveBy(const Vec2& v);

		Property_Get(bool, isEmpty) const { return m_points.empty(); }

		Property_Get(size_t, num_points) const { return m_points.size(); }

		Property_Get(size_t, num_lines) const { return isEmpty ? 0 : m_points.size() - 1; }

		LineString substr(size_t offset) const
		{
			return LineString(begin() + offset, end());
		}

		LineString substr(size_t offset, size_t count) const
		{
			return LineString(begin() + offset, begin() + offset + count);
		}

		LineString toCatmullRomSpline(bool isClosedCurve = false, int32 interpolation = 24) const;

		RectF calculateBoundingRect() const;

		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		void write(Image& image, const Color& color = Palette::Black, bool isClosed = false) const;

		void write(Image& image, int32 thickness, const Color& color = Palette::Black, bool isClosed = false) const;

		void overwrite(Image& image, const Color& color = Palette::Black, bool isClosed = false) const;

		void overwrite(Image& image, int32 thickness, const Color& color = Palette::Black, bool isClosed = false) const;

		void writeCatmullRomSpline(Image& image, int32 thickness = 1, const Color& color = Palette::Black, bool isClosed = false, int32 interpolation = 24) const;

		void overwriteCatmullRomSpline(Image& image, int32 thickness = 1, const Color& color = Palette::Black, bool isClosed = false, int32 interpolation = 24) const;

		void draw(const Color& color = Palette::White, bool isClosedCurve = false) const;

		void draw(double thickness, const Color& color = Palette::White, bool isClosedCurve = false) const;

		void drawCatmullRomSpline(double thickness = 1.0, const Color& color = Palette::White, bool isClosedCurve = false, int interpolation = 24) const;

		Polygon asPolygon(double thickness = 1.0, bool isClosed = false) const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const LineString& lineStr)
	{
		os << CharType('(');

		bool b = false;

		for (const auto& point : lineStr)
		{
			if (std::exchange(b, true))
			{
				os << CharType(',');
			}

			os << point;
		}

		return os << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, LineString& lineStr)
	{
		lineStr.clear();

		CharType unused;

		is >> unused;

		for (;;)
		{
			Vec2 v;

			is >> v;

			if (!is)
			{
				break;
			}

			is >> unused;

			lineStr.push_back(v);

			if (unused == L')')
			{
				break;
			}
		}

		return is;
	}
}
