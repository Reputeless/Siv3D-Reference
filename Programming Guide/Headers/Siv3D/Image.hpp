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
# include "Array.hpp"
# include "Color.hpp"
# include "Rectangle.hpp"
# include "Utility.hpp"

namespace s3d
{
	/// <summary>
	/// 画像フォーマット
	/// </summary>
	enum class ImageFormat
	{
		/// <summary>
		/// 不明
		/// </summary>
		Unknown,

		/// <summary>
		/// DDS
		/// </summary>
		DDS,

		/// <summary>
		/// PNG
		/// </summary>
		PNG,

		/// <summary>
		/// JPEG
		/// </summary>
		JPEG,

		/// <summary>
		/// JPEG2000
		/// </summary>
		JPEG2000,

		//JPEGXR,
		//ICO,

		/// <summary>
		/// BMP
		/// </summary>
		BMP,

		/// <summary>
		/// WebP
		/// </summary>
		WebP,

		/// <summary>
		/// GIF
		/// </summary>
		GIF,

		/// <summary>
		/// TIFF
		/// </summary>
		TIFF,

		/// <summary>
		/// TGA
		/// </summary>
		TGA,

		/// <summary>
		/// PPM
		/// </summary>
		PPM,

		/// <summary>
		/// 指定しない / 拡張子から判断
		/// </summary>
		Unspecified = Unknown,
	};

	/// <summary>
	/// DDS フォーマット
	/// </summary>
	enum class DDSFormat
	{
		/// <summary>
		/// ABGR8
		/// </summary>
		ABGR8,

		/// <summary>
		/// BC1 (DXT1)
		/// </summary>
		BC1,

		/// <summary>
		/// BC2 (DXT3)
		/// </summary>
		BC2,

		/// <summary>
		/// BC3 (DXT5)
		/// </summary>
		BC3,
	};

	/// <summary>
	/// PNG フィルタ
	/// </summary>
	struct PNGFilter
	{
		enum Flag
		{
			/// <summary>
			/// 
			/// </summary>
			None = 0x08,

			/// <summary>
			/// 
			/// </summary>
			Sub = 0x10,

			/// <summary>
			/// 
			/// </summary>
			Up = 0x20,

			/// <summary>
			/// 
			/// </summary>
			Avg = 0x40,

			/// <summary>
			/// 
			/// </summary>
			Paeth = 0x80,

			/// <summary>
			/// 
			/// </summary>
			Default = None | Sub | Up | Avg | Paeth,
		};
	};

	/// <summary>
	/// WebP の圧縮方法
	/// </summary>
	enum class WebPMethod
	{
		/// <summary>
		/// 高速圧縮	(圧縮率と品質： 最低、	速度： 早い)
		/// </summary>
		Fast,

		/// <summary>
		/// 通常圧縮	(圧縮率と品質： 普通、	速度： 普通)
		/// </summary>
		Default,

		/// <summary>
		/// 高圧縮	(圧縮率と品質： 高、	速度： 遅い)
		/// </summary>
		Quality,

		/// <summary>
		/// 最高圧縮	(圧縮率と品質： 最高、	速度： 非常に遅い)
		/// </summary>
		BestQuality,
	};

	/// <summary>
	/// 
	/// </summary>
	enum class ImageAddressMode
	{
		/// <summary>
		/// 
		/// </summary>
		Wrap,

		/// <summary>
		/// 
		/// </summary>
		Mirror,

		/// <summary>
		/// 
		/// </summary>
		Clamp,
	};

	/// <summary>
	/// 
	/// </summary>
	enum class AdaptiveMethod
	{
		/// <summary>
		/// 
		/// </summary>
		Mean,

		/// <summary>
		/// 
		/// </summary>
		Gaussian,
	};

	/// <summary>
	/// 画像拡大縮小の手法
	/// </summary>
	enum class Interpolation
	{
		/// <summary>
		/// 最近傍補間
		/// </summary>
		Nearest,

		/// <summary>
		/// バイリニア補間
		/// </summary>
		Linear,

		/// <summary>
		/// バイキュービック補間
		/// </summary>
		Cubic,

		/// <summary>
		/// エリア（画像の大幅な縮小に適している）
		/// </summary>
		Area,

		/// <summary>
		/// Lanczos 法（拡大や、小幅な縮小に適している）
		/// </summary>
		Lanczos,

		/// <summary>
		/// 最適な手法を自動選択
		/// </summary>
		Unspecified,
	};

	/// <summary>
	/// 塗りつぶしの連結性
	/// </summary>
	enum class FloodFillConnectivity
	{
		/// <summary>
		/// 上下左右 4 ピクセル
		/// </summary>
		Value4 = 4,

		/// <summary>
		/// 周囲 8 ピクセル
		/// </summary>
		Value8 = 8,
	};

	/// <summary>
	/// 顔検出の画像の種類
	/// </summary>
	enum class CascadeType
	{
		/// <summary>
		/// 写真
		/// </summary>
		Photo,

