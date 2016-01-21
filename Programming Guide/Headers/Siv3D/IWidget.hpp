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
# include "WidgetStyle.hpp"
# include "String.hpp"

namespace s3d
{
	class IWidget
	{
	public:

		WidgetStyle m_style;

		IWidget() = default;

		IWidget(const WidgetStyle& style)
			: m_style(style) {}

		virtual ~IWidget() = default;

		virtual const String& getWidgetName() const = 0;

		virtual Size getSize() const = 0;

		virtual bool forceNewLineBefore() const = 0;

		virtual bool forceNewLineAfter() const = 0;

		virtual void update(const WidgetState& state) = 0;

		virtual void draw(const WidgetState& state) const = 0;
	};
}
