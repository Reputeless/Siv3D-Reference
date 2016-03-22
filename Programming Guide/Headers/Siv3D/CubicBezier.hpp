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
	/// 3 次ベジェ曲線
	/// </summary>
	struct CubicBezier
	{
		Vec2 p0, p1, p2, p3;

		CubicBezier() = default;

		constexpr CubicBezier(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2, const Vec2& _p3)
			: p0(_p0)
			, p1(_p1)
			, p2(_p2)
			, p3(_p3) {}

		constexpr Vec2 getPos(double t) const
		{
			return (1 - t)*(1 - t)*(1 - t)*p0 + 3 * (1 - t)*(1 - t)*t*p1 + 3 * (1 - t)*t*t*p2 + t*t*t*p3;
		}

		Vec2 getTangent(double t) const
		{
			return (-3 * p0*(1 - t) * (1 - t) +
				p1*(3 * (1 - t)*(1 - t) - 6 * (1 - t) *t) +
				p2*(6 * (1 - t)*t - 3 * t * t) + 3 * p3*t * t).normalized();
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

	struct CubicBezierPath
	{
	private:

		CubicBezier m_bezier;

		Vec2 m_v1, m_v2, m_v3;

		double m_t = 0.0;

	public:

		CubicBezierPath() = default;

		explicit CubicBezierPath(const CubicBezier& bezier)
		{
			set(bezier);
		}

		void set(const CubicBezier& bezier)
		{
			m_bezier = bezier;
			m_v1.set(-3 * bezier.p0 + 9 * bezier.p1 - 9 * bezier.p2 + 3 * bezier.p3);
			m_v2.set(6 * bezier.p0 - 12 * bezier.p1 + 6 * bezier.p2);
			m_v3.set(-3 * bezier.p0 + 3 * bezier.p1);
		}

		void set(double t)
		{
			m_t = t;
		}

		double advance(double distance, int quality = 8)
		{
			for (int i = 0; i < quality; ++i)
			{
				m_t = m_t + (distance / quality) / (m_t * m_t * m_v1 + m_t * m_v2 + m_v3).length();
			}

			return m_t;
		}
	};
}
