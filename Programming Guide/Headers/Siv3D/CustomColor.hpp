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
# include "HalfFloat.hpp"
# include "Color.hpp"
# include "TextureFormat.hpp"
# include "StaticAssertMacro.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr __m128 vec4aInv255 = { 1.0f / 255.0f,1.0f / 255.0f, 1.0f / 255.0f, 1.0f / 255.0f };
	}

	/// <summary>
	/// カスタムカラー
	/// </summary>
	template <TextureFormat format>
	struct CustomColor
	{
		static constexpr TextureFormat Format = format;
	};

	/// <summary>
	/// R32F カラー
	/// </summary>
	struct R32F : CustomColor<TextureFormat::R32_Float>
	{
		float r;

		R32F() = default;

		explicit constexpr R32F(float _r)
			: r(_r) {}

		explicit constexpr R32F(const Color& color)
			: r(color.r / 255.0f) {}
	
		explicit constexpr R32F(const ColorF& color)
			: r(static_cast<float>(color.r)) {}

		constexpr Color toColor() const
		{
			return Color(r >= 1.0f ? 255 : r <= 0.0f ? 0 : static_cast<uint8>(r * 255.0f + 0.5f));
		}

		constexpr ColorF toColorF() const
		{
			return ColorF(r);
		}
	};

	/// <summary>
	/// RGBA16F カラー
	/// </summary>
	struct RGBA16F : CustomColor<TextureFormat::R16G16B16A16_Float>
	{
		HalfFloat r, g, b, a;

		RGBA16F() = default;

		RGBA16F(float _r, float _g, float _b, float _a)
		{
			const float values[4] = { _r, _g, _b, _a };
			DirectX::PackedVector::XMConvertFloatToHalfStream(&r.m_value, sizeof(HalfFloat), values, sizeof(float), 4);
		}

		explicit RGBA16F(const Color& color)
		{
			const __m128 ve = ::_mm_mul_ps(::_mm_cvtepi32_ps(::_mm_set_epi32(color.a, color.b, color.g, color.r)), detail::vec4aInv255);
			DirectX::PackedVector::XMConvertFloatToHalfStream(&r.m_value, sizeof(HalfFloat), ve.m128_f32, sizeof(float), 4);
		}

		explicit RGBA16F(const ColorF& color)
			: r(static_cast<float>(color.r))
			, g(static_cast<float>(color.g))
			, b(static_cast<float>(color.b))
			, a(static_cast<float>(color.a)) {}

		Color toColor() const
		{
			float values[4];
			DirectX::PackedVector::XMConvertHalfToFloatStream(values, sizeof(float), &r.m_value, sizeof(HalfFloat), 4);
			const uint8 cr = values[0] >= 1.0f ? 255 : values[0] <= 0.0f ? 0 : static_cast<uint8>(values[0] * 255.0f + 0.5f);
			const uint8 cg = values[1] >= 1.0f ? 255 : values[1] <= 0.0f ? 0 : static_cast<uint8>(values[1] * 255.0f + 0.5f);
			const uint8 cb = values[2] >= 1.0f ? 255 : values[2] <= 0.0f ? 0 : static_cast<uint8>(values[2] * 255.0f + 0.5f);
			const uint8 ca = values[3] >= 1.0f ? 255 : values[3] <= 0.0f ? 0 : static_cast<uint8>(values[3] * 255.0f + 0.5f);
			return{ cr, cg, cb, ca };
		}

		ColorF toColorF() const
		{
			float values[4];
			DirectX::PackedVector::XMConvertHalfToFloatStream(values, sizeof(float), &r.m_value, sizeof(HalfFloat), 4);
			return{ values[0], values[1], values[2], values[3] };
		}
	};

	/// <summary>
	/// RGBA32F カラー
	/// </summary>
	struct RGBA32F : CustomColor<TextureFormat::R32G32B32A32_Float>
	{
# pragma warning ( disable: 4201 )	
		union
		{
			__m128 v;

			struct
			{
				float r, g, b, a;
			};
		};
# pragma warning ( default: 4201 )	

		RGBA32F() = default;

		explicit RGBA32F(__m128 _v)
			: v(_v) {}

		RGBA32F(float _r, float _g, float _b, float _a)
			: v(::_mm_setr_ps(_r, _g, _b, _a)) {}

		explicit RGBA32F(const Color& color)
			: v(::_mm_mul_ps(::_mm_cvtepi32_ps(::_mm_set_epi32(color.a, color.b, color.g, color.r)), detail::vec4aInv255)) {}

		explicit RGBA32F(const ColorF& color)
			: v(::_mm_setr_ps(static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a))) {}

		Color toColor() const
		{
			static const __m128i toColorShuffleMask = ::_mm_setr_epi8(0, 4, 8, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
			const __m128 sv = ::_mm_min_ps(::_mm_max_ps(v, ::_mm_setzero_ps()), ::_mm_set_ps1(1.0f));
			const __m128 result = ::_mm_mul_ps(sv, ::_mm_set_ps1(255.0f));
			const __m128i re = _mm_cvtps_epi32(result);
			Color color;
			*static_cast<uint32*>(static_cast<void*>(&color)) = ::_mm_cvtsi128_si32(::_mm_shuffle_epi8(re, toColorShuffleMask));
			return color;
		}

		ColorF toColorF() const
		{
			return{ r, g, b, a };
		}
	};

	/// <summary>
	/// R16F カラー
	/// </summary>
	struct R16F : CustomColor<TextureFormat::R16_Float>
	{
		HalfFloat r;

		R16F() = default;

		R16F(float _r)
			: r(_r) {}

		explicit R16F(const Color& color)
			: r(color.r / 255.0f) {}

		explicit R16F(const ColorF& color)
			: r(static_cast<float>(color.r)) {}

		Color toColor() const
		{
			const float t = r.get();
			return Color(t >= 1.0f ? 255 : t <= 0.0f ? 0 : static_cast<uint8>(t * 255.0f + 0.5f));
		}

		ColorF toColorF() const
		{
			return ColorF(r.get());
		}
	};

	/// <summary>
	/// RG16F カラー
	/// </summary>
	struct RG16F : CustomColor<TextureFormat::R16G16_Float>
	{
		HalfFloat r, g;

		RG16F() = default;

		RG16F(float _r, float _g)
			: r(_r)
			, g(_g) {}

		explicit RG16F(const Color& color)
			: r(color.r / 255.0f)
			, g(color.g / 255.0f) {}

		explicit RG16F(const ColorF& color)
			: r(static_cast<float>(color.r))
			, g(static_cast<float>(color.g)) {}

		Color toColor() const
		{
			const float tr = r.get();
			const float tg = g.get();
			const uint8 cr = tr >= 1.0f ? 255 : tr <= 0.0f ? 0 : static_cast<uint8>(tr * 255.0f + 0.5f);
			const uint8 cg = tg >= 1.0f ? 255 : tg <= 0.0f ? 0 : static_cast<uint8>(tg * 255.0f + 0.5f);
			return Color(cr, cg, 255);
		}

		ColorF toColorF() const
		{
			return ColorF(r.get(), g.get(), 1.0);
		}
	};

	/// <summary>
	/// RG32F カラー
	/// </summary>
	struct RG32F : CustomColor<TextureFormat::R32G32_Float>
	{
		float r, g;

		RG32F() = default;

		constexpr RG32F(float _r, float _g)
			: r(_r)
			, g(_g) {}

		explicit constexpr RG32F(const Color& color)
			: r(color.r / 255.0f)
			, g(color.g / 255.0f) {}

		explicit constexpr RG32F(const ColorF& color)
			: r(static_cast<float>(color.r))
			, g(static_cast<float>(color.g)) {}

		constexpr Color toColor() const
		{
			return Color(r >= 1.0f ? 255 : r <= 0.0f ? 0 : static_cast<uint8>(r * 255.0f + 0.5f),
						 g >= 1.0f ? 255 : g <= 0.0f ? 0 : static_cast<uint8>(g * 255.0f + 0.5f), 255);
		}

		constexpr ColorF toColorF() const
		{
			return ColorF(r, g, 1.0);
		}
	};

	s3d_static_assert(sizeof(R32F) == 4);
	s3d_static_assert(sizeof(RGBA16F) == 8);
	s3d_static_assert(sizeof(RGBA32F) == 16);
	s3d_static_assert(sizeof(R16F) == 2);
	s3d_static_assert(sizeof(RG16F) == 4);
	s3d_static_assert(sizeof(RG32F) == 8);
}
