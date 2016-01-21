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
	class GUITextArea : public IWidget
	{
	private:

		Optional<size_t> m_maxLength;

		size_t m_cursorPos = 0;

		String m_text;

		double m_pressedPressure = 0.0;

		double m_scaling = 0.0;

		unsigned m_cols = 0;

		unsigned m_rows = 0;

		bool m_mouseOver = false;

		bool m_hasChanged = false;

		bool m_enabled = true;

		bool m_active = false;

		Point ItemSize() const;

		Point TextRegion() const;

		Rect MarginBox(const Point& offset) const;

		Rect PaddingBox(const Point& offset) const;

		Rect ItemBox(const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"TextArea";
			return name;
		}

		static std::shared_ptr<GUITextArea> Create(uint32 rows, uint32 cols = 8, const Optional<size_t>& maxLength = none, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUITextArea>(rows, cols, maxLength, true, style);
		}

		static std::shared_ptr<GUITextArea> Create(uint32 rows, uint32 cols, const Optional<size_t>& maxLength, bool enabled, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUITextArea>(rows, cols, maxLength, enabled, style);
		}

		GUITextArea() {}

		GUITextArea(uint32 rows, uint32 cols, const Optional<size_t>& maxLength, bool enabled, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		bool& getEnabled();

		bool& getActive();

		const String& getText() const;

		void setText(const String& text);

		const Optional<size_t>& getMaxLength() const;

		void setMaxLength(const Optional<size_t>& length);

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, hasChanged) const;
	};

	class GUITextAreaWrapper
	{
	public:

		using WidgetType = GUITextArea;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUITextAreaWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, enabled(m_widget->getEnabled())
			, active(m_widget->getActive())
			, style(m_widget->m_style) {}

		GUITextAreaWrapper& operator = (const GUITextAreaWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		bool& enabled;

		bool& active;

		WidgetStyle& style;

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, hasChanged) const;

		Property_Get(const String&, text) const;

		void setText(const String& text);

		Property_Get(Optional<size_t>, maxLength) const;

		void setMaxLength(const Optional<size_t>& length);
	};
}
