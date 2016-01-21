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

namespace s3d
{
	/// <summary>
	/// 二次元図形の作成と幾何計算
	/// </summary>
	namespace Geometry2D
	{
		bool Intersect(const Point& a, const Point&		b);
		bool Intersect(const Point& a, const Rect&		b);
		bool Intersect(const Point& a, const RectF&		b);
		bool Intersect(const Point& a, const LineInt&	b);

		bool Intersect(const Vec2& a, const Vec2&			b);
		bool Intersect(const Vec2& a, const RectF&			b);
		bool Intersect(const Vec2& a, const Circle&			b);
		bool Intersect(const Vec2& a, const Ellipse&		b);
		bool Intersect(const Vec2& a, const Line&			b);
		bool Intersect(const Vec2& a, const Triangle&		b);
		bool Intersect(const Vec2& a, const Quad&			b);
		bool Intersect(const Vec2& a, const RoundRect&		b);
		bool Intersect(const Vec2& a, const Polygon&		b);
		bool Intersect(const Vec2& a, const MultiPolygon&	b);
		bool Intersect(const Vec2& a, const LineString&		b);

		bool Intersect(const Rect& a, const Point&		b);
		bool Intersect(const Rect& a, const Rect&		b);
		bool Intersect(const Rect& a, const RectF&		b);

		bool Intersect(const RectF& a, const Point&			b);
		bool Intersect(const RectF& a, const Vec2&			b);
		bool Intersect(const RectF& a, const Rect&			b);
		bool Intersect(const RectF& a, const RectF&			b);
		bool Intersect(const RectF& a, const Circle&		b);
		bool Intersect(const RectF& a, const Ellipse&		b);
		bool Intersect(const RectF& a, const Line&			b);
		bool Intersect(const RectF& a, const Triangle&		b);
		bool Intersect(const RectF& a, const Quad&			b);
		bool Intersect(const RectF& a, const RoundRect&		b);
		bool Intersect(const RectF& a, const Polygon&		b);
		bool Intersect(const RectF& a, const MultiPolygon&	b);
		bool Intersect(const RectF& a, const LineString&	b);

		bool Intersect(const Circle& a, const Vec2&				b);
		bool Intersect(const Circle& a, const RectF&			b);
		bool Intersect(const Circle& a, const Circle&			b);
		//bool Intersect(const Circle& a, const Ellipse&		b);
		bool Intersect(const Circle& a, const Line&				b);
		bool Intersect(const Circle& a, const Triangle&			b);
		bool Intersect(const Circle& a, const Quad&				b);
		bool Intersect(const Circle&  a, const RoundRect&		b);
		bool Intersect(const Circle& a, const Polygon&			b);
		bool Intersect(const Circle& a, const MultiPolygon&		b);
		bool Intersect(const Circle& a, const LineString&		b);

		bool Intersect(const Ellipse& a, const Vec2&			b);
		bool Intersect(const Ellipse& a, const RectF&			b);
		//bool Intersect(const Ellipse& a, const Circle&		b);
		//bool Intersect(const Ellipse& a, const Ellipse&		b);
		bool Intersect(const Ellipse& a, const Line&			b);
		//bool Intersect(const Ellipse& a, const Triangle&		b);
		//bool Intersect(const Ellipse& a, const Quad&			b);
		//bool Intersect(const Ellipse&  a, const RoundRect&	b);
		//bool Intersect(const Ellipse& a, const Polygon&		b);
		//bool Intersect(const Ellipse&  a, const MultiPolygon&	b);
		bool Intersect(const Ellipse& a, const LineString&	b);

		bool Intersect(const LineInt& a, const LineInt& b);

		bool Intersect(const Line& a, const Vec2&		b);
		bool Intersect(const Line& a, const RectF&		b);
		bool Intersect(const Line& a, const Circle&		b);
		bool Intersect(const Line& a, const Ellipse&	b);
		bool Intersect(const Line& a, const Line&		b);
		bool Intersect(const Line& a, const Triangle&	b);
		bool Intersect(const Line& a, const Quad&		b);
		bool Intersect(const Line&  a, const RoundRect&	b);
		bool Intersect(const Line& a, const Polygon&	b);
		bool Intersect(const Line& a, const MultiPolygon& b);
		bool Intersect(const Line& a, const LineString& b);

		bool Intersect(const Triangle& a, const Vec2&		b);
		bool Intersect(const Triangle& a, const RectF&		b);
		bool Intersect(const Triangle& a, const Circle&		b);
		//bool Intersect(const Triangle& a, const Ellipse&	b);
		bool Intersect(const Triangle& a, const Line&		b);
		bool Intersect(const Triangle& a, const Triangle&	b);
		bool Intersect(const Triangle& a, const Quad&		b);
		bool Intersect(const Triangle&  a, const RoundRect&	b);
		bool Intersect(const Triangle& a, const Polygon&	b);
		bool Intersect(const Triangle& a, const MultiPolygon& b);
		bool Intersect(const Triangle& a, const LineString& b);

