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
# include <random>
# include <type_traits>

namespace s3d
{
	/// <summary>
	/// 一様分布
	/// </summary>
	/// <remarks>
	/// 乱数の型と範囲を定義します。
	/// </remarks>
	template <class Type>
	class UniformDistribution
	{
	private:

		using DistributionType = std::conditional_t<std::is_floating_point<Type>::value,
			std::uniform_real_distribution<Type>, std::uniform_int_distribution<Type>> ;

		DistributionType m_distribution;

	public:

		/// <summary>
		/// 一様分布を設定します。
		/// </summary>
		/// <param name="min">
		/// 生成する乱数の最小値
		/// </param>
		/// <param name="max">
		/// 生成する乱数の最大値
		/// </param>
		UniformDistribution(Type min, Type max)
		{
			assert(min <= max);

			m_distribution.param(DistributionType::param_type{ min, max });
		}

		/// <summary>
		/// 一様分布の乱数を生成します。
		/// </summary>
		/// <param name="engine">
		/// 乱数生成エンジン
		/// </param>
		/// <returns>
		/// 乱数
		/// </returns>
		template <class Engine>
		Type operator()(Engine& engine) const
		{
			return m_distribution(engine);
		}

		/// <summary>
		/// 一様分布を設定します。
		/// </summary>
		/// <param name="min">
		/// 生成する乱数の最小値
		/// </param>
		/// <param name="max">
		/// 生成する乱数の最大値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(Type min, Type max)
		{
			assert(min <= max);

			m_distribution.param({ min, max });
		}

		/// <summary>
		/// 生成する乱数の最小値
		/// </summary>
		Type min() const
		{
			return distribution.min();
		}

		/// <summary>
		/// 生成する乱数の最大値
		/// </summary>
		Type max() const
		{
			return distribution.max();
		}
	};

	/// <summary>
	/// 正規分布
	/// </summary>
	/// <remarks>
	/// 正規分布を定義します。
	/// </remarks>
	class NormalDistribution
	{
	private:

		std::normal_distribution<double> m_distribution;

	public:

		/// <summary>
		/// 正規分布を設定します。
		/// </summary>
		/// <param name="mean">
		/// 平均
		/// </param>
		/// <param name="sigma">
		/// 標準偏差
		/// </param>
		NormalDistribution(double mean, double sigma)
			: m_distribution(mean, sigma) {}

		/// <summary>
		/// 正規分布の乱数を生成します。
		/// </summary>
		/// <param name="engine">
		/// 乱数生成エンジン
		/// </param>
		/// <returns>
		/// 乱数
		/// </returns>
		template <class Engine>
		double operator()(Engine& engine)
		{
			return m_distribution(engine);
		}

		/// <summary>
		/// 正規分布を設定します。
		/// </summary>
		/// <param name="mean">
		/// 平均
		/// </param>
		/// <param name="sigma">
		/// 標準偏差
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(double mean, double sigma)
		{
			m_distribution.param(std::normal_distribution<double>::param_type{ mean, sigma });
		}

		/// <summary>
		/// 平均
		/// </summary>
		double mean() const
		{
			return m_distribution.mean();
		}

		/// <summary>
		/// 標準偏差
		/// </summary>
		double sigma() const
		{
			return m_distribution.sigma();
		}
	};
}
