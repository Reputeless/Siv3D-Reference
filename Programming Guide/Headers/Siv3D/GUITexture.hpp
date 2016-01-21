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
	class GUITexture : public IWidget
	{
	private:

		Texture m_texture;

		Point ItemSize() const;

		Point TextureRegion() const;

		Rect MarginBox(const Point& offset) const;

		Rect PaddingBox(const Point& offset) const;

		Rect ItemBox(const Point& offset) const;

	public:

		static const String& Name()
		{
			static const String name = L"Texture";
			return name;
		}

		static std::shared_ptr<GUITexture> Create(const s3d::Texture& texture, const WidgetStyle& style = WidgetStyle())
		{
			return std::make_shared<GUITexture>(texture, style);
		}

		GUITexture() {}

		GUITexture(const Texture& texture, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		Texture& getTexture();
	};

	class GUITextureWrapper
	{
	public:

		using WidgetType = GUITexture;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUITextureWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, texture(m_widget->getTexture())
			, style(m_widget->m_style) {}

		GUITextureWrapper& operator = (const GUITextureWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}
		
	public:

		Texture& texture;

		WidgetStyle& style;
	};
}
