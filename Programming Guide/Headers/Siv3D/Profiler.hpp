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
# include "ApplicationUtility.hpp"

namespace s3d
{
	/// <summary>
	/// グラフィックスのプロファイリング
	/// </summary>
	struct GraphicsProfile
	{
		/// <summary>
		/// 直前のフレームの Deferred レンダリングでの Draw call の回数
		/// </summary>
		uint32 drawCallsDeferred = 0;
		
		/// <summary>
		/// 直前のフレームの Forward レンダリングでの Draw call の回数
		/// </summary>
		uint32 drawCallsForward = 0;

		/// <summary>
		/// 直前のフレームの 2D レンダリングでの Draw call の回数
		/// </summary>
		uint32 drawCalls2D = 0;

		/// <summary>
		/// 直前のフレームの エンジン内部で呼ばれた Draw call の回数
		/// </summary>
		uint32 drawCallsEngine = 0;

		/// <summary>
		/// 直前のフレームの Draw call の合計数
		/// </summary>
		uint32 num_drawCalls() const
		{
			return drawCallsDeferred
				+ drawCallsForward
				+ drawCalls2D
				+ drawCallsEngine;
		}

		/// <summary>
		/// 直前のフレームの Draw call の回数を画面に表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void print() const
		{
			Println(L"Draw Calls");
			Println(L"- Deferred\t: ", drawCallsDeferred);
			Println(L"- Forward\t: ", drawCallsForward);
			Println(L"- 2D\t\t: ", drawCalls2D);
			Println(L"- Engine\t: ", drawCallsEngine);
		}
	};

	/// <summary>
	/// プロファイリング
	/// </summary>
	/// <remarks>
	/// プロファイリング機能を提供します。
	/// </remarks>
	namespace Profiler
	{
		/// <summary>
		/// 実測のフレームレートを取得します。
		/// </summary>
		/// <returns>
		/// フレームレート
		/// </returns>
		int32 FPS();

		/// <summary>
		/// 直前のフレームのグラフィックスプロファイルを取得します。
		/// </summary>
		/// <returns>
		/// 直前のフレームのグラフィックスプロファイル
		/// </returns>
		GraphicsProfile Graphics();

		void EnableWarning(bool enabled);
	}
}