		bool Intersect(const Quad& a, const Vec2&		b);
		bool Intersect(const Quad& a, const RectF&		b);
		bool Intersect(const Quad& a, const Circle&		b);
		//bool Intersect(const Quad& a, const Ellipse&	b);
		bool Intersect(const Quad& a, const Line&		b);
		bool Intersect(const Quad& a, const Triangle&	b);
		bool Intersect(const Quad& a, const Quad&		b);
		bool Intersect(const Quad&  a, const RoundRect&	b);
		bool Intersect(const Quad& a, const Polygon&	b);
		bool Intersect(const Quad& a, const MultiPolygon& b);
		bool Intersect(const Quad& a, const LineString& b);

		bool Intersect(const RoundRect& a, const Vec2&		b);
		bool Intersect(const RoundRect& a, const RectF&		b);
		bool Intersect(const RoundRect& a, const Circle&	b);
		//bool Intersect(const RoundRect& a, const Ellipse&	b);
		bool Intersect(const RoundRect& a, const Line&		b);
		bool Intersect(const RoundRect& a, const Triangle&	b);
		bool Intersect(const RoundRect& a, const Quad&		b);
		bool Intersect(const RoundRect&  a, const RoundRect& b);
		bool Intersect(const RoundRect& a, const Polygon&	b);
		bool Intersect(const RoundRect& a, const MultiPolygon& b);
		bool Intersect(const RoundRect& a, const LineString& b);

		bool Intersect(const Polygon& a, const Vec2&		b);
		bool Intersect(const Polygon& a, const RectF&		b);
		bool Intersect(const Polygon& a, const Line&		b);
		bool Intersect(const Polygon& a, const Circle&		b);
		//bool Intersect(const Polygon& a, const Ellipse&	b);
		bool Intersect(const Polygon& a, const Triangle&	b);
		bool Intersect(const Polygon& a, const Quad&		b);
		bool Intersect(const Polygon& a, const RoundRect&	b);
		bool Intersect(const Polygon& a, const Polygon&		b);
		bool Intersect(const Polygon& a, const MultiPolygon& b);
		bool Intersect(const Polygon& a, const LineString&	b);

		bool Intersect(const MultiPolygon& a, const Vec2&		b);
		bool Intersect(const MultiPolygon& a, const RectF&		b);
		bool Intersect(const MultiPolygon& a, const Line&		b);
		bool Intersect(const MultiPolygon& a, const Circle&		b);
		//bool Intersect(const MultiPolygon& a, const Ellipse&	b);
		bool Intersect(const MultiPolygon& a, const Triangle&	b);
		bool Intersect(const MultiPolygon& a, const Quad&		b);
		bool Intersect(const MultiPolygon&  a, const RoundRect&	b);
		bool Intersect(const MultiPolygon& a, const Polygon&	b);
		bool Intersect(const MultiPolygon& a, const MultiPolygon& b);
		bool Intersect(const MultiPolygon& a, const LineString&	b);

		bool Intersect(const LineString& a, const Vec2&			b);
		bool Intersect(const LineString& a, const RectF&		b);
		bool Intersect(const LineString& a, const Circle&		b);
		bool Intersect(const LineString& a, const Ellipse&		b);
		bool Intersect(const LineString& a, const Line&			b);
		bool Intersect(const LineString& a, const Triangle&		b);
		bool Intersect(const LineString& a, const Quad&			b);
		bool Intersect(const LineString& a, const RoundRect&	b);
		bool Intersect(const LineString& a, const Polygon&		b);
		bool Intersect(const LineString& a, const MultiPolygon& b);
		bool Intersect(const LineString& a, const LineString&	b);


		bool Within(const Point& a, const Rect&		b);
		bool Within(const Point& a, const RectF&	b);

		bool Within(const Vec2&  a, const RectF&	b);
		bool Within(const Vec2&  a, const Circle&	b);
		bool Within(const Vec2&  a, const Ellipse&	b);
		bool Within(const Vec2&  a, const Triangle&	b);
		bool Within(const Vec2&  a, const Quad&		b);
		bool Within(const Vec2&  a, const RoundRect& b);
		bool Within(const Vec2&  a, const Polygon&	b);
		bool Within(const Vec2&  a, const MultiPolygon&	b);

		bool Within(const Rect& a, const Rect&	b);
		bool Within(const Rect& a, const RectF&	b);

