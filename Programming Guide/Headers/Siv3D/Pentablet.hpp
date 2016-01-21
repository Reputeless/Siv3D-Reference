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

namespace s3d
{
	/// <summary>
	/// ペンタブレット
	/// </summary>
	/// <remarks>
	/// ペンタブレット入力の機能を提供します。
	/// </remarks>
	namespace Pentablet
	{
		/// <summary>
		/// ペンタブレットが使用可能かを調べます。
		/// </summary>
		/// <returns>
		/// ペンタブレットを使える場合 true, それ以外の場合は false
		/// </returns>
		bool IsAvailable();

		/// <summary>
		/// 接続されているペンタブレットが筆圧計測に対応しているかを調べます。
		/// </summary>
		/// <returns>
		/// 筆圧計測に対応している場合 true, それ以外の場合は false
		/// </returns>
		bool SupportsPressure();

		/// <summary>
		/// 筆圧を返します。
		/// </summary>
		/// <returns>
		/// 筆圧 [0.0-1.0]
		/// </returns>
		double Pressure();

		/// <summary>
		/// 地面に対するペンの傾きを取得します。
		/// </summary>
		/// <remarks>
		/// ペンが直立していると 90 になります。
		/// </remarks>
		/// <returns>
		/// 地面に対するペンの傾き（°）
		/// </returns>
		int DegreeXZ();

		/// <summary>
		/// 垂直な軸に対するペンの回転角度を取得します。
		/// </summary>
		/// <returns>
		/// 垂直な軸に対するペンの回転角度（°）。時計回りで [0-360]
		/// </returns>
		int DegreeY();
	}
}
