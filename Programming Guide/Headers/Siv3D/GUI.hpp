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
# include <memory>
# include "Handle.hpp"
# include "Fwd.hpp"
# include "WidgetStyle.hpp"
# include "IWidget.hpp"
# include "GUIText.hpp"
# include "GUINewLine.hpp"
# include "GUITexture.hpp"
# include "GUIHorizontalLine.hpp"
# include "GUIButton.hpp"
# include "GUIToggleSwitch.hpp"
# include "GUISlider.hpp"
# include "GUICheckBox.hpp"	
# include "GUIRadioButton.hpp"
# include "GUITextField.hpp"
# include "GUITextArea.hpp"
# include "GUIColorPalette.hpp"

namespace s3d
{
	/// <summary>
	/// GUI ウィンドウスタイル
	/// </summary>
	struct GUIStyle
	{
		Padding padding = Padding(10);

		Background background;

		Optional<int32> width;

		Optional<Color> borderColor = Color(90, 70);

		Optional<ColorF> shadowColor = ColorF(0.0, 0.6);

		double borderRadius = 8.0;

		Font font = GUIManager::GetDefaultFont();

		/// <summary>
		/// GUI ウィンドウの描画順を示します。
		/// 値が大きいほど前面に表示されます。
		/// </summary>
		int z = 0;

		/// <summary>
		/// タイトルを表示するかを示します。
		/// </summary>
		bool showTitle = false;

		/// <summary>
		/// タイトルバーをつかんで移動可能かを示します。
		/// </summary>
		bool movable = true;

		/// <summary>
		/// アクティブであるかを示します。
		/// </summary>
		bool active = true;

		/// <summary>
		/// 表示されているかを示します。
		/// </summary>
		bool visible = true;

		/// <summary>
		/// デバッグ用のボックスモデルを表示するかを示します。
		/// </summary>
		bool showBoxModel = false;

		enum class Predefined
		{
			Default,
		};

		GUIStyle()
		{
			background.color = s3d::Color(242);
		}

		GUIStyle(Predefined)
		{
			background.color = s3d::Color(242);
		}

		/// <summary>
		/// デフォルトの GUI ウィンドウスタイル
		/// </summary>
		const static Predefined Default = Predefined::Default;
	};

	/// <summary>
	/// GUI ウィンドウ
	/// </summary>
	class GUI
	{
	private:

		class Handle{};

		using GUIHandle = Siv3DHandle<Handle>;

		std::shared_ptr<GUIHandle> m_handle;

		std::shared_ptr<IWidget> getWidget(const String& widgetName, const String& name) const;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		GUI();

		/// <summary>
		/// GUI ウィンドウを作成します。
		/// </summary>
		/// <param name="style">
		/// GUI ウィンドウスタイル
		/// </param>
		explicit GUI(const GUIStyle& style);

		void release();

		explicit operator bool() const { return !isEmpty(); }

		HandleIDType id() const;

		bool isEmpty() const;

		bool operator == (const GUI& gui) const;

		bool operator != (const GUI& gui) const;

		/// <summary>
		/// GUI ウィンドウを非表示、非アクティブにします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void hide();

		/// <summary>
		/// GUI ウィンドウの [非表示、非アクティブ] / [表示、アクティブ] を切り替えます。
		/// </summary>
		/// <param name="show">
		/// [表示、アクティブ] にする場合 true, [非表示、非アクティブ] にする場合は false
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void show(bool show = true);

		/// <summary>
		/// ウィジェットを追加します。
		/// </summary>
		/// <param name="pWidget">
		/// ウィジェット
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void add(const std::shared_ptr<IWidget>& pWidget);

		/// <summary>
		/// 名前付きのウィジェットを追加します。
		/// </summary>
		/// <param name="name">
		/// ウィジェットの名前
		/// </param>
		/// <param name="pWidget">
		/// ウィジェット
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void add(const String& name, const std::shared_ptr<IWidget>& pWidget);

		/// <summary>
		/// ウィジェットを追加し、改行します。
		/// </summary>
		/// <param name="pWidget">
		/// ウィジェット
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void addln(const std::shared_ptr<IWidget>& pWidget);

		/// <summary>
		/// 名前付きのウィジェットを追加し、改行します。
		/// </summary>
		/// <param name="name">
		/// ウィジェットの名前
		/// </param>
		/// <param name="pWidget">
		/// ウィジェット
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void addln(const String& name, const std::shared_ptr<IWidget>& pWidget);

		/// <summary>
		/// GUI ウィンドウにタイトルを設定します。
		/// </summary>
		/// <param name="title">
		/// タイトル
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setTitle(const String& title);

		String getTitle() const;

		void setPos(int x, int y);

		void setPos(const Point& pos);

		void setCenter(const Point& pos);

		Point getPos() const;

		Rect getRect() const;

		/// <summary>
		/// GUI ウィンドウのスタイルにアクセスします。
		/// </summary>
		Property_Get(GUIStyle&, style);

		template <class Type>
		Type get(const String& name) const
		{
			if (const auto widget = getWidget(Type::WidgetTypeName(), name))
			{
				return Type(std::dynamic_pointer_cast<Type::WidgetType>(widget));
			}
			else
			{
				return Type(nullptr);
			}
		}

		GUITextWrapper text(const String& name) const
		{
			return get<GUITextWrapper>(name);
		}

		GUINewLineWrapper newLine(const String& name) const
		{
			return get<GUINewLineWrapper>(name);
		}

		GUITextureWrapper texture(const String& name) const
		{
			return get<GUITextureWrapper>(name);
		}

		GUIHorizontalLineWrapper horizontalLine(const String& name) const
		{
			return get<GUIHorizontalLineWrapper>(name);
		}

		GUIButtonWrapper button(const String& name) const
		{
			return get<GUIButtonWrapper>(name);
		}

		GUIToggleSwitchWrapper toggleSwitch(const String& name) const
		{
			return get<GUIToggleSwitchWrapper>(name);
		}

		GUISliderWrapper slider(const String& name) const
		{
			return get<GUISliderWrapper>(name);
		}

		GUICheckBoxWrapper checkBox(const String& name) const
		{
			return get<GUICheckBoxWrapper>(name);
		}

		GUIRadioButtonWrapper radioButton(const String& name) const
		{
			return get<GUIRadioButtonWrapper>(name);
		}

		GUITextFieldWrapper textField(const String& name) const
		{
			return get<GUITextFieldWrapper>(name);
		}

		GUITextAreaWrapper textArea(const String& name) const
		{
			return get<GUITextAreaWrapper>(name);
		}

		GUIColorPaletteWrapper colorPalette(const String& name) const
		{
			return get<GUIColorPaletteWrapper>(name);
		}
	};
}
