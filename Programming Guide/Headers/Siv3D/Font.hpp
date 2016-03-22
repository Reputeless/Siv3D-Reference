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
# include "Handle.hpp"
# include "Color.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "PropertyMacro.hpp"
# include "KineticTypography.hpp"

namespace s3d
{
	/// <summary>
	/// 標準フォント
	/// </summary>
	struct Typeface
	{
		/// <summary>
		/// 標準 [UmePlus P Gothic]
		/// </summary>
		const static String Default;

		/// <summary>
		/// とても細い [M+ 1p thin]
		/// </summary>
		const static String Thin;

		/// <summary>
		/// 細い [M+ 1p light]
		/// </summary>
		const static String Light;

		/// <summary>
		/// 普通 [M+ 1p regular]
		/// </summary>
		const static String Regular;

		/// <summary>
		/// やや太い [M+ 1p medium]
		/// </summary>
		const static String Medium;

		/// <summary>
		/// 太い [M+ 1p bold]
		/// </summary>
		const static String Bold;

		/// <summary>
		/// とても太い [M+ 1p heavy]
		/// </summary>
		const static String Heavy;

		/// <summary>
		/// 非常に太い [M+ 1p black]
		/// </summary>
		const static String Black;
	};

	/// <summary>
	/// フォントのスタイル
	/// </summary>
	enum class FontStyle
	{
		/// <summary>
		/// レギュラー
		/// </summary>
		Regular,

		/// <summary>
		/// ボールド
		/// </summary>
		Bold,

		/// <summary>
		/// イタリック
		/// </summary>
		Italic,

		/// <summary>
		/// ボールドイタリック
		/// </summary>
		BoldItalic,

		/// <summary>
		/// ビットマップ
		/// </summary>
		Bitmap,

		/// <summary>
		/// ビットマップ・ボールド
		/// </summary>
		BitmapBold,

		/// <summary>
		/// ビットマップ・イタリック
		/// </summary>
		BitmapItalic,

		/// <summary>
		/// ビットマップ・ボールドイタリック
		/// </summary>
		BitmapBoldItalic,

		Outline,
	};

	/// <summary>
	/// フォントプロパティ
	/// </summary>
	struct FontProperty
	{
		FontProperty(const String& _name = L"Meiryo", int _size = 16, FontStyle _style = FontStyle::Regular)
			: name(_name)
			, size(_size)
			, style(_style) {}

		String name;

		int size;

		FontStyle style;
	};

	struct TextOutlineStyle
	{
		constexpr TextOutlineStyle() = default;

		constexpr TextOutlineStyle(const Color& _outlineColor, const Color& _fillColor, double _thickness)
			: outlineColor(_outlineColor)
			, fillColor(_fillColor)
			, thickness(_thickness) {}

		Color outlineColor = Color(0);

		Color fillColor = Color(255);

		double thickness = 1.0;
	};

	/// <summary>
	/// フォント
	/// </summary>
	class Font
	{
	private:

		class Handle{};

		using FontHandle = Siv3DHandle<Handle>;

		std::shared_ptr<FontHandle> m_handle;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Font();

		/// <summary>
		/// フォントを作成します。
		/// </summary>
		/// <param name="size">
		/// フォントのサイズ
		/// </param>
		/// <param name="name">
		/// フォント名
		/// </param>
		/// <param name="style">
		/// フォントのスタイル
		/// </param>
		explicit Font(int32 size, const String& name = Typeface::Default, FontStyle style = FontStyle::Regular);

		/// <summary>
		/// フォントを作成します。
		/// </summary>
		/// <param name="fontProperty">
		/// フォントプロパティ
		/// </param>
		explicit Font(const FontProperty& fontProperty);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Font();

		/// <summary>
		/// フォントをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じフォントが使われていない場合、フォントのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		String name() const;

		int32 size() const;

		FontStyle style() const;

		TextOutlineStyle outlineStyle() const;

		Property_Get(int32, height) const;

		Property_Get(int32, ascent) const;

		bool operator == (const Font& font) const;

		bool operator != (const Font& font) const;

		void changeOutlineStyle(const TextOutlineStyle& outlineStyle) const;

