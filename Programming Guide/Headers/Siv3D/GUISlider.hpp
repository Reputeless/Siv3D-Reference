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
	class GUISlider : public IWidget
	{
	private:

		double m_pressedPressure = 0.0;

		double m_leftValue = 0.0;

		double m_rightValue = 0.0;

		Optional<Point> m_grabbed;

		double m_sliderPosition = 0;

		int m_sliderWidth = 0;

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
			static const String name = L"Slider";
			return name;
		}

		/// <summary>
		/// スライダーウィジェットを作成します。
		/// </summary>
		/// <param name="left">
		/// 一番左の値
		/// </param>
		/// <param name="right">
		/// 一番右の値
		/// </param>
		/// <param name="initial">
		/// 初期状態の値
		/// </param>
		/// <param name="enabled">
		/// 有効かどうか
		/// </param>
		/// <param name="style">
		/// スタイル
		/// </param>
		/// <returns>
		/// スライダーウィジェット
		/// </returns>
		static std::shared_ptr<GUISlider> Create(double left, double right, double initial, bool enabled = true, const WidgetStyle& style = WidgetStyle())
		{
			return Create(left, right, initial, style.font.height * 5, enabled, style);
		}

		/// <summary>
		/// スライダーウィジェットを作成します。
		/// </summary>
		/// <param name="left">
		/// 一番左の値
		/// </param>
		/// <param name="right">
		/// 一番右の値
		/// </param>
		/// <param name="initial">
		/// 初期状態の値
		/// </param>
		/// <param name="width">
		/// スライダーのサイズ（ピクセル）
		/// </param>
		/// <param name="enabled">
		/// 有効かどうか
		/// </param>
		/// <param name="style">
		/// スタイル
		/// </param>
		/// <returns>
		/// スライダーウィジェット
		/// </returns>
		static std::shared_ptr<GUISlider> Create(double left, double right, double initial, int width, bool enabled = true, const WidgetStyle& style = WidgetStyle())
		{
			double position = 0.0;

			if (right - left != 0.0)
			{
				const double current = Clamp(initial, s3d::Min(left, right), s3d::Max(left, right));

				position = width * (current - left) / (right - left);
			}

			return std::make_shared<GUISlider>(left, right, width, position, enabled, style);
		}

		GUISlider() {}

		GUISlider(double left, double right, int width, double position, bool enabled, const WidgetStyle& style);

		const String& getWidgetName() const override;

		Size getSize() const override;

		bool forceNewLineBefore() const override;

		bool forceNewLineAfter() const override;

		void update(const WidgetState& state) override;

		void draw(const WidgetState& state) const override;

		bool& getEnabled();

		Property_Get(double, leftValue) const;

		void setLeftValue(double value);

		Property_Get(double, rightValue) const;

		void setRightValue(double value);

		Property_Get(int, sliderWidth) const;

		void setSliderWidth(int sliderWidth);

		Property_Get(double, sliderPosition) const;

		void setSliderPosition(double position);

		Property_Get(bool, mouseOver) const;

		Property_Get(bool, pressed) const;

		Property_Get(bool, hasChanged) const;
	};

	class GUISliderWrapper
	{
	public:

		using WidgetType = GUISlider;

	private:

		friend class GUI;

		std::shared_ptr<WidgetType> m_widget;

		GUISliderWrapper(const std::shared_ptr<WidgetType>& widget)
			: m_widget(widget ? widget : std::make_shared<WidgetType>())
			, enabled(m_widget->getEnabled())
			, style(m_widget->m_style) {}

		GUISliderWrapper& operator = (const GUISliderWrapper&) = delete;

		static const String& WidgetTypeName()
		{
			return WidgetType::Name();
		}

	public:

		bool& enabled;

		WidgetStyle& style;


		Property_Get(bool, mouseOver) const;

		Property_Get(bool, pressed) const;

		/// <summary>
		/// スライダーの値がユーザによって変更されたかどうかを示します。
		/// </summary>
		Property_Get(bool, hasChanged) const;


		Property_Get(double, leftValue) const;

		void setLeftValue(double value);

		Property_Get(double, rightValue) const;

		void setRightValue(double value);


		Property_Get(int, sliderWidth) const;

		void setSliderWidth(int width);

		Property_Get(double, sliderPosition) const;

		void setSliderPosition(double position);

		/// <summary>
		/// 現在スライダーの値
		/// </summary>
		Property_Get(double, value) const;

		/// <summary>
		/// 現在スライダーの値（整数）
		/// </summary>
		Property_Get(int, valueInt) const;

		/// <summary>
		/// スライダーの値を変更します。
		/// </summary>
		/// <param name="value">
		/// 新しい値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setValue(double value);
	};
}
