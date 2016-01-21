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
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// スプライトの頂点データ
	/// </summary>
	struct SpriteVertex
	{
		SpriteVertex() = default;

		SpriteVertex(float x, float y, const Color& _color)
			: pos(x, y)
			, color(_color) {}

		constexpr SpriteVertex(float x, float y, const Color& _color, float u, float v)
			: pos(x, y)
			, tex(u, v)
			, color(_color) {}

		void set(float x, float y, float u, float v, const Color& _color)
		{
			pos.set(x, y);

			tex.set(u, v);

			color = _color;
		}

		void set(const Float2& _pos, float u, float v, const Color& _color)
		{
			pos = _pos;

			tex.set(u, v);

			color = _color;
		}

		void setPosColor(float x, float y, const Color& _color)
		{
			pos.set(x, y);

			color = _color;
		}

		void setPosColor(const Float2& _pos, const Color& _color)
		{
			pos = _pos;

			color = _color;
		}

		/// <summary>
		/// 位置
		/// </summary>
		Float2 pos;

		/// <summary>
		/// UV 座標
		/// </summary>
		Float2 tex;

		/// <summary>
		/// 色
		/// </summary>
		Color color;
	};

	/// <summary>
	/// スプライト（2D 自由描画）
	/// </summary>
	class Sprite
	{
	public:

		/// <summary>
		/// 頂点バッファ
		/// </summary>
		Array<SpriteVertex> vertices;

		/// <summary>
		/// インデックスバッファ
		/// </summary>
		/// <remarks>
		/// サイズは 3 の倍数でなければなりません。
		/// </remarks>
		Array<uint32> indices;

		Sprite() = default;

		Sprite(uint32 vertexSize, uint32 indexSize)
			: vertices(vertexSize)
			, indices(indexSize) {}

		/// <summary>
		/// スプライトに適切なインデックス値が設定されているかを返します。
		/// </summary>
		/// <returns>
		/// スプライトに適切なインデックス値が設定されている場合 true, それ以外の場合は false
		/// </returns>
		bool isValid() const;

		void draw() const;

		void draw(const Color& color) const;

		void draw(double x, double y) const;

		void draw(const Vec2& pos) const;

		void draw(double x, double y, const Color& color) const;

		void draw(const Vec2& pos, const Color& color) const;

		void draw(const Texture& texture) const;

		void draw(const Texture& texture, const Color& color) const;

		void draw(const Texture& texture, double x, double y) const;

		void draw(const Texture& texture, const Vec2& pos) const;

		void draw(const Texture& texture, double x, double y, const Color& color) const;

		void draw(const Texture& texture, const Vec2& pos, const Color& color) const;


		void drawSubset(uint32 indexStart, uint32 indexSize) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Color& color) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, double x, double y) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Vec2& pos) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, double x, double y, const Color& color) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Vec2& pos, const Color& color) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Texture& texture) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Texture& texture, const Color& color) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Texture& texture, double x, double y) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Texture& texture, const Vec2& pos) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Texture& texture, double x, double y, const Color& color) const;

		void drawSubset(uint32 indexStart, uint32 indexSize, const Texture& texture, const Vec2& pos, const Color& color) const;
	};
}