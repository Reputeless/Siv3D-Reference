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
	class GUICheckBox : public IWidget
	{
	public:

		struct Item
		{
			double pressure;

			double scaling;

			String label;

			bool pressed;

			bool checked;
		};

	private:

		Array<Item> m_items;

		int m_maxLabelWidth = 0;

		bool m_hasChanged = false;

		bool m_mouseOver = false;

		bool m_enabled = true;

		Point ItemSize() const;

		Rect MarginBox(const Point& offset) const;

		Rect PaddingBox(const Point& offset) const;

		Rect ItemBox(const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"CheckBox";
			return name;
		}

		static std::shared_ptr<GUICheckBox> Create(const Array<String>& items, const Array<size_t>& chekedItems = {}, bool enabled = true, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUICheckBox>(items, chekedItems, enabled, style);
		}

		GUICheckBox() {}

		GUICheckBox(const Array<String>& items, const Array<size_t>& chekedItems, bool enabled, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		bool& getEnabled();

		Array<Item>& getItems();

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, hasChanged) const;

		void setName(size_t index, const String& name);
	};

	class GUICheckBoxWrapper
	{
	public:

		using WidgetType = GUICheckBox;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUICheckBoxWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, enabled(m_widget->getEnabled())
			, style(m_widget->m_style) {}

		GUICheckBoxWrapper& operator = (const GUICheckBoxWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		bool& enabled;

		WidgetStyle& style;


		Property_Get(bool, mouseOver) const;

		Property_Get(bool, hasChanged) const;


		Property_Get(size_t, num_items) const;

		Property_Get(Array<String>, itemNames) const;

		Property_Get(Array<size_t>, checkedItems) const;

		String name(size_t index) const;

		bool checked(size_t index) const;

		void check(size_t index, bool checked);

		void setName(size_t index, const String& name);
	};
}
