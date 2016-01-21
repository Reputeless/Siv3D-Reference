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
# include "Rectangle.hpp"

namespace s3d
{
	/// <summary>
	/// ウィンドウスタイル
	/// </summary>
	enum class WindowStyle
	{
		/// <summary>
		/// 通常のウィンドウ
		/// </summary>
		Fixed = 0x3,

		/// <summary>
		/// サイズが変更可能なウィンドウ
		/// </summary>
		Sizeable = 0x7,

		/// <summary>
		/// フレームが無いウィンドウ
		/// </summary>
		NonFrame = 0x1,
	};

	/// <summary>
	/// ウィンドウの状態
	/// </summary>
	struct WindowState
	{
		/// <summary>
		/// クライアント画面（描画可能域）の幅と高さ
		/// </summary>
		Size clientSize;

		/// <summary>
		/// 枠線を含めたウィンドウの幅と高さ
		/// </summary>
		Size windowSize;

		/// <summary>
		/// スクリーンの幅と高さ
		/// </summary>
		Size screenSize;

		double desktopScaling;

		/// <summary>
		/// ウィンドウの左上の位置
		/// </summary>
		Point windowPos;

		/// <summary>
		/// ウィンドウの枠線の幅と高さ
		/// </summary>
		Size frameSize;

		/// <summary>
		/// ウィンドウのタイトルバーの高さ
		/// </summary>
		int32 titleBarHeight;

		/// <summary>
		/// スクリーンのタスクバーの矩形範囲
		/// </summary>
		Rect taskbarRect;

		/// <summary>
		/// スクリーンのタスクバーの位置（下: 0 左: 1 上: 2 右: 3)
		/// </summary>
		int32 taskbarPos;

		/// <summary>
		/// ウィンドウスタイル
		/// </summary>
		WindowStyle style;

		/// <summary>
		/// フルスクリーンモードか
		/// </summary>
		bool fullscreen;

		/// <summary>
		/// スクリーンの解像度や向きが変更されたか
		/// </summary>
		bool displayChanged;

		/// <summary>
		/// カーソルがクライアント画面（描画可能域）上にあるか
		/// </summary>
		bool cursorOnClient;

		/// <summary>
		/// カーソルがウィンドウ上にあるか
		/// </summary>
		bool cursorOnWindow;

		/// <summary>
		/// ウィンドウが最小化されているか
		/// </summary>
		bool minimized;

		/// <summary>
		/// ウィンドウが最大化されているか
		/// </summary>
		bool maximized;

		/// <summary>
		/// ウィンドウがアクティブか
		/// </summary>
		bool focused;

		/// <summary>
		/// ウィンドウが移動中か
		/// </summary>
		bool windowMoving;

		/// <summary>
		/// ウィンドウがサイズ変更中か
		/// </summary>
		bool windowSizing;

		/// <summary>
		/// ウィンドウのタイトル
		/// </summary>
		String windowTitle;
	};

	/// <summary>
	/// ウィンドウ
	/// </summary>
	/// <remarks>
	/// ウィンドウの状態を管理します。
	/// </remarks>
	namespace Window
	{
		/// <summary>
		/// ウィンドウの状態を返します。
		/// </summary>
		/// <returns>
		/// 現在のウィンドウの情報を格納した WindowState 構造体への参照
		/// </returns>
		const WindowState& GetState();

		/// <summary>
		/// ウィンドウのクライアント領域のサイズを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域のサイズ
		/// </returns>
		s3d::Size Size();

		/// <summary>
		/// ウィンドウのクライアント領域の中央の座標を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の中央の座標
		/// </returns>
		Point Center();

		/// <summary>
		/// ウィンドウのクライアント領域の幅を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の幅(ピクセル）
		/// </returns>
		int32 Width();

		/// <summary>
		/// ウィンドウのクライアント領域の高さを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の高さ(ピクセル）
		/// </returns>
		int32 Height();

		/// <summary>
		/// ウィンドウのクライアント領域と同じサイズの Rect を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域と同じサイズの Rect
		/// </returns>
		Rect ClientRect();

		/// <summary>
		/// ウィンドウのアスペクト比を返します。
		/// </summary>
		/// <returns>
		/// 高さを 1 としたときの横の大きさ
		/// </returns>
		double AspectRatio();

		/// <summary>
		/// ウィンドウの左上の位置を返します。
		/// </summary>
		/// <returns>
		/// スクリーン座標系でのウィンドウの左上の位置
		/// </returns>
		Point GetPos();

