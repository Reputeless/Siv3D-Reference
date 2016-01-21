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
# include "Window.hpp"

namespace s3d
{
	/// <summary>
	/// スクリーンキャプチャ
	/// </summary>
	/// <remarks>
	/// 背景色やスクリーンショットに関する機能を提供します。
	/// </remarks>
	namespace ScreenCapture
	{
		/// <summary>
		/// 現在のフレームのスクリーンショットを保存します。
		/// </summary>
		/// <remarks>
		/// スクリーンショットは "実行ファイル/Screenshot/" フォルダに保存されます。
		/// 撮影されたスクリーンショットは次のフレームで ScreenCapture::GetFrame() を通して取得できます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void Save();

		/// <summary>
		/// 現在のフレームのスクリーンショットを保存します。
		/// </summary>
		/// <param name="path">
		/// スクリーンショットを保存するパス
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Save(const FilePath& path);

		/// <summary>
		/// 現在のフレームのスクリーンショットをメモリ上に保存します。
		/// </summary>
		/// <remarks>
		/// 撮影されたスクリーンショットは次のフレームで ScreenCapture::GetFrame() を通して取得できます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void Request();

		/// <summary>
		/// 新しいスクリーンショットがあるかを返します。
		/// </summary>
		/// <remarks>
		/// 直前のフレームで ScreenCapture::Request() を呼び、
		/// 現在のフレームで ScreenCapture::GetFrmae() を呼んでいないときに true を返します。
		/// </remarks>
		/// <returns>
		/// 新しいスクリーンショットがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewFrame();

		/// <summary>
		/// メモリ上に保存されたスクリーンショットを取得します。
		/// </summary>
		/// <remarks>
		/// 以前のフレームで Graphics::ReceiveScreenCapture()　が呼ばれていないといけません。
		/// </remarks>
		/// <returns>
		/// 保存されているスクリーンショット。スクリーンショットが保存されていない場合は空の画像
		/// </returns>
		const Image& GetFrame();

		/// <summary>
		/// スクリーンショットを取得します。
		/// </summary>
		/// <param name="image">
		/// スクリーンショットのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetFrame(Image& image);

		/// <summary>
		/// スクリーンショットを取得します。
		/// </summary>
		/// <param name="texture">
		/// スクリーンショットのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetFrame(DynamicTexture& texture);

		bool BeginGIF(const Size& size = Window::Size()/2);

		bool BeginGIF(const FilePath& path, const Size& size = Window::Size() / 2);

		void EndGIF();


		bool BeginVideo(const Size& size = Window::Size());

		bool BeginVideo(const FilePath& path, const Size& size = Window::Size() / 2);

		void EndVideo();


		void EnableScreenshot(bool enabled);

		void EnableVideoCapture(bool enabled);


		void GetDesktopBackground(Image& image);

		void GetScreen(Image& image);
	}
}