		/// <summary>
		/// アニメ・イラスト
		/// </summary>
		Anime,
	};

	enum class EdgePreservingFilterType
	{
		Recursive,

		NormalizedConvolution,
	};

	/// <summary>
	/// 画像
	/// </summary>
	/// <remarks>
	/// メモリ上に確保される画像データです。
	/// ピクセル単位のアクセスや、変形、エフェクト処理を適用できます。
	/// イメージを描画する場合は Texture に変換する必要があります。
	/// </remarks>
	class Image
	{
	private:

		Array<Color> m_data;

		uint32 m_width = 0;

		uint32 m_height = 0;

		bool isValidSize(size_t width, size_t height) const
		{
			return width <= MaxSize && height <= MaxSize;
		}

		int mod(int32 x, int32 y) const
		{
			return x % y + ((x < 0) ? y : 0);
		}

		int mir(int32 x, int32 y) const
		{
			const int t = mod(x, y * 2);

			return t > y ? (y * 2) - t : t;
		}

		double biliner(double c1, double c2, double c3, double c4, double px, double py) const
		{
			return px * py * (c1 - c2 - c3 + c4) + px * (c2 - c1) + py * (c3 - c1) + c1;
		}

	public:

		using iterator					= Array<Color>::iterator;
		using const_iterator			= Array<Color>::const_iterator;
		using reverse_iterator			= Array<Color>::reverse_iterator;
		using const_reverse_iterator	= Array<Color>::const_reverse_iterator;

		/// <summary>
		/// 画像の最大サイズ
		/// </summary>
		static constexpr int32 MaxSize = 8192;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Image();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Image();

		/// <summary>
		/// 指定したサイズの画像を作成します。
		/// </summary>
		/// <param name="size">
		/// 画像のサイズ（ピクセル）
		/// </param>
		explicit Image(const Size& size)
			: Image(size.x, size.y) {}

		/// <summary>
		/// 指定した色、サイズで塗りつぶされた画像を作成します。
		/// </summary>
		/// <param name="size">
		/// 画像のサイズ（ピクセル）
		/// </param>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		Image(const Size& size, const Color& color)
			: Image(size.x, size.y, color) {}

		Image(const Size& size, std::function<Color(Point)> generator)
			: Image(size.x, size.y, generator) {}

		/// <summary>
		/// 指定したサイズの画像を作成します。
		/// </summary>
		/// <param name="width">
		/// 画像の幅（ピクセル）
		/// </param>
		/// <param name="height">
		/// 画像の高さ（ピクセル）
		/// </param>
		Image(uint32 width, uint32 height)
			: m_data(isValidSize(width, height) ? width*height : 0)
			, m_width(isValidSize(width, height) ? width : 0)
			, m_height(isValidSize(width, height) ? height : 0) {}

		Image(uint32 width, uint32 height, std::function<Color(Point)> generator);

		/// <summary>
		/// 指定した色、サイズで塗りつぶされた画像を作成します。
		/// </summary>
		/// <param name="width">
		/// 画像の幅（ピクセル）
		/// </param>
		/// <param name="height">
		/// 画像の高さ（ピクセル）
		/// </param>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		Image(uint32 width, uint32 height, const Color& color)
			: m_data(isValidSize(width, height) ? width*height : 0, color)
			, m_width(isValidSize(width, height) ? width : 0)
			, m_height(isValidSize(width, height) ? height : 0) {}

		/// <summary>
		/// 画像ファイルから画像を作成します。
		/// </summary>
		/// <param name="path">
		/// 画像ファイルのパス
		/// </param>
		explicit Image(const FilePath& path);

		/// <summary>
		/// Reader から画像を作成します。
		/// </summary>
		/// <param name="reader">
		/// Reader
		/// </param>
		/// <param name="format">
		/// 画像のフォーマット
		/// </param>
		explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

		/// <summary>
		/// 2 つの画像ファイルから画像を作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB を読み込む画像ファイルのパス
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		Image(const FilePath& rgb, const FilePath& alpha);

		/// <summary>
		/// 画像ファイルからアルファ値を作成し、画像を作成します。
		/// </summary>
		/// <param name="rgb">
		/// RGB 成分の色
		/// </param>
		/// <param name="alpha">
		/// アルファ値を読み込む画像ファイルのパス
		/// </param>
		/// <remarks>
		/// alpha の画像の R 成分を、テクスチャのアルファ値に設定します。
		/// 画像ファイルの読み込みに失敗した場合、空のテクスチャを作成します。
		/// </remarks>
		Image(const Color& rgb, const FilePath& alpha);

		/// <summary>
		/// 画像を別の画像からコピーして作成します。
		/// </summary>
		/// <param name="image">
		/// コピーする画像
		/// </param>
		Image(const Image& image)
			: m_data(image.m_data)
			, m_width(image.m_width)
			, m_height(image.m_height) {}

		/// <summary>
		/// 画像を別の画像からムーブして作成します。
		/// </summary>
		/// <param name="image">
		/// ムーブする画像
		/// </param>
		Image(Image&& image)
			: m_data(std::move(image.m_data))
			, m_width(image.m_width)
			, m_height(image.m_height)
		{
			image.m_width = image.m_height = 0;
		}

