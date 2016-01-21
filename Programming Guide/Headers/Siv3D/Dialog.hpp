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
# include "String.hpp"
# include "FileSystem.hpp"
# include "Font.hpp"

namespace s3d
{
	/// <summary>
	/// 拡張子フィルタ
	/// </summary>
	/// <remarks>
	/// ファイルダイアログで検索する拡張子を示します。
	/// </remarks>
	enum class ExtensionFilter
	{
		/// <summary>
		/// bmp
		/// </summary>
		BMP,
		
		/// <summary>
		/// png
		/// </summary>
		PNG,
		
		/// <summary>
		/// jpg, jpeg
		/// </summary>
		JPEG,
		
		/// <summary>
		/// gif
		/// </summary>
		GIF,
		
		/// <summary>
		/// tga
		/// </summary>
		TGA,
		
		/// <summary>
		/// dds
		/// </summary>
		DDS,
		
		/// <summary>
		/// webp
		/// </summary>
		WebP,
		
		/// <summary>
		/// 
		/// </summary>
		JPEG2000,
		
		/// <summary>
		/// tif, tiff
		/// </summary>
		TIFF,
		
		/// <summary>
		/// ppm
		/// </summary>
		PPM,

		/// <summary>
		/// BMP, PNG, JPEG, GIF の組み合わせ
		/// </summary>
		BasicImage,

		/// <summary>
		/// すべての画像ファイル
		/// </summary>
		AllImage,

		/// <summary>
		/// wav
		/// </summary>
		WAVE,
		
		/// <summary>
		/// mp3
		/// </summary>
		MP3,
		
		/// <summary>
		/// ogg
		/// </summary>
		OggVorbis,
		
		/// <summary>
		/// m4a
		/// </summary>
		AAC,
		
		/// <summary>
		/// wma
		/// </summary>
		WMA,

		/// <summary>
		/// すべてのサウンドファイル
		/// </summary>
		AllSound,

		/// <summary>
		/// mid, midi
		/// </summary>
		MIDI,

		/// <summary>
		/// txt
		/// </summary>
		Text,
		
		/// <summary>
		/// ini
		/// </summary>
		INI,
		
		/// <summary>
		/// xml
		/// </summary>
		XML,
		
		/// <summary>
		/// csv
		/// </summary>
		CSV,
		
		/// <summary>
		/// avi
		/// </summary>
		AVI,

		/// <summary>
		/// mp4
		/// </summary>
		MP4,

		/// <summary>
		/// wmv
		/// </summary>
		WMV,

		/// <summary>
		/// mov
		/// </summary>
		MOV,

		/// <summary>
		/// すべてのムービーファイル
		/// </summary>
		AllVideo,

		/// <summary>
		/// 全ての形式
		/// </summary>
		All,
	};

	/// <summary>
	/// ファイルダイアログで検索するフィルタの定義
	/// </summary>
	struct ExtensionFilterPair
	{
		String description, pattern;

		ExtensionFilterPair() = default;

		ExtensionFilterPair(ExtensionFilter type);

		ExtensionFilterPair(const String& _description, const String& _pattern);
	};

	/// <summary>
	/// ダイアログ
	/// </summary>
	/// <remarks>
	/// ダイアログの機能を提供します。
	/// </remarks>
	namespace Dialog
	{
		/// <summary>
		/// ファイルオープンダイアログを使ってファイルのパスを選択します。
		/// </summary>
		/// <param name="filters">
		/// 検索するファイル形式を示すフィルタ
		/// </param>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// フィルタの例:
		/// PNG ファイルのみ		{ ExtensionFilter::PNG }
		/// PNG / JPEG ファイル	{ ExtensionFilter::PNG, ExtensionFilter::JPEG }
		/// HTML ファイル			{ { L"HTML ファイル (*.html;*.htm)", L"*.html;*.htm" } }
		/// 独自の拡張子 (.aaa)	{ { L"説明 (*.aaa)", L"*.aaa" } }
		/// 独自の拡張子 (.aaa) と (.bbb)	{ { L"説明 (*.aaa)", L"*.aaa" }, { L"説明 (*.bbb)", L"*.bbb" }}
		/// </remarks>
		/// <returns>
		/// 選択されたファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		Optional<FilePath> GetOpen(const Array<ExtensionFilterPair>& filters, const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使ってファイルのパスを選択します。
		/// </summary>
		/// <param name="filters">
		/// 検索するファイル形式を示すフィルタ
		/// </param>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// フィルタの例:
		/// PNG ファイルのみ		{ ExtensionFilter::PNG }
		/// PNG / JPEG ファイル	{ ExtensionFilter::PNG, ExtensionFilter::JPEG }
		/// HTML ファイル			{ { L"HTML ファイル (*.html;*.htm)", L"*.html;*.htm" } }
		/// 独自の拡張子 (.aaa)	{ { L"説明 (*.aaa)", L"*.aaa" } }
		/// 独自の拡張子 (.aaa) と (.bbb)	{ { L"説明 (*.aaa)", L"*.aaa" }, { L"説明 (*.bbb)", L"*.bbb" }}
		/// </remarks>
		/// <returns>
		/// 選択されたファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		Optional<FilePath> GetSave(const Array<ExtensionFilterPair>& filters, const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 選択された画像ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenBasicImage(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された画像ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenImage(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使ってオーディオファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたオーディオファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenSound(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使って MIDI ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された MIDI ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenMidi(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使ってテキストファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたテキストファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenText(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使って動画ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された動画ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenVideo(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルオープンダイアログを使ってファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetOpenAll(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 選択されたオーディオファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveBasicImage(const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使って画像ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された画像ファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveImage(const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使ってオーディオファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたオーディオファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveSound(const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使ってテキストファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたテキストファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveText(const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使って動画ファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択された動画のパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveVideo(const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイル保存ダイアログを使ってファイルのパスを選択します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたファイルのパスの Optional, キャンセルされた場合は none
		/// </returns>
		inline Optional<FilePath> GetSaveAll(const String& title = L"名前をつけて保存", const FilePath& initialPath = L"");

