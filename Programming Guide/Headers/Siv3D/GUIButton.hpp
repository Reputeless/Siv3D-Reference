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
	class GUIButton : public IWidget
	{
	private:

		double m_pressedPressure = 0.0;

		bool m_pressed = false;

		bool m_mouseOver = false;

		bool m_pushed = false;

		bool m_enabled = true;

		String m_text;

		Point ItemSize() const;

		Point TextRegion() const;

		Rect MarginBox(const Point& offset) const;

		Rect PaddingBox(const Point& offset) const;

		Rect ItemBox(const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"Button";
			return name;
		}

		static std::shared_ptr<GUIButton> Create(const s3d::String& label, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIButton>(label, true, style);
		}

		static std::shared_ptr<GUIButton> Create(const s3d::String& label, bool enabled, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIButton>(label, enabled, style);
		}

		GUIButton() {}

		GUIButton(const String& text, bool enabled, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		bool& getEnabled();

		String& getText();

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, pressed) const;

		Property_Get(bool, pushed) const;
	};

	class GUIButtonWrapper
	{
	public:

		using WidgetType = GUIButton;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUIButtonWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, enabled(m_widget->getEnabled())
			, text(m_widget->getText())
			, style(m_widget->m_style) {}

		GUIButtonWrapper& operator = (const GUIButtonWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		bool& enabled;

		String& text;

		WidgetStyle& style;

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, pressed) const;

		Property_Get(bool, pushed) const;
	};
}