		/// <summary>
		/// 新しい画像を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい画像
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& operator = (const Image& image);

		/// <summary>
		/// 新しい画像を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい画像
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& operator = (Image && image);

		/// <summary>
		/// 画像を消去し、空の画像にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear()
		{
			m_data.clear();

			m_width = m_height = 0;
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		/// <summary>
		/// 画像を指定した色で塗りつぶします。
		/// </summary>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void fill(const Color& color)
		{
			for (auto& pixel : m_data)
			{
				pixel = color;
			}
		}

		/// <summary>
		/// 画像が空ではないかを返します。
		/// </summary>
		/// <returns>
		/// 画像が空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return !isEmpty;
		}

		/// <summary>
		/// 画像のサイズを変更します。
		/// </summary>
		/// <param name="width">
		/// 新しい幅(ピクセル)
		/// </param>
		/// <param name="height">
		/// 新しい高さ(ピクセル)
		/// </param>
		/// <remarks>
		/// サイズの変更が必要ないときは何もしません。
		/// サイズが変更された場合、すべての要素の値が不定になります。
		/// 画像を拡大縮小する場合は scale() を使います。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_t width, size_t height);

		/// <summary>
		/// 画像のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しいサイズ(ピクセル)
		/// </param>
		/// <remarks>
		/// サイズの変更が必要ないときは何もしません。
		/// サイズが変更された場合、すべての要素の値が不定になります。
		/// 画像を拡大縮小する場合は scale() を使います。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void resize(const Size& size)
		{
			resize(size.x, size.y);
		}

		/// <summary>
		/// 画像のサイズを変更します。
		/// </summary>
		/// <param name="width">
		/// 新しい幅(ピクセル)
		/// </param>
		/// <param name="height">
		/// 新しい高さ(ピクセル)
		/// </param>
		/// <param name="fillColor">
		/// 塗りつぶしの色
		/// </param>
		/// <remarks>
		/// サイズの変更が必要ないときは何もしません。
		/// サイズが変更された場合、すべての要素が fillColor で塗りつぶされます。
		/// 画像を拡大縮小する場合は scale() を使います。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_t width, size_t height, const Color& fillColor);

		/// <summary>
		/// 画像のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しいサイズ(ピクセル)
		/// </param>
		/// <param name="fillColor">
		/// 塗りつぶしの色
		/// </param>
		/// <remarks>
		/// サイズの変更が必要ないときは何もしません。
		/// サイズが変更された場合、すべての要素が fillColor で塗りつぶされます。
		/// 画像を拡大縮小する場合は scale() を使います。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void resize(const Size& size, const Color& fillColor)
		{
			resize(size.x, size.y, fillColor);
		}

		/// <summary>
		/// 画像の一部分をコピーした新しい画像を返します。
		/// </summary>
		/// <param name="rect">
		/// 画像上の範囲
		/// </param>
		/// <returns>
		/// 一部分をコピーした新しい画像
		/// </returns>
		Image clip(const Rect& rect) const;

		/// <summary>
		/// 画像の一部分をコピーした新しい画像を返します。
		/// </summary>
		/// <param name="x">
		/// 画像上の範囲の左上 X 座標
		/// </param>
		/// <param name="y">
		/// 画像上の範囲の左上 Y 座標
		/// </param>
		/// <param name="w">
		/// 画像上の範囲の幅
		/// </param>
		/// <param name="h">
		/// 画像上の範囲の高さ
		/// </param>
		/// <returns>
		/// 一部分をコピーした新しい画像
		/// </returns>
		Image clip(int32 x, int32 y, int32 w, int32 h) const
		{
			return clip({ x, y, w, h });
		}

		Image clip(const Point& pos, int32 w, int32 h) const
		{
			return clip({ pos, w, h });
		}

		Image clip(int32 x, int32 y, const Size& size) const
		{
			return clip({ x, y, size });
		}

