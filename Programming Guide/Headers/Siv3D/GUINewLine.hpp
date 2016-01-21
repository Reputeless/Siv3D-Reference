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
# include "IWidget.hpp"
# include "WidgetStyle.hpp"

namespace s3d
{
	class GUINewLine : public IWidget
	{
	public:

		static const String& Name()
		{
			static const String name = L"NewLine";
			return name;
		}

		static std::shared_ptr<GUINewLine> Create(const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUINewLine>(style);
		}

		GUINewLine() {}

		GUINewLine(const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;
	};

	class GUINewLineWrapper
	{
	public:

		using WidgetType = GUINewLine;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUINewLineWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, style(m_widget->m_style) {}

		GUINewLineWrapper& operator = (const GUINewLineWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		WidgetStyle& style;
	};
}