		Rect
			write(
			Image& image,
			const String& text,
			int x,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			write(
			Image& image,
			const String& text,
			const Point& pos = { 0, 0 },
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwrite(
			Image& image,
			const String& text,
			int x,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwrite(
			Image& image,
			const String& text,
			const Point& pos = { 0, 0 },
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			writeCenter(
			Image& image,
			const String& text,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			writeCenter(
			Image& image,
			const String& text,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			writeCenter(
			Image& image,
			const String& text,
			const Point& pos,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwriteCenter(
			Image& image,
			const String& text,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwriteCenter(
			Image& image,
			const String& text,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwriteCenter(
			Image& image,
			const String& text,
			const Point& pos,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			region(
			const String& text,
			double lineHeight
			) const;

		Rect
			region(
			const String& text,
			const Point& pos = { 0, 0 },
			double lineHeight = 1.0
			) const;

		Rect
			region(
			const String& text,
			int x,
			int y,
			double lineHeight = 1.0
			) const;

		RectF
			region(
			const String& text,
			double x,
			double y,
			double lineHeight = 1.0
			) const;

		RectF
			region(
			const String& text,
			const Vec2& pos,
			double lineHeight = 1.0
			) const;

		RectF
			regionCenter(
			const String& text,
			double y,
			double lineHeight = 1.0
			) const;

		RectF
			regionCenter(
			const String& text,
			const Vec2& pos,
			double lineHeight = 1.0
			) const;

		size_t drawableCharacters(
			const String& text,
			double width
			) const;

		RectF
			draw(
			const String& text,
			double x,
			double y,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		RectF
			draw(
			const String& text,
			const Vec2& pos = { 0.0, 0.0 },
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		void
			drawKinetic(
			const String& text,
			double x,
			double y,
			KineticTypographyFunction_t kineticFunction,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		void
			drawKinetic(
			const String& text,
			const Vec2& pos,
			KineticTypographyFunction_t kineticFunction,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		RectF
			drawCenter(
			const String& text,
			double y,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		RectF
			drawCenter(
			const String& text,
			const Vec2& pos,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		const TextureRegion
			getTexture(
			wchar_t ch
			) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		DrawableString operator()(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="args">
		/// 文字列に変換するデータ
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		template <class ... Args>
		inline DrawableString operator()(const Args& ... args) const;
	};

	class DrawableString
	{
	private:

		friend class Font;

		const Font& m_font;

		const String m_text;

		DrawableString(const DrawableString&) = default;

		DrawableString& operator = (const DrawableString&) = delete;

		DrawableString(const Font& font, const String& text)
			: m_font(font)
			, m_text(text) {}

		DrawableString(const Font& font, String&& text)
			: m_font(font)
			, m_text(std::move(text)) {}

	public:

		Rect
			write(
			Image& image,
			int x,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			write(
			Image& image,
			const Point& pos = { 0, 0 },
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwrite(
			Image& image,
			int x,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwrite(
			Image& image,
			const Point& pos = { 0, 0 },
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			writeCenter(
			Image& image,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			writeCenter(
			Image& image,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			writeCenter(
			Image& image,
			const Point& pos,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwriteCenter(
			Image& image,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwriteCenter(
			Image& image,
			int y,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			overwriteCenter(
			Image& image,
			const Point& pos,
			const Color& color = Palette::Black,
			double lineHeight = 1.0
			) const;

		Rect
			region(
			double lineHeight
			) const;

		Rect
			region(
			const Point& pos = { 0, 0 },
			double lineHeight = 1.0
			) const;

		Rect
			region(
			int x,
			int y,
			double lineHeight = 1.0
			) const;

		RectF
			region(
			double x,
			double y,
			double lineHeight = 1.0
			) const;

		RectF
			region(
			const Vec2& pos,
			double lineHeight = 1.0
			) const;

		RectF
			regionCenter(
			double y,
			double lineHeight = 1.0
			) const;

		RectF
			regionCenter(
			const Vec2& pos,
			double lineHeight = 1.0
			) const;

		/// <summary>
		/// テキストを描きます。
		/// </summary>
		/// <param name="x">
		/// 描き始めの位置の X 座標
		/// </param>
		/// <param name="y">
		/// 描き始めの位置の Y 座標
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <param name="lineHeight">
		/// 行間のスケール
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF
			draw(
			double x,
			double y,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		/// <summary>
		/// テキストを描きます。
		/// </summary>
		/// <param name="pos">
		/// 描き始めの位置
		/// </param>
		/// <param name="color">
		/// 色
		/// </param>
		/// <param name="lineHeight">
		/// 行間のスケール
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF
			draw(
			const Vec2& pos = { 0.0, 0.0 },
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		void
			drawKinetic(
			double x,
			double y,
			KineticTypographyFunction_t kineticFunction,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		void
			drawKinetic(
			const Vec2& pos,
			KineticTypographyFunction_t kineticFunction,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		RectF
			drawCenter(
			double y,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;

		RectF
			drawCenter(
				double x,
				double y,
				const Color& color = Palette::White,
				double lineHeight = 1.0
				) const;

		RectF
			drawCenter(
			const Vec2& pos,
			const Color& color = Palette::White,
			double lineHeight = 1.0
			) const;
	};

	/// <summary>
	/// 描画するテキストを作成します。
	/// </summary>
	/// <param name="args">
	/// 文字列に変換するデータ
	/// </param>
	/// <returns>
	/// DrawableString
	/// </returns>
	template <class ... Args>
	inline DrawableString Font::operator()(const Args& ... args) const
	{
		return DrawableString(*this, Format(args...));
	}

	struct TextStyle
	{
		constexpr TextStyle() = default;

		constexpr TextStyle(const Color& _color, double _lineHeight = 1.0)
			: lineHeight(_lineHeight)
			, color(_color) {}

		double lineHeight = 1.0;

		Color color = Palette::White;
	};

	/// <summary>
	/// フォント管理
	/// </summary>
	/// <remarks>
	/// 
	/// </remarks>
	namespace FontManager
	{
		/// <summary>
		/// システムにフォントを一時的に登録します。
		/// </summary>
		/// <param name="path">
		/// 登録するフォントファイル
		/// </param>
		/// <remarks>
		/// コンピュータにインストールされていないフォントが使えるようになります。
		/// </remarks>
		/// <returns>
		/// フォントの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Register(const FilePath& path);

		bool Register(IReader&& reader);
	}
}