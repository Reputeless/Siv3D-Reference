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
# include "Fwd.hpp"
# include "Handle.hpp"
# include "PropertyMacro.hpp"
# include "Image.hpp"
# include "TextureFormat.hpp"

namespace s3d
{
	/// <summary>
	/// テクスチャの設定
	/// </summary>
	enum class TextureDesc
	{
		/// <summary>
		/// ミップマップなし
		/// </summary>
		Unmipped,

		/// <summary>
		/// ミップマップなし、sRGB
		/// </summary>
		UnmippedSRGB,

		/// <summary>
		/// ミップマップあり
		/// </summary>
		Mipped,

		/// <summary>
		/// ミップマップあり、sRGB
		/// </summary>
		MippedSRGB,

		/// <summary>
		/// 3D 用のテクスチャのデフォルト [ミップマップあり、sRGB]
		/// </summary>
		For3D = MippedSRGB,
	};

	struct MultiSampling
	{
		MultiSampling() = default;

		MultiSampling(uint32 _count, uint32 _quality)
			: count(_count)
			, quality(_quality) {}

		uint32 count = 1;
		
		uint32 quality = 0;
	};

	/// <summary>
	/// テクスチャ
	/// </summary>
	class Texture
	{
	protected:

		class Handle{};

		using TextureHandle = Siv3DHandle<Handle>;

		std::shared_ptr<TextureHandle> m_handle;

		struct _swapChain{};

		struct _render{};

		struct _depthStencil{};

		struct _dyanmic{};

		Texture(const _swapChain&);

		Texture(const _render&, const Size& size, TextureFormat format, const MultiSampling& multiSampling);

		Texture(const _depthStencil&, const Size& size, TextureFormat format, const MultiSampling& multiSampling);

		Texture(uint32 width, uint32 height, const void* src, uint32 srcSize, uint32 stride, TextureFormat format);

		Texture(uint32 width, uint32 height, const void* src, uint32 srcSize, uint32 stride, TextureFormat format, const _dyanmic&);

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Texture();

