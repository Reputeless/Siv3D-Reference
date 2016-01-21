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

namespace s3d
{
	/// <summary>
	/// グラフィックス
	/// </summary>
	/// <remarks>
	/// レンダリングに関する機能を提供します。
	/// </remarks>
	namespace Graphics
	{
		/// <summary>
		/// 背景色を設定します。
		/// </summary>
		/// <param name="color">
		/// 背景色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetBackground(const Color& color);

		/// <summary>
		/// これまで draw された 2D アイテムを 3D より先にレンダリングします。
		/// </summary>
		/// <remarks>
		/// 通常は 3D レンダリングの後に 2D アイテムがレンダリングされます。
		/// その順番を変える必要がある場合に使用します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void Render2D();

		[[deprecated("** Graphics::Render2DBackground() is a deprecated function. Use Graphics::Render2D() instead. **")]]
		bool Render2DBackground();


		const RenderTexture& GetSwapChainTexture();

		const Texture& GetDepthTexture();

		/// <summary>
		/// フルスクリーンモードで利用できる解像度の一覧を取得します。
		/// </summary>
		/// <remarks>
		/// これ以外の解像度を Window::SetFullscreen() に渡すと失敗します。
		/// </remarks>
		/// <returns>
		/// フルスクリーンモードで利用できる解像度の一覧
		/// </returns>
		Array<Size> GetFullScreenSize();

		bool IsVSyncEnabled();

		void SetVSyncEnabled(bool enabled);
	}
}
