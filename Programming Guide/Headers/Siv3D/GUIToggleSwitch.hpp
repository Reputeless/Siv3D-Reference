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
	class GUIToggleSwitch : public IWidget
	{
	private:

		double m_pressedPressure = 0.0;

		bool m_isRight = false;

		bool m_hasChanged = false;

		bool m_pressed = false;

		bool m_mouseOver = false;

		bool m_enabled = true;

		String m_leftText;

		String m_rightText;

		Point ItemSize() const;

		Point TextRegion() const;

		Rect MarginBox(const Point& offset) const;

		Rect PaddingBox(const Point& offset) const;

		Rect ItemBox(const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"ToggleSwitch";
			return name;
		}

		static std::shared_ptr<GUIToggleSwitch> Create(const s3d::String& left, const s3d::String& right, bool isRight, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIToggleSwitch>(left, right, isRight, true, style);
		}

		static std::shared_ptr<GUIToggleSwitch> Create(const s3d::String& left, const s3d::String& right, bool isRight, bool enabled, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIToggleSwitch>(left, right, isRight, enabled, style);
		}

		GUIToggleSwitch() {}

		GUIToggleSwitch(const s3d::String& labelLeft, const s3d::String& labelRight, bool isRight, bool enabled, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		bool& getEnabled();

		Property_Get(bool, isRight) const;

		void setIsRight(bool isRight);

		String& getLeftText();

		String& getRightText();

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, pressed) const;

		Property_Get(bool, hasChanged) const;
	};

	class GUIToggleSwitchWrapper
	{
	public:

		using WidgetType = GUIToggleSwitch;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUIToggleSwitchWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, enabled(m_widget->getEnabled())
			, leftText(m_widget->getLeftText())
			, rightText(m_widget->getRightText())
			, style(m_widget->m_style) {}

		GUIToggleSwitchWrapper& operator = (const GUIToggleSwitchWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		bool& enabled;

		String& leftText;

		String& rightText;

		WidgetStyle& style;

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, pressed) const;

		Property_Get(bool, hasChanged) const;

		Property_Get(bool, isLeft) const;

		void setLeft();

		Property_Get(bool, isRight) const;

		void setRight();

		void setIsRight(bool isRight);
	};
}