		/// <summary>
		/// ウィンドウがアクティブであるかを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウがアクティブな場合 true, それ以外の場合は false
		/// </returns>
		bool Focused();

		/// <summary>
		/// ウィンドウに枠があるかを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウに枠がある場合 true, それ以外の場合は false
		/// </returns>
		bool Framed();

		/// <summary>
		/// サイズが変更なウィンドウであるかを返します。
		/// </summary>
		/// <returns>
		/// サイズが変更なウィンドウの場合 true, それ以外の場合は false
		/// </returns>
		bool Sizeable();

		/// <summary>
		/// ウィンドウモードであるかを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウモードの場合 true, それ以外の場合は false
		/// </returns>
		bool Windowed();

		/// <summary>
		/// フルスクリーンモードであるかを返します。
		/// </summary>
		/// <returns>
		/// フルスクリーンモードの場合 true, それ以外の場合は false
		/// </returns>
		bool IsFullSceen();

		/// <summary>
		/// ウィンドウが最小化されているかを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウが最小化されている場合 true, それ以外の場合は false
		/// </returns>
		bool Minimized();

		/// <summary>
		/// ウィンドウが最大化されているかを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウが最大化されている場合 true, それ以外の場合は false
		/// </returns>
		bool Maximized();

		/// <summary>
		/// ウィンドウのタイトルを設定します。
		/// </summary>
		/// <param name="title">
		/// タイトルにするテキスト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetTitle(const String& title);

		/// <summary>
		/// ウィンドウのタイトルを設定します。
		/// </summary>
		/// <param name="args">
		/// タイトルにするテキスト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <typename ... Args>
		inline void SetTitle(const Args& ... args)
		{
			SetTitle(Format(args...));
		}

		/// <summary>
		/// 現在のウィンドウのタイトルを取得します。
		/// </summary>
		/// <returns>
		/// ウィンドウのタイトル
		/// </returns>
		String GetTitle();

		/// <summary>
		/// ウィンドウのアイコンを設定します。
		/// </summary>
		/// <param name="image">
		/// アイコンに設定する画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetIcon(const Image& image);

		/// <summary>
		/// ウィンドウの位置を変更します。
		/// </summary>
		/// <param name="x">
		/// 新しいウィンドウ位置の x 座標
		/// </param>
		/// <param name="y">
		/// 新しいウィンドウ位置の y 座標
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetPos(int32 x, int32 y);

		/// <summary>
		/// ウィンドウの位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しいウィンドウ位置
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetPos(const Point& pos);

		/// <summary>
		/// ウィンドウを、タスクバーに重ならないよう左上に移動します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void ToUpperLeft();

		/// <summary>
		/// ウィンドウのサイズを変更します。
		/// </summary>
		/// <param name="width">
		/// 新しいウィンドウのクライアント領域の幅(ピクセル）
		/// </param>
		/// <param name="height">
		/// 新しいウィンドウのクライアント領域の高さ(ピクセル）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Resize(int32 width, int32 height);

		/// <summary>
		/// ウィンドウのサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しいウィンドウのクライアント領域のサイズ(ピクセル）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Resize(const s3d::Size& size);

		/// <summary>
		/// ウィンドウを最小化します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Minimize();

		/// <summary>
		/// 最小化、最大化されたウィンドウを元の大きさに戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Restore();

		/// <summary>
		/// ウィンドウを最大化します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Maximize();

		/// <summary>
		/// ウィンドウを中央に移動します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Centering();

		/// <summary>
		/// ウィンドウスタイルを変更します。
		/// </summary>
		/// <param name="style">
		/// 新しいウィンドウスタイル
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStyle(WindowStyle style);

		/// <summary>
		/// スクリーンモードを切り替えます。
		/// </summary>
		/// <param name="fullscreen">
		/// フルスクリーンの場合 true, ウィンドウモードの場合 false
		/// </param>
		/// <param name="size">
		/// 新しい解像度
		/// </param>
		/// <returns>
		/// 切り替えに成功した場合 true, 失敗した場合は false
		/// </returns>
		bool SetFullscreen(bool fullscreen, const s3d::Size& size);

		Point ClientToScreen(const Point& pos);

		Point ScreenToClient(const Point& pos);


		[[deprecated("** Window::SetVirtualFullscreen() is a deprecated function. Use Window::SetFullscreen() instead. **")]]
		bool SetVirtualFullscreen(const s3d::Size& size);
	}
}
