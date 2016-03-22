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
# include "PointVector.hpp"
# include "LineString.hpp"

namespace s3d
{
	/// <summary>
	/// 2 次ベジェ曲線
	/// </summary>
	struct QuadraticBezier
	{
		Vec2 p0, p1, p2;

		QuadraticBezier() = default;

		constexpr QuadraticBezier(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2)
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		constexpr Vec2 getPos(double t) const
		{
			return (1 - t) * (1 - t)* p0 + 2 * (1 - t) * t * p1 + t * t * p2;
		}

		Vec2 getTangent(double t) const
		{
			return ((p1 - p0) * 2 * (1 - t) + (p2 - p1) * (2 * t)).normalized();
		}

		LineString getLineString(uint32 quality = 24) const
		{
			return getLineString(0.0, 1.0, quality);
		}

		LineString getLineString(double start, double end, uint32 quality = 24) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void write(Image& image, int32 thickness, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, int32 thickness, const Color& color = Palette::Black) const;

		void draw(const Color& color = Palette::White) const;

		void draw(double thickness, const Color& color = Palette::White) const;
	};

	struct QuadraticBezierPath
	{
	private:

		QuadraticBezier m_bezier;

		Vec2 m_v1, m_v2;

		double m_t = 0.0;

	public:

		QuadraticBezierPath() = default;

		explicit QuadraticBezierPath(const QuadraticBezier& bezier)
		{
			set(bezier);
		}

		void set(const QuadraticBezier& bezier)
		{
			m_bezier = bezier;
			m_v1.set(2 * bezier.p0 - 4 * bezier.p1 + 2 * bezier.p2);
			m_v2.set(-2 * bezier.p0 + 2 * bezier.p1);
		}

		void set(double t)
		{
			m_t = t;
		}

		double advance(double distance, int32 quality = 8)
		{
			for (int32 i = 0; i < quality; ++i)
			{
				m_t = m_t + (distance/quality) / (m_t * m_v1 + m_v2).length();
			}

			return m_t;
		}
	};
}
