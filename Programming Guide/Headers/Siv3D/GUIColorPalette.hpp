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
# include "HSV.hpp"
# include "DynamicTexture.hpp"
# include "IWidget.hpp"
# include "WidgetStyle.hpp"

namespace s3d
{
	class GUIColorPalette : public IWidget
	{
	private:

		int32 m_PaletteHeight = 240;
		
		int32 m_SVPaletteWidth = 160;
		
		int32 m_PaletteMarginWidth = 15;
		
		int32 m_HuePaletteWidth = 20;

		DynamicTexture m_textureSV_mini;

		DynamicTexture m_textureHue1D;

		Point m_posSV = { 0, 0 };

		int32 m_posHue = 0;

		bool m_enabled = true;

		bool m_svPressed = false;

		bool m_huePressed = false;

		Rect getSVBox(const Point& offset) const;

		Rect getHueBox(const Point& offset) const;

		Size getPaletteRegion() const;

		Size getItemSize() const;

		Rect getMarginBox(const Point& offset) const;

		Rect getPaddingBox(const Point& offset) const;

		Rect getItemBox(const Point& offset) const;

		Point getAlignOffset() const;

		void updateSVPalette();

		void updateHuePalette();

		double getHue() const;

		double getS() const;

		double getV() const;

	public:

		static const String& Name()
		{
			static const String name = L"GUIColorPalette";
			return name;
		}

		static std::shared_ptr<GUIColorPalette> Create(const HSV& color = HSV(30.0, 0.9, 0.9), bool enabled = true, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIColorPalette>(color, 240, 160, 15, 20, enabled, style);
		}

		static std::shared_ptr<GUIColorPalette> Create(const HSV& color, int32 paletteHeight, int32 svPaletteWidth, int32 paletteMarginWidth, int32 huePaletteWidth, bool enabled = true, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUIColorPalette>(color, paletteHeight, svPaletteWidth, paletteMarginWidth, huePaletteWidth, enabled, style);
		}

		GUIColorPalette() = default;

		GUIColorPalette(const HSV& color, int32 paletteHeight, int32 svPaletteWidth, int32 paletteMarginWidth, int32 huePaletteWidth, bool enabled, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		bool& getEnabled();

		HSV getHSV() const;

		void setHSV(const HSV& hsv);

		bool isPressed() const;
	};

	class GUIColorPaletteWrapper
	{
	public:

		using WidgetType = GUIColorPalette;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUIColorPaletteWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, enabled(m_widget->getEnabled())
			, style(m_widget->m_style) {}

		GUIColorPaletteWrapper& operator = (const GUIColorPaletteWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		bool& enabled;
		WidgetStyle& style;

		void set(const Color& color) { m_widget->setHSV(color); }
		void set(const ColorF& color) { m_widget->setHSV(color); }
		void set(const HSV& color) { m_widget->setHSV(color); }

		Property_Get(HSV, hsv) { return m_widget->getHSV(); }
		Property_Get(Color, color) { return hsv; }
		Property_Get(ColorF, colorF) { return hsv; }

		Property_Get(bool, pressed) { return m_widget->isPressed(); }
	};
}
