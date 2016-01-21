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

# ifndef S3D_LOOP_DEFINED
#	define S3D_LOOP_DEFINED
# endif

namespace s3d
{ 
#pragma warning(disable:4389)
	# include "../ThirdParty/steps/loop.h"
#pragma warning(default:4389)

	namespace loop
	{
		template <class T, class N, class S>
		class steps_class2D
		{
		public:

			class steps_iterator : public std::iterator<std::forward_iterator_tag, Point>
			{
				int m_countX;
				int m_startX;
				Point m_step_counter;
				Point m_counter;
				Point m_step;

			public:

				steps_iterator()
					: m_step_counter(0, 0) {}

				constexpr steps_iterator(Point steps_count, Point start, Point step)
					: m_countX(steps_count.x)
					, m_startX(start.x)
					, m_step_counter(steps_count)
					, m_counter(start)
					, m_step(step) {}

				steps_iterator& operator++()
				{
					if (m_step_counter.x == 1)
					{
						m_step_counter.x = m_countX;

						--m_step_counter.y;

						m_counter.x = m_startX;

						m_counter.y = m_counter.y + m_step.y;
					}
					else
					{
						--m_step_counter.x;

						m_counter.x = m_counter.x + m_step.x;
					}

					return *this;
				}

				steps_iterator operator++(int)
				{
					steps_iterator it = *this;

					++(*this);

					return it;
				}

				const T& operator*() const
				{
					return m_counter;
				}

				const T* operator->() const
				{
					return &m_counter;
				}

				bool operator== (const steps_iterator& r) const
				{
					return m_step_counter == r.m_step_counter;
				}

				bool operator!= (const steps_iterator& r) const
				{
					return !(m_step_counter == r.m_step_counter);
				}
			};

			typedef steps_iterator iterator;

		private:
			T m_start;
			N m_step_count;
			S m_step_length;
			iterator m_end_iterator;
			iterator m_start_iterator;

		public:

			constexpr steps_class2D(T start, N step_count, S step) :
				m_start(start),
				m_step_count(step_count),
				m_step_length(step),
				m_end_iterator({ step_count.x, 0 }, {}, {}),
				m_start_iterator(step_count, start, step) {}

			iterator begin() const
			{
				return m_start_iterator;
			}

			iterator end() const { return m_end_iterator; }

			T first_value() const { return m_start; }
			N size() const { return m_step_count; }
			S step_length() const { return m_step_length; }
		};

		inline constexpr auto step(Point a, Point n, Point s)
		{
			return steps_class2D<Point, Point, Point>(a, n, s);
		}

		inline constexpr auto step(Point a, Point n)
		{
			return steps_class2D<Point, Point, Point>(a, n, Point(1, 1));
		}

		inline constexpr auto step(Point n)
		{
			return steps_class2D<Point, Point, Point>(Point(0, 0), n, Point(1, 1));
		}

		inline constexpr auto step_backward(Point n)
		{
			return steps_class2D<Point, Point, Point>(n - Point(1, 1), n, Point(-1, -1));
		}

		template <class Type, class S, class F>
		inline Array<Type> step_array(S n, F f)
		{
			Array<Type> v;
			
			for (auto i : step(n))
			{
				v.push_back(f(i));
			}

			return v;
		}
	}
}
