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
# include "Unspecified.hpp"

namespace s3d
{
	class GUIText : public IWidget
	{
	private:

		String m_text;

		Point ItemSize() const;

		Point TextRegion() const;

		Rect MarginBox(const Point& offset) const;

		Rect PaddingBox(const Point& offset) const;

		Rect ItemBox(const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"Text";
			return name;
		}

		static std::shared_ptr<GUIText> Create(const String& text, const Optional<int> width)
		{
			WidgetStyle style;
			style.width = width;

			return std::make_shared<GUIText>(text, style);
		}

		static std::shared_ptr<GUIText> Create(const String& text, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIText>(text, style);
		}

		GUIText() {}

		GUIText(const String& text, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		String& getText();
	};

	class GUITextWrapper
	{
	public:

		using WidgetType = GUIText;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUITextWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, text(m_widget->getText())
			, style(m_widget->m_style) {}

		GUITextWrapper& operator = (const GUITextWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		String& text;
	
		WidgetStyle& style;
	};
}