		bool Within(const RectF& a, const Rect&		b);
		bool Within(const RectF& a, const RectF&	b);
		bool Within(const RectF& a, const Circle&	b);
		bool Within(const RectF& a, const Ellipse&	b);
		bool Within(const RectF& a, const Triangle&	b);
		bool Within(const RectF& a, const Quad&		b);
		bool Within(const RectF& a, const RoundRect& b);
		bool Within(const RectF& a, const Polygon&	b);
		bool Within(const RectF& a, const MultiPolygon& b);

		bool Within(const Circle& a, const RectF&		b);
		bool Within(const Circle& a, const Circle&		b);
		//bool Within(const Circle& a, const Ellipse&	b);
		bool Within(const Circle& a, const Triangle&	b);
		bool Within(const Circle& a, const Quad&		b);
		bool Within(const Circle&  a, const RoundRect&	b);
		bool Within(const Circle& a, const Polygon&		b);
		bool Within(const Circle& a, const MultiPolygon& b);

		bool Within(const Ellipse& a, const RectF&	b);
		bool Within(const Ellipse& a, const Circle&	b);
		bool Within(const Ellipse& a, const Ellipse&	b);
		bool Within(const Ellipse& a, const Triangle&	b);
		//bool Within(const Ellipse& a, const Quad&		b);
		//bool Within(const Ellipse&  a, const RoundRect&	b);
		//bool Within(const Ellipse& a, const Polygon&	b);
		//bool Within(const Ellipse&  a, const MultiPolygon&	b);

		bool Within(const LineInt& a, const Rect&	b);
		bool Within(const LineInt& a, const RectF&	b);

		bool Within(const Line& a, const Rect&		b);
		bool Within(const Line& a, const RectF&		b);
		bool Within(const Line& a, const Circle&	b);
		bool Within(const Line& a, const Ellipse&	b);
		bool Within(const Line& a, const Triangle&	b);
		bool Within(const Line& a, const Quad&		b);
		bool Within(const Line& a, const RoundRect& b);
		//bool Within(const Line& a, const Polygon& b);
		//bool Within(const Line&  a, const MultiPolygon&	b);

		bool Within(const Triangle& a, const RectF&		b);
		bool Within(const Triangle& a, const Circle&	b);
		bool Within(const Triangle& a, const Ellipse&	b);
		bool Within(const Triangle& a, const Triangle&	b);
		bool Within(const Triangle& a, const Quad&		b);
		bool Within(const Triangle& a, const RoundRect& b);
		bool Within(const Triangle& a, const Polygon&	b);
		bool Within(const Triangle& a, const MultiPolygon& b);

		bool Within(const Quad& a, const RectF&		b);
		bool Within(const Quad& a, const Circle&	b);
		bool Within(const Quad& a, const Ellipse&	b);
		bool Within(const Quad& a, const Triangle&	b);
		bool Within(const Quad& a, const Quad&		b);
		bool Within(const Quad& a, const RoundRect& b);
		bool Within(const Quad& a, const Polygon&	b);
		bool Within(const Quad& a, const MultiPolygon& b);

		bool Within(const Polygon& a, const RectF&		b);
		bool Within(const Polygon& a, const Circle&		b);
		bool Within(const Polygon& a, const Ellipse&	b);
		bool Within(const Polygon& a, const Triangle&	b);
		bool Within(const Polygon& a, const Quad&		b);
		bool Within(const Polygon& a, const RoundRect&	b);
		bool Within(const Polygon& a, const Polygon&	b);
		bool Within(const Polygon& a, const MultiPolygon& b);

		bool Within(const MultiPolygon& a, const RectF&		b);
		bool Within(const MultiPolygon& a, const Circle&	b);
		bool Within(const MultiPolygon& a, const Ellipse&	b);
		bool Within(const MultiPolygon& a, const Triangle&	b);
		//bool Within(const MultiPolygon& a, const Quad&	b);
		//bool Within(const MultiPolygon&  a, const RoundRect&	b);
		//bool Within(const MultiPolygon& a, const Polygon&	b);
		//bool Within(const MultiPolygon&  a, const MultiPolygon&	b);

		bool Within(const LineString& a, const RectF&		b);
		bool Within(const LineString& a, const Circle&		b);
		bool Within(const LineString& a, const Ellipse&		b);
		bool Within(const LineString& a, const Triangle&	b);
		bool Within(const LineString& a, const Quad&		b);
		//bool Within(const LineString&  a, const RoundRect&	b);
		//bool Within(const LineString& a, const Polygon&	b);
		//bool Within(const LineString&  a, const MultiPolygon&	b);
	}
}