		/// <summary>
		/// 画像からテクスチャを作成します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像が空の場合、空のテクスチャを作成します。
		/// </remarks>
		explicit Texture(const Image& image, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 画像ファイルからテクスチャを作成します。
		/// </summary>
		/// <param name="path">
		/// 画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		explicit Texture(const FilePath& path, TextureDesc desc = TextureDesc::Unmipped);

		explicit Texture(IReader&& reader, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 2 つの画像ファイルからテクスチャを作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB を読み込む画像ファイルのパス
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Texture(const FilePath& rgb, const FilePath& alpha, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 画像ファイルからアルファ値を作成し、テクスチャを作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB 成分の色
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Texture(const Color& rgb, const FilePath& alpha, TextureDesc desc = TextureDesc::Unmipped);

		/// <summary>
		/// 一連の画像ファイルからミップマップテクスチャを作成します。
		/// </summary>
		/// <param name="mipImages">
		/// ミップマップに使う一連の画像
		/// </param>
		/// <param name="desc">
		/// テクスチャの設定
		/// </param>
		/// <remarks>
		/// 画像が空の場合かエラーが発生した場合は、空のテクスチャを作成します。
		/// </remarks>
		Texture(const Array<Image>& mipImages, TextureDesc desc = TextureDesc::Mipped);

		/// <summary>
		/// カスタム画像からテクスチャを作成します。
		/// </summary>
		/// <param name="image">
		/// カスタム画像
		/// </param>
		/// <remarks>
		/// 画像が空の場合、空のテクスチャを作成します。
		/// </remarks>
		template <class Type>
		explicit Texture(const CustomImage<Type>& image)
			: Texture(
					image.width,
					image.height,
					image.data(),
					image.memorySize(),
					image.stride,
					CustomImage<Type>::Format
					) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Texture();

		/// <summary>
		/// テクスチャをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じテクスチャが使われていない場合、テクスチャのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// テクスチャが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// テクスチャが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return !isEmpty(); }

		/// <summary>
		/// テクスチャハンドルの ID を示します。
		/// </summary>
		HandleIDType id() const;

		/// <summary>
		/// テクスチャが空かどうかを示します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// 2 つの Texture が同じかどうかを返します。
		/// </summary>
		/// <param name="texture">
		/// 比較する Texture
		/// </param>
		/// <returns>
		/// 2 つの Texture が同じ場合 true, それ以外の場合は false
		/// </returns>
		bool operator == (const Texture& texture) const;

		/// <summary>
		/// 2 つの Texture が異なるかどうかを返します。
		/// </summary>
		/// <param name="texture">
		/// 比較する Texture
		/// </param>
		/// <returns>
		/// 2 つの Texture が異なる場合 true, それ以外の場合は false
		/// </returns>
		bool operator != (const Texture& texture) const;

		/// <summary>
		/// テクスチャの幅（ピクセル）
		/// </summary>
		Property_Get(int32, width) const;

		/// <summary>
		/// テクスチャの高さ（ピクセル）
		/// </summary>
		Property_Get(int32, height) const;

		/// <summary>
		/// テクスチャの大きさ（ピクセル）
		/// </summary>
		Property_Get(Size, size) const;

		/// <summary>
		/// ミップマップの有無を示します。
		/// </summary>
		Property_Get(bool, mipped) const;

		/// <summary>
		/// テクスチャフォーマットを示します。
		/// </summary>
		Property_Get(TextureFormat, format) const;

		/// <summary>
		/// テクスチャを描きます。
		/// </summary>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF draw(const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 描画開始位置の X 座標
		/// </param>
		/// <param name="y">
		/// 描画開始位置の Y 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF draw(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 描画開始位置
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF draw(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="y">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF drawAt(double x, double y, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 中心位置の座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		const RectF drawAt(const Vec2& pos, const Color& diffuse = Palette::White) const;

		/// <summary>
		/// テクスチャ内の範囲を表す TextureRegion を返します。
		/// </summary>
		/// <param name="x">
		/// 範囲開始位置の X 座標（ピクセル）
		/// </param>
		/// <param name="y">
		/// 範囲開始位置の Y 座標（ピクセル）
		/// </param>
		/// <param name="w">
		/// 範囲の幅（ピクセル）
		/// </param>
		/// <param name="h">
		/// 範囲の高さ（ピクセル）
		/// </param>
		/// <returns>
		/// テクスチャの範囲を表す TextureRegion
		/// </returns>
		const TextureRegion operator ()(double x, double y, double w, double h) const;

		const TextureRegion operator ()(const Vec2& xy, double w, double h) const;

		const TextureRegion operator ()(double x, double y, const Vec2& size) const;

		const TextureRegion operator ()(const Vec2& xy, const Vec2& size) const;

		/// <summary>
		/// テクスチャ内の範囲を表す TextureRegion を返します。
		/// </summary>
		/// <param name="rect">
		/// 範囲（ピクセル）
		/// </param>
		/// <returns>
		/// テクスチャの範囲を表す TextureRegion
		/// </returns>
		const TextureRegion operator ()(const RectF& rect) const;

		/// <summary>
		/// テクスチャ内の範囲を表す TextureRegion を返します。
		/// </summary>
		/// <param name="u">
		/// 
		/// </param>
		/// <param name="v">
		/// 
		/// </param>
		/// <param name="w">
		/// 
		/// </param>
		/// <param name="h">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		const TextureRegion uv(double u, double v, double w, double h) const;

		/// <summary>
		/// テクスチャ内の範囲を表す TextureRegion を返します。
		/// </summary>
		/// <param name="rect">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		const TextureRegion uv(const RectF& rect) const;

		const TextureRegion mirror() const;

		const TextureRegion flip() const;

		const TextureRegion scale(double scaling) const;

		const TextureRegion scale(double xScaling, double yScaling) const;

		const TextureRegion scale(const Vec2& scaling) const;

		const TextureRegion resize(double width, double height) const;

		const TextureRegion resize(const Vec2& size) const;

		const TextureRegion repeat(double xRepeat, double yRepeat) const;

		const TextureRegion repeat(const Vec2& repeat) const;

		const TextureRegion map(double width, double height) const;

		const TextureRegion map(const Vec2& size) const;

		const TexturedQuad rotate(double radian) const;

		const TexturedQuad rotateAt(double x, double y, double radian) const;

		const TexturedQuad rotateAt(const Vec2& pos, double radian) const;
	};
}
