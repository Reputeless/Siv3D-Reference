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
	class GUIHorizontalLine : public IWidget
	{
	private:

		int m_thickness = 1;

		Point ItemSize(int areaWidth) const;

		Rect MarginBox(int areaWidth, const Point& offset) const;

		Rect PaddingBox(int areaWidth, const Point& offset) const;

		Rect ItemBox(int areaWidth, const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"HorizontalLine";
			return name;
		}

		static std::shared_ptr<GUIHorizontalLine> Create(int thickness = 1, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIHorizontalLine>(thickness, style);
		}

		GUIHorizontalLine() {}

		GUIHorizontalLine(int thickness, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		int& getThickness();
	};

	class GUIHorizontalLineWrapper
	{
	public:

		using WidgetType = GUIHorizontalLine;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUIHorizontalLineWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, thickness(m_widget->getThickness())
			, style(m_widget->m_style) {}

		GUIHorizontalLineWrapper& operator = (const GUIHorizontalLineWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		int& thickness;

		WidgetStyle& style;
	};
}
