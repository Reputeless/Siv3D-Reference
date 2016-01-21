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
# include "PropertyMacro.hpp"
# include "PointVector.hpp"
# include "Texture.hpp"
# include "Font.hpp"

namespace s3d
{
	namespace GUIManager
	{
		const Font& GetDefaultFont();
	}

	/// <summary>
	/// パディング
	/// </summary>
	struct Padding
	{
		Padding() = default;

		constexpr Padding(int32 padding)
			: Padding(padding, padding, padding, padding) {}

		constexpr Padding(int32 _topBottom, int32 _rightLeft)
			: Padding(_topBottom, _rightLeft, _topBottom, _rightLeft) {}

		constexpr Padding(int32 _top, int32 _rightLeft, int32 _bottom)
			: Padding(_top, _rightLeft, _bottom, _rightLeft) {}

		constexpr Padding(int32 _top, int32 _right, int32 _bottom, int32 _left)
			: top(_top)
			, right(_right)
			, bottom(_bottom)
			, left(_left) {}

		int32 top = 0;

		int32 right = 0;

		int32 bottom = 0;

		int32 left = 0;

		Property_Get(Point, lt) const { return{ left, top }; }

		Property_Get(Point, rb) const { return{ right, bottom }; }
	};

	/// <summary>
	/// マージン
	/// </summary>
	struct Margin
	{
		Margin() = default;

		constexpr Margin(int32 padding)
			: Margin(padding, padding, padding, padding) {}

		constexpr Margin(int32 _topBottom, int32 _rightLeft)
			: Margin(_topBottom, _rightLeft, _topBottom, _rightLeft) {}

		constexpr Margin(int32 _top, int32 _rightLeft, int32 _bottom)
			: Margin(_top, _rightLeft, _bottom, _rightLeft) {}

		constexpr Margin(int32 _top, int32 _right, int32 _bottom, int32 _left)
			: top(_top)
			, right(_right)
			, bottom(_bottom)
			, left(_left) {}

		int32 top = 0;

		int32 right = 0;

		int32 bottom = 0;

		int32 left = 0;

		Property_Get(Point, lt) const { return{ left, top }; }

		Property_Get(Point, rb) const { return{ right, bottom }; }
	};

	/// <summary>
	/// アライメント
	/// </summary>
	enum class Align
	{
		Left,

		Right,

		Center,
	};

	/// <summary>
	/// 背景画像の繰り返し方法
	/// </summary>
	enum class Repeat
	{
		None,

		ScaleX,

		ScaleY,

		ScaleXY,

		X,

		Y,

		XY,
	};

	/// <summary>
	/// GUI ウィンドウの背景
	/// </summary>
	struct Background
	{
		Optional<Texture> texture;

		Optional<Color> color;

		Optional<Repeat> repeat;
	};

	/// <summary>
	/// ウィジェットのスタイル
	/// </summary>
	struct WidgetStyle
	{
		Padding padding = Padding(0);

		Margin margin = Margin(5);

		Optional<Align> align;

		Background background;

		Optional<int32> width;

		Optional<Color> color;

		Font font = GUIManager::GetDefaultFont();
	};

	/// <summary>
	/// ウィジェットの更新と描画のための情報
	/// </summary>
	struct WidgetState
	{
		Point currentPos;

		Point size;

		bool showBoxModel;

		bool active;
	};
}
