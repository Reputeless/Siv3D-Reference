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
# include "Optional.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// タッチの情報
	/// </summary>
	struct Touch
	{
		/// <summary>
		/// クライアント座標系でのタッチ位置
		/// </summary>
		Point pos;

		/// <summary>
		/// スクリーン座標系でのタッチ位置
		/// </summary>
		Point screenPos;

		/// <summary>
		/// クライアント座標系での 1 フレーム前のタッチ位置の Optional, タッチされていなかった場合は none
		/// </summary>
		Optional<Point> previousPos;

		/// <summary>
		/// スクリーン座標系での 1 フレーム前のタッチ位置の Optional, タッチされていなかった場合は none
		/// </summary>
		Optional<Point> previousScreenPos;

		/// <summary>
		/// タッチの ID
		/// </summary>
		uint32 id;

		/// <summary>
		/// タッチされた瞬間であるかを示します。
		/// </summary>
		Property_Get(bool, clicked) const { return !previousPos; }
	};
}
