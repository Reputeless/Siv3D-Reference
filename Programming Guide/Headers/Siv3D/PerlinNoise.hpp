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
# include <array>
# include "Types.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// Perlin Noise 生成
	/// </summary>
	/// <remarks>
	/// リファレンス実装 http://mrl.nyu.edu/~perlin/noise/
	/// </remarks>
	class PerlinNoise
	{
	public:

		explicit PerlinNoise(uint32 seed = 0);

		double noise(double x) const;

		double noise(double x, double y) const;

		double noise(const Vec2& xy) const
		{
			return noise(xy.x, xy.y);
		}

		double noise(double x, double y, double z) const;

		double noise(const Vec3& xyz) const
		{
			return noise(xyz.x, xyz.y, xyz.z);
		}

		double noise0_1(double x) const
		{
			return noise(x) * 0.5 + 0.5;
		}

		double noise0_1(double x, double y) const
		{
			return noise(x, y) * 0.5 + 0.5;
		}

		double noise0_1(const Vec2& xy) const
		{
			return noise0_1(xy.x, xy.y);
		}

		double noise0_1(double x, double y, double z) const
		{
			return noise(x, y, z) * 0.5 + 0.5;
		}

		double noise0_1(const Vec3& xyz) const
		{
			return noise0_1(xyz.x, xyz.y, xyz.z);
		}

		double octaveNoise(double x, int32 octaves) const;

		double octaveNoise(double x, double y, int32 octaves) const;

		double octaveNoise(const Vec2& xy, int32 octaves) const
		{
			return octaveNoise(xy.x, xy.y, octaves);
		}

		double octaveNoise(double x, double y, double z, int32 octaves) const;

		double octaveNoise(const Vec3& xyz, int32 octaves) const
		{
			return octaveNoise(xyz.x, xyz.y, xyz.z, octaves);
		}

		double octaveNoise0_1(double x, int32 octaves) const
		{
			return octaveNoise(x, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(double x, double y, int32 octaves) const
		{
			return octaveNoise(x, y, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(const Vec2& xy, int32 octaves) const
		{
			return octaveNoise(xy.x, xy.y, octaves);
		}

		double octaveNoise0_1(double x, double y, double z, int32 octaves) const
		{
			return octaveNoise(x, y, z, octaves) * 0.5 + 0.5;
		}

		double octaveNoise0_1(const Vec3& xyz, int32 octaves) const
		{
			return octaveNoise(xyz.x, xyz.y, xyz.z, octaves);
		}

		const std::array<int32, 512>& serialize() const;

		void deserialize(const std::array<int32, 512>& representation);

	private:

		double fade(double t) const;

		double lerp(double t, double a, double b) const;

		double grad(int32 hash, double x, double y, double z) const;

		std::array<int32, 512> p;
	};
}