		Image clip(const Point& pos, const Size& size) const
		{
			return clip({ pos, size });
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		template <ImageAddressMode addressMode = ImageAddressMode::Clamp>
		const Color& getPixel(int32 y, int32 x) const;

		template <ImageAddressMode addressMode = ImageAddressMode::Clamp>
		const Color& getPixel(const Point& pos) const
		{
			return getPixel<addressMode>(pos.y, pos.x);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		template <>
		const Color& getPixel<ImageAddressMode::Wrap>(int32 y, int32 x) const
		{
			y = mod(y, height);

			x = mod(x, width);

			return m_data[m_width*y + x];
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		template <>
		const Color& getPixel<ImageAddressMode::Mirror>(int32 y, int32 x) const
		{
			y = mir(y, height);

			x = mir(x, width);

			return m_data[m_width*y + x];
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		template <>
		const Color& getPixel<ImageAddressMode::Clamp>(int32 y, int32 x) const
		{
			y = Clamp(y, 0, static_cast<int32>(height) -1);

			x = Clamp(x, 0, static_cast<int32>(width) -1);

			return m_data[m_width*y + x];
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		template <ImageAddressMode addressMode = ImageAddressMode::Clamp>
		ColorF sample(double y, double x) const
		{
			const int32 ix = static_cast<int>(x);
			const int32 iy = static_cast<int>(y);

			const Color& c1 = getPixel<addressMode>(iy, ix);
			const Color& c2 = getPixel<addressMode>(iy, ix + 1);
			const Color& c3 = getPixel<addressMode>(iy + 1, ix);
			const Color& c4 = getPixel<addressMode>(iy + 1, ix + 1);

			const double xr1 = x - ix;
			const double yr1 = y - iy;

			const double r = biliner(c1.r, c2.r, c3.r, c4.r, xr1, yr1);
			const double g = biliner(c1.g, c2.g, c3.g, c4.g, xr1, yr1);
			const double b = biliner(c1.b, c2.b, c3.b, c4.b, xr1, yr1);
			const double a = biliner(c1.a, c2.a, c3.a, c4.a, xr1, yr1);

			return{ r / 255.0, g / 255.0, b / 255.0, a / 255.0 };
		}

		template <ImageAddressMode addressMode = ImageAddressMode::Clamp>
		ColorF sample(const Vec2& pos) const
		{
			return sample<addressMode>(pos.y, pos.x);
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		Color* operator [](uint32 y)
		{
			return &m_data[m_width*y];
		}

		Color& operator [](const Point& pos)
		{
			return m_data[m_width*pos.y + pos.x];
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		const Color* operator [](uint32 y) const
		{
			return &m_data[m_width*y];
		}

		const Color& operator [](const Point& pos) const
		{
			return m_data[m_width*pos.y + pos.x];
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		void* data()
		{
			return &m_data[0];
		}

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		const void* data() const
		{
			return &m_data[0];
		}

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		iterator begin() { return m_data.begin(); }

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		const_iterator begin() const { return m_data.begin(); }

		/// <summary>
		/// 画像の先頭位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭位置のイテレータ
		/// </returns>
		const_iterator cbegin() const { return m_data.cbegin(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		iterator end() { return m_data.end(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		const_iterator end() const { return m_data.end(); }

		/// <summary>
		/// 画像の終了位置のイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の終了位置のイテレータ
		/// </returns>
		const_iterator cend() const { return m_data.cend(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		reverse_iterator rbegin() { return m_data.rbegin(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rbegin() const { return m_data.rbegin(); }

		/// <summary>
		/// 画像の末尾へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の末尾へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crbegin() const { return m_data.crbegin(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		reverse_iterator rend() { return m_data.rend(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rend() const { return m_data.rend(); }

		/// <summary>
		/// 画像の先頭の前へのリバースイテレータを取得します。
		/// </summary>
		/// <returns>
		/// 画像の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crend() const { return m_data.crend(); }

		/// <summary>
		/// 画像の不要なメモリ消費を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit() { m_data.shrink_to_fit(); }

		/// <summary>
		/// 画像を別の画像と交換します。
		/// </summary>
		/// <param name="image">
		/// 交換する画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Image& image)
		{
			m_data.swap(image.m_data);

			std::swap(m_width, image.m_width);

			std::swap(m_height, image.m_height);
		}

		/// <summary>
		/// 画像をコピーした新しい画像を返します。
		/// </summary>
		/// <returns>
		/// コピーした新しい画像
		/// </returns>
		Image clone() const
		{
			return *this;
		}

		/// <summary>
		/// 画像の幅（ピクセル）
		/// </summary>
		Property_Get(int32, width) const { return m_width; }

		/// <summary>
		/// 画像の高さ（ピクセル）
		/// </summary>
		Property_Get(int32, height) const { return m_height; }

		/// <summary>
		/// 画像の幅と高さ（ピクセル）
		/// </summary>
		Property_Get(Size, size) const { return{ width, height }; }

		/// <summary>
		/// 画像の各行のデータサイズ
		/// </summary>
		Property_Get(uint32, stride) const { return m_width * sizeof(Color); }

		/// <summary>
		/// 画像のピクセル数
		/// </summary>
		Property_Get(uint32, num_pixels) const { return m_width * m_height; }

		/// <summary>
		/// 画像のデータサイズ
		/// </summary>
		uint32 memorySize() const { return stride*m_height; }

		/// <summary>
		/// 画像が空かどうかを示します。
		/// </summary>
		Property_Get(bool, isEmpty) const { return m_data.empty(); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool applyAlphaFromRChannel(const FilePath& alpha);

		/// <summary>
		/// 画像を保存します。
		/// </summary>
		/// <param name="path">
		/// 保存するファイル名
		/// </param>
		/// <param name="format">
		/// 保存する際の画像フォーマット。ImageFormat::Unspecified の場合、拡張子から自動で判断します。
		/// </param>
		/// <returns>
		/// 保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool save(const FilePath& path, ImageFormat format = ImageFormat::Unspecified) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path">
		/// 
		/// </param>
		/// <param name="ddsFormat">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool saveDDS(const FilePath& path, DDSFormat ddsFormat = DDSFormat::ABGR8) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path">
		/// 
		/// </param>
		/// <param name="filterFlag">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool savePNG(const FilePath& path, PNGFilter::Flag filterFlag = PNGFilter::Default) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path">
		/// 
		/// </param>
		/// <param name="quality">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool saveJPEG(const FilePath& path, int32 quality = 90) const;

		/// <summary>
		/// 
		/// </summary>path
		/// <param name="">
		/// 
		/// </param>
		/// <param name="compressionRatio">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool saveJPEG2000(const FilePath& path, double compressionRatio = 10.0) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path">
		/// 
		/// </param>
		/// <param name="dither">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool saveGIF(const FilePath& path, bool dither = true) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path">
		/// 
		/// </param>
		/// <param name="quality">
		/// 
		/// </param>
		/// <param name="method">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool saveWebP(const FilePath& path, double quality = 95.0, WebPMethod method = WebPMethod::Default) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="format">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encode(ImageFormat format) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="ddsFormat">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encodeDDS(DDSFormat ddsFormat = DDSFormat::ABGR8) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="filterFlag">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encodePNG(PNGFilter::Flag filterFlag = PNGFilter::Default) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="quality">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encodeJPEG(int32 quality = 90) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="compressionRatio">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encodeJPEG2000(double compressionRatio = 10.0) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="dither">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encodeGIF(bool dither = true) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="quality">
		/// 
		/// </param>
		/// <param name="method">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ByteArray encodeWebP(double quality = 95.0, WebPMethod method = WebPMethod::Default) const;

		/// <summary>
		/// すべてのピクセルに変換関数を適用します。
		/// </summary>
		/// <param name="function">
		/// 変換関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& forEach(std::function<void(Color&)> function)
		{
			for (auto& pixel : m_data)
			{
				function(pixel);
			}

			return *this;
		}

		/// <summary>
		/// ネガポジ反転処理を行います。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& negate();

		/// <summary>
		/// ネガポジ反転処理した画像を返します。
		/// </summary>
		/// <returns>
		/// ネガポジ反転処理した画像
		/// </returns>
		Image negated() const;

		/// <summary>
		/// グレースケール変換を行います。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& grayscale();

		/// <summary>
		/// グレースケール変換した画像を返します。
		/// </summary>
		/// <returns>
		/// グレースケール変換した画像
		/// </returns>
		Image grayscaled() const;

		/// <summary>
		/// セピア調変換を行います。
		/// </summary>
		/// <param name="level">
		/// セピアの強さ [0,255]
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& sepia(int32 level = 25);

		/// <summary>
		/// セピア調変換した画像を返します。
		/// </summary>
		/// <param name="level">
		/// セピアの強さ [0,255]
		/// </param>
		/// <returns>
		/// セピア調変換した画像
		/// </returns>
		Image sepiaed(int32 level = 25) const;

		/// <summary>
		/// ポスタライズ処理を行います。
		/// </summary>
		/// <param name="level">
		/// 各チャンネルの段階数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& postarize(int32 level);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="level">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image postarized(int32 level) const;

		/// <summary>
		/// 明るさを変更します。
		/// </summary>
		/// <param name="level">
		/// 変更レベル
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& brighten(int32 level);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="level">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image brightened(int32 level) const;

		/// <summary>
		/// 上下反転します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& flip();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		Image flipped() const;

		/// <summary>
		/// 左右反転します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& mirror();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		Image mirrored() const;

		/// <summary>
		/// 時計回りに 90° 回転します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& rotate90();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		Image rotated90() const;

		/// <summary>
		/// 時計回りに 180° 回転します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& rotate180();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		Image rotated180() const;

		/// <summary>
		/// 時計回りに 270° 回転します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Image& rotate270();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		Image rotated270() const;

		/// <summary>
		/// ガンマ補正を行います。
		/// </summary>
		/// <param name="gamma">
		/// ガンマ値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Image& gammaCorrect(double gamma);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="gamma">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image gammaCorrected(double gamma) const;

		/// <summary>
		/// 閾値処理を行います。
		/// </summary>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <param name="inverse">
		/// 結果の白黒の反転
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& threshold(uint8 threshold, bool inverse = false);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="threshold">
		/// 
		/// </param>
		/// <param name="inverse">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image thresholded(uint8 threshold, bool inverse = false) const;

		/// <summary>
		/// 適応的な閾値処理を行います。
		/// </summary>
		/// <param name="method">
		/// 適応的閾値アルゴリズム
		/// </param>
		/// <param name="blockSize">
		/// 閾値を求めるために利用される近傍領域のサイズ。奇数
		/// </param>
		/// <param name="c">
		/// 平均または加重平均から引かれる定数
		/// </param>
		/// <param name="inverse">
		/// 結果の白黒の反転
		/// </param>
		/// <remarks>
		/// http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html 参照
		/// </remarks>
		/// <returns>
		/// 
		/// </returns>
		Image& adaptiveThreshold(AdaptiveMethod method, int32 blockSize, int32 c, bool inverse = false);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="method">
		/// 適応的閾値アルゴリズム
		/// </param>
		/// <param name="blockSize">
		/// 閾値を求めるために利用される近傍領域のサイズ。奇数
		/// </param>
		/// <param name="c">
		/// 平均または加重平均から引かれる定数
		/// </param>
		/// <param name="inverse">
		/// 結果の白黒の反転
		/// </param>
		/// <remarks>
		/// http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html 参照
		/// </remarks>
		/// <returns>
		/// 
		/// </returns>
		Image adaptiveThresholded(AdaptiveMethod method, int32 blockSize, int32 c, bool inverse = false) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& mosaic(int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image mosaiced(int32 horizontal, int32 vertical) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& spread(int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image spreaded(int32 horizontal, int32 vertical) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& blur(int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image blurred(int32 horizontal, int32 vertical) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="apertureSize">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& medianBlur(int32 apertureSize);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="apertureSize">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image medianBlurred(int32 apertureSize) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& gaussianBlur(int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image gaussianBlurred(int32 horizontal, int32 vertical) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& dilate(int32 iterations = 1);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image dilated(int32 iterations = 1) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& erode(int32 iterations = 1);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image eroded(int32 iterations = 1) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& floodFill(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image floodFilled(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& scale(int32 _width, int32 _height, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image scaled(int32 _width, int32 _height, Interpolation interpolation = Interpolation::Unspecified) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& scale(const Size& size, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image scaled(const Size& size, Interpolation interpolation = Interpolation::Unspecified) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& scale(double scaling, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image scaled(double scaling, Interpolation interpolation = Interpolation::Unspecified) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& fit(int32 _width, int32 _height, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image fitted(int32 _width, int32 _height, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& fit(const Size& size, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image fitted(const Size& size, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image& border(int32 width, const Color& color = Palette::White);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image bordered(int32 width, const Color& color = Palette::White) const;

		/// <summary>
		/// 画像を別の画像にブレンドして書き込みます。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="pos">
		/// 書き込み開始位置
		/// </param>
		/// <param name="color">
		/// 乗算する色
		/// </param>
		/// <remarks>
		/// 書き込み先を自身にすることはできません。image に自身を指定した場合、何も起こりません。
		/// </remarks>
		/// <returns>
		/// 
		/// </returns>
		void write(Image& image, const Point& pos = { 0, 0 }, const Color& color = Palette::White) const;

		/// <summary>
		/// 画像を別の画像に上書きして書き込みます。
		/// </summary>
		/// <param name="image">
		/// 書き込み先の画像
		/// </param>
		/// <param name="pos">
		/// 書き込み開始位置
		/// </param>
		/// <param name="color">
		/// 乗算する色
		/// </param>
		/// <remarks>
		/// 書き込み先を自身にすることはできません。image に自身を指定した場合、何も起こりません。
		/// </remarks>
		/// <returns>
		/// 
		/// </returns>
		void overwrite(Image& image, const Point& pos = { 0, 0 }, const Color& color = Palette::White) const;

		Image& ARGBtoABGR();

		ImageRegion operator ()(int32 x, int32 y, int32 w, int32 h) const;

		ImageRegion operator ()(const Point& pos, int32 w, int32 h) const;

		ImageRegion operator ()(int32 x, int32 y, const Size& size) const;

		ImageRegion operator ()(const Point& pos, const Size& size) const;

		ImageRegion operator ()(const Rect& rect) const;
	};

	class ImageRegion
	{
	private:

		friend class Image;

		const Image& m_imageRef;

		const Rect m_rect;

		ImageRegion(const ImageRegion&) = default;

		ImageRegion& operator = (const ImageRegion&) = delete;

		ImageRegion(const Image& image, const Rect& rect)
			: m_imageRef(image)
			, m_rect(rect) {}

	public:

		void write(Image& image, const Point& pos = { 0, 0 }, const Color& color = Palette::White) const;

		void overwrite(Image& image, const Point& pos = { 0, 0 }, const Color& color = Palette::White) const;
	};

	inline ImageRegion Image::operator ()(int32 x, int32 y, int32 w, int32 h) const
	{
		return operator()({ x, y, w, h });
	}

	inline ImageRegion Image::operator ()(const Point& pos, int32 w, int32 h) const
	{
		return operator()({ pos, w, h });
	}

	inline ImageRegion Image::operator ()(int32 x, int32 y, const Size& size) const
	{
		return operator()({ x, y, size });
	}

	inline ImageRegion Image::operator ()(const Point& pos, const Size& size) const
	{
		return operator()({ pos, size });
	}

	/// <summary>
	/// 
	/// </summary>
	namespace Imaging
	{
		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ImageFormat GetFormat(const FilePath& path);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ImageFormat GetFormat(const IReader& reader);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		ImageFormat GetFormatFromFileName(const FilePath& path);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Size GetSize(const FilePath& path);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Size GetSize(const IReader& reader);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Array<Image> LoadAnimatedGIF(const FilePath& path);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="">
		/// 
		/// </param>
		/// <param name="">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image ExpandAnimatedGIF(const FilePath& path, Array<Rect>& frameRects);

		[[deprecated("** Imaging::SaveAnimatedGIF() is a deprecated function. Use AnimatedGIFWriter instead. **")]]
		bool SaveAnimatedGIF(const FilePath& path, const Array<Image>& images, uint16 delay, bool dither = true, bool hasAlpha = true);

		/// <summary>
		/// すべてのピクセルに変換関数を適用します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="function">
		/// 変換関数
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		void ForEach(const Image& src, Image& dst, std::function<void(Color&)> function);

		/// <summary>
		/// ネガポジ反転処理を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Negate(const Image& src, Image& dst);

		/// <summary>
		/// グレースケール変換を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Grayscale(const Image& src, Image& dst);

		/// <summary>
		/// セピア調変換を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="level">
		/// セピアの強さ [0,255]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Sepia(const Image& src, Image& dst, int32 level = 25);

		/// <summary>
		/// ポスタライズ処理を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="level">
		/// 各チャンネルの段階数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Postarize(const Image& src, Image& dst, int32 level);

		/// <summary>
		/// 明るさを変更します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="level">
		/// 変更レベル
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Brighten(const Image& src, Image& dst, int32 level);

		/// <summary>
		/// 上下反転します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Flip(const Image& src, Image& dst);

		/// <summary>
		/// 左右反転します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Mirror(const Image& src, Image& dst);

		/// <summary>
		/// 時計回りに 90° 回転します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Rotate90(const Image& src, Image& dst);

		/// <summary>
		/// 時計回りに 180° 回転します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Rotate180(const Image& src, Image& dst);

		/// <summary>
		/// 時計回りに 270° 回転します。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Rotate270(const Image& src, Image& dst);

		/// <summary>
		/// ガンマ補正を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="gamma">
		/// ガンマ値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void GammaCorrect(const Image& src, Image& dst, double gamma);

		/// <summary>
		/// 閾値処理を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <param name="inverse">
		/// 結果の白黒の反転
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Threshold(const Image& src, Image& dst, uint8 threshold, bool inverse = false);

		/// <summary>
		/// 適応的な閾値処理を行います。
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="method">
		/// 適応的閾値アルゴリズム
		/// </param>
		/// <param name="blockSize">
		/// 閾値を求めるために利用される近傍領域のサイズ。奇数
		/// </param>
		/// <param name="c">
		/// 平均または加重平均から引かれる定数
		/// </param>
		/// <param name="inverse">
		/// 結果の白黒の反転
		/// </param>
		/// <remarks>
		/// http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void AdaptiveThreshold(const Image& src, Image& dst, AdaptiveMethod method, int32 blockSize, int32 c, bool inverse = false);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Mosaic(const Image& src, Image& dst, int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Spread(const Image& src, Image& dst, int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Blur(const Image& src, Image& dst, int32 horizontal, int32 vertical);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="apertureSize">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void MedianBlur(const Image& src, Image& dst, int32 apertureSize);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="horizontal">
		/// 
		/// </param>
		/// <param name="vertical">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void GaussianBlur(const Image& src, Image& dst, int32 horizontal, int32 vertical);
	
		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="iterations">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Dilate(const Image& src, Image& dst, int32 iterations = 1);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="iterations">
		/// 
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Erode(const Image& src, Image& dst, int32 iterations = 1);

		/// <summary>
		/// 画像に塗りつぶし処理を行います。
		/// </summary>
		/// <param name="src">
		/// 塗りつぶし対象の画像
		/// </param>
		/// <param name="dst">
		/// 塗りつぶした結果の画像のコピー先
		/// </param>
		/// <param name="pos">
		/// 塗りつぶし開始位置
		/// </param>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		/// <param name="connectivity">
		/// 塗りつぶされるかどうかの接続性チェックの方式
		/// </param>
		/// <param name="lowerDifference">
		/// 塗りつぶされる色の許容範囲
		/// </param>
		/// <param name="upperDifference">
		/// 塗りつぶされる色の許容範囲
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void FloodFill(const Image& src, Image& dst, const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 
		/// </param>
		/// <param name="dst">
		/// 
		/// </param>
		/// <param name="width">
		/// 
		/// </param>
		/// <param name="height">
		/// 
		/// </param>
		/// <param name="interpolation">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		void Scale(const Image& src, Image& dst, int32 width, int32 height, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 
		/// </param>
		/// <param name="dst">
		/// 
		/// </param>
		/// <param name="size">
		/// 
		/// </param>
		/// <param name="interpolation">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		void Scale(const Image& src, Image& dst, const Size& size, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 
		/// </param>
		/// <param name="dst">
		/// 
		/// </param>
		/// <param name="scaling">
		/// 
		/// </param>
		/// <param name="interpolation">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		void Scale(const Image& src, Image& dst, double scaling, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="width">
		/// 
		/// </param>
		/// <param name="height">
		/// 
		/// </param>
		/// <param name="scaleUp">
		/// 
		/// </param>
		/// <param name="interpolation">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		void Fit(const Image& src, Image& dst, int32 width, int32 height, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="size">
		/// 
		/// </param>
		/// <param name="scaleUp">
		/// 
		/// </param>
		/// <param name="interpolation">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		void Fit(const Image& src, Image& dst, const Size& size, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SwapARGBtoABGR(const Image& src, Image& dst);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		Image GenerateMip(const Image& src);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="dx">
		/// 
		/// </param>
		/// <param name="dy">
		/// 
		/// </param>
		/// <param name="apertureSize">
		/// 
		/// </param>
		/// <remarks>
		/// 入力と出力を同じ Image にすることはできません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void Sobel(const Image& src, Image& dst, int32 dx = 1, int32 dy = 1, int32 apertureSize = 3);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="apertureSize">
		/// 
		/// </param>
		/// <remarks>
		/// 入力と出力を同じ Image にすることはできません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void Laplacian(const Image& src, Image& dst, int32 apertureSize = 3);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="src">
		/// 入力画像
		/// </param>
		/// <param name="dst">
		/// 出力画像
		/// </param>
		/// <param name="lowThreshold">
		/// 
		/// </param>
		/// <param name="highThreshold">
		/// 
		/// </param>
		/// <param name="apertureSize">
		/// 
		/// </param>
		/// <param name="useL2Gradient">
		/// 
		/// </param>
		/// <remarks>
		/// 入力と出力を同じ Image にすることはできません。
		/// </remarks>
		/// <returns>
		/// 
		/// </returns>
		void Canny(const Image& src, Image& dst, uint8 lowThreshold, uint8 highThreshold, int32 apertureSize = 3, bool useL2Gradient = false);

		void EdgePreservingFilter(const Image& src, Image& dst, EdgePreservingFilterType filterType = EdgePreservingFilterType::Recursive, _Field_range_(0.0, 200.0) double sigma_s = 60, _Field_range_(0.0, 1.0) double sigma_r = 0.4);

		void DetailEnhance(const Image& src, Image& dst, _Field_range_(0.0, 200.0) double sigma_s = 10, _Field_range_(0.0, 1.0) double sigma_r = 0.15);

		void Stylization(const Image& src, Image& dst, _Field_range_(0.0, 200.0) double sigma_s = 60, _Field_range_(0.0, 1.0) double sigma_r = 0.07);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="image1">
		/// 
		/// </param>
		/// <param name="image2">
		/// 
		/// </param>
		/// <remarks>
		/// 比較する画像は同じサイズである必要があります。
		/// </remarks>
		/// <returns>
		/// RGB 各チャンネルの SSIM
		/// </returns>
		ColorF SSIM(const Image& image1, const Image& image2);

		/// <summary>
		/// 画像から人物の顔を検出します
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="cascadeType">
		/// 画像の種類
		/// </param>
		/// <param name="minNeighbors">
		/// 検出の厳しさ
		/// </param>
		/// <param name="minSize">
		/// 検出する顔の最小サイズ（ピクセル）
		/// </param>
		/// <param name="maxSize">
		/// 検出する顔の最大サイズ(ピクセル）。指定しない場合 { 0, 0 }
		/// </param>
		/// <remarks>
		/// 検出する顔のサイズの範囲を絞ればパフォーマンスが向上します。
		/// </remarks>
		/// <returns>
		/// 検出された顔の領域の一覧
		/// </returns>
		Array<Rect> DetectFaces(const Image& image, CascadeType cascadeType = CascadeType::Photo, int32 minNeighbors = 3, const Point& minSize = { 30, 30 }, const Point& maxSize = { 0, 0 });

		/// <summary>
		/// 画像から最大の輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された Polygon
		/// </returns>
		Polygon FindExternalContour(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		/// <summary>
		/// 画像から輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された MultiPolygon
		/// </returns>
		MultiPolygon FindExternalContours(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		/// <summary>
		/// 画像から穴を含む最大の輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された Polygon
		/// </returns>
		Polygon FindContour(const Image& image, bool useAlpha = false, uint32 threshold = 127);

		/// <summary>
		/// 画像から穴を含む輪郭を抽出します。
		/// </summary>
		/// <param name="image">
		/// 画像
		/// </param>
		/// <param name="useAlpha">
		/// 輪郭抽出に画像のグレースケール値を使う場合は false, アルファ値を使う場合は true
		/// </param>
		/// <param name="threshold">
		/// 閾値
		/// </param>
		/// <returns>
		/// 輪郭から構成された MultiPolygon
		/// </returns>
		MultiPolygon FindContours(const Image& image, bool useAlpha = false, uint32 threshold = 127);
	}
}

namespace std
{
	inline void swap(s3d::Image& x, s3d::Image& y)
	{
		x.swap(y);
	}
}