		/// <summary>
		/// カラーダイアログで選択された Color を返します。
		/// </summary>
		/// <returns>
		/// 選択された Color の Optional, キャンセルされた場合は none
		/// </returns>
		Optional<Color> GetColor();

		/// <summary>
		/// カラーダイアログで選択された Color を返します。
		/// </summary>
		/// <param name="defaultColor">
		/// キャンセルされた場合に返す Color
		/// </param>
		/// <returns>
		/// 選択された Color, キャンセルされた場合は defaultColor
		/// </returns>
		Color GetColor(const Color& defaultColor);

		/// <summary>
		/// フォルダ選択ダイアログで選択されたフォルダのパスを返します。
		/// </summary>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 選択されたフォルダのパスの Optional, キャンセルされた場合は none
		/// </returns>
		Optional<FilePath> GetFolder(const FilePath& initialPath = FileSystem::InitialPath());

		/// <summary>
		/// フォントダイアログで選択した FontProperty を返します。
		/// </summary>
		/// <returns>
		/// 選択された FontProperty の Optional, キャンセルされた場合は none
		/// </returns>
		Optional<FontProperty> GetFont();

		/// <summary>
		/// フォントダイアログで選択した FontProperty を返します。
		/// </summary>
		/// <param name="defaultFont">
		/// キャンセルされた場合に返す FontProperty
		/// </param>
		/// <returns>
		/// 選択された FontProperty, キャンセルされた場合は defaultFont
		/// </returns>
		FontProperty GetFont(const FontProperty& defaultFont);

		/// <summary>
		/// ファイルダイアログで選択した画像ファイルから Image を作成します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 作成された Image
		/// </returns>
		Image OpenBasicImage(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択した画像ファイルから Image を作成します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 作成された Image
		/// </returns>
		Image OpenImage(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択した画像ファイルから Texture を作成します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 作成された Texture
		/// </returns>
		Texture OpenBasicTexture(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択した画像ファイルから Texture を作成します。
		/// </summary>
		/// <param name="desc">
		/// 作成するテクスチャの設定
		/// </param>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <remarks>
		/// BMP, PNG, JPEG, GIF 形式の画像ファイルのみ表示されます。
		/// </remarks>
		/// <returns>
		/// 作成された Texture
		/// </returns>
		Texture OpenBasicTexture(const TextureDesc& desc, const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択した画像ファイルから Texture を作成します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 作成された Texture
		/// </returns>
		Texture OpenTexture(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択した画像ファイルから Texture を作成します。
		/// </summary>
		/// <param name="desc">
		/// 作成するテクスチャの設定
		/// </param>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 作成された Texture
		/// </returns>
		Texture OpenTexture(const TextureDesc& desc, const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択したオーディオファイルから Wave を作成します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 作成された Wave
		/// </returns>
		Wave OpenWave(const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// ファイルダイアログで選択したオーディオファイルから Sound を作成します。
		/// </summary>
		/// <param name="title">
		/// ファイルダイアログのタイトル
		/// </param>
		/// <param name="initialPath">
		/// ダイアログに表示する初期フォルダ
		/// </param>
		/// <returns>
		/// 作成された Sound
		/// </returns>
		Sound OpenSound(const String& title = L"開く", const FilePath& initialPath = L"");

		Sound OpenSound(const SoundLoop& loop, SoundDesc desc, double maxSpeed, const String& title = L"開く", const FilePath& initialPath = L"");

		/// <summary>
		/// フォントダイアログを使って Font を作成します。
		/// </summary>
		/// <returns>
		/// 作成された Font
		/// </returns>
		Font OpenFont();
	}
}

# include "Dialog.inl"
