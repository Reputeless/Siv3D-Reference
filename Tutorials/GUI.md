# 19. GUI

## 基本ウィジェット
![基本ウィジェット](resource/GUI/widgets.png "基本ウィジェット")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	const Texture texture(Image(L"Example/Windmill.png").scale(0.3));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");

	// テキスト
	gui.add(GUIText::Create(L"テキストと画像"));

	// 画像
	gui.addln(GUITexture::Create(texture));

	// 水平線
	gui.add(L"hr", GUIHorizontalLine::Create(1));
	gui.horizontalLine(L"hr").style.color = Color(127);

	// ボタン
	gui.add(L"bt1", GUIButton::Create(L"OK"));
	gui.add(L"bt2", GUIButton::Create(L"キャンセル"));
	gui.add(L"bt3", GUIButton::Create(L"OK", false));
	gui.addln(L"bt4", GUIButton::Create(L"キャンセル", false));

	// トグルスイッチ
	gui.add(L"ts1", GUIToggleSwitch::Create(L"OFF", L"ON", false));
	gui.add(L"ts2", GUIToggleSwitch::Create(L"OFF", L"ON", true));
	gui.add(L"ts3", GUIToggleSwitch::Create(L"OFF", L"ON", false, false));
	gui.addln(L"ts4", GUIToggleSwitch::Create(L"OFF", L"ON", true, false));

	// スライダー
	gui.add(L"sl1", GUISlider::Create(0.0, 100.0, 30.0, 200));
	gui.addln(L"sl2", GUISlider::Create(0.0, 100.0, 30.0, 200, false));

	// チェックボックス
	gui.add(L"cb1", GUICheckBox::Create({ L"Red", L"Green", L"Blue" }, { 1u, 2u }, true));
	gui.add(L"cb2", GUICheckBox::Create({ L"Red", L"Green", L"Blue" }, { 1u, 2u }, false));

	// ラジオボタン
	gui.add(L"rb1", GUIRadioButton::Create({ L"Red", L"Green", L"Blue" }, none, true));
	gui.add(L"rb2", GUIRadioButton::Create({ L"Red", L"Green", L"Blue" }, 1u, true));
	gui.addln(L"rb3", GUIRadioButton::Create({ L"Red", L"Green", L"Blue" }, 2u, false));

	// テキストフィールド
	gui.add(L"tf1", GUITextField::Create(none));
	gui.addln(L"tf2", GUITextField::Create(none, false));

	// テキストエリア
	gui.add(L"ta1", GUITextArea::Create(2, 10));
	gui.addln(L"ta2", GUITextArea::Create(2, 10, none, false));

	while (System::Update())
	{

	}
}
```

## GUI ウィンドウの位置と大きさ
![GUI ウィンドウの位置と大きさ](resource/GUI/pos.png "GUI ウィンドウの位置と大きさ")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"bt1", GUIButton::Create(L"OK"));
	gui.add(L"bt2", GUIButton::Create(L"キャンセル"));
	gui.setCenter(Window::Center());

	while (System::Update())
	{
		ClearPrint();
		Println(gui.getPos());
		Println(gui.getRect());
	}
}
```

## GUI のスタイルを変える
![GUI のスタイルを変える](resource/GUI/style.png "GUI のスタイルを変える")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));
	const Font font(20);

	GUIStyle style = GUIStyle::Default;
	style.font = font;
	style.borderRadius = 0;

	GUI gui(style);
	gui.setTitle(L"タイトル");

	WidgetStyle widgetStyle;
	widgetStyle.font = font;

	gui.add(L"bt1", GUIButton::Create(L"OK", widgetStyle));
	gui.add(L"bt2", GUIButton::Create(L"キャンセル", widgetStyle));
	gui.setCenter(Window::Center());

	while (System::Update())
	{

	}
}
```

## テキスト
![テキスト](resource/GUI/text.png "テキスト")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"text", GUIText::Create(L"", 300));

	while (System::Update())
	{
		gui.text(L"text").text = Format(L"マウスカーソル: ", Mouse::Pos());
	}
}
```

## ボタン
![ボタン](resource/GUI/button.png "ボタン")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"left", GUIButton::Create(L"左"));
	gui.add(L"right", GUIButton::Create(L"右"));

	int32 x1 = 320;
	int32 x2 = 320;

	while (System::Update())
	{
		if (gui.button(L"left").pushed)
		{
			x1 -= 10;
		}
		else if (gui.button(L"right").pushed)
		{
			x1 += 10;
		}

		if (gui.button(L"left").pressed)
		{
			x2 -= 10;
		}
		else if (gui.button(L"right").pressed)
		{
			x2 += 10;
		}

		Circle(x1, 300, 20).draw();

		Circle(x2, 360, 20).draw();
	}
}
```

## トグルスイッチ
![トグルスイッチ](resource/GUI/toggleswitch.png "トグルスイッチ")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"circle", GUIToggleSwitch::Create(L"非表示", L"表示", false));

	while (System::Update())
	{
		if (gui.toggleSwitch(L"circle").isRight)
		{
			Circle(Window::Center(), 50).draw();
		}
	}
}
```

## スライダー
![スライダー](resource/GUI/slider.png "スライダー")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"x", GUISlider::Create(0.0, 640.0, 320.0, 200));

	while (System::Update())
	{
		Circle(gui.slider(L"x").value, 240, 50).draw();
	}
}
```

## チェックボックス
![チェックボックス](resource/GUI/checkbox.png "チェックボックス")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"color", GUICheckBox::Create({ L"Red", L"Green", L"Blue" }));

	while (System::Update())
	{
		if (gui.checkBox(L"color").checked(0))
		{
			Circle(220, 300, 40).draw(Palette::Red);
		}

		if (gui.checkBox(L"color").checked(1))
		{
			Circle(320, 300, 40).draw(Palette::Green);
		}

		if (gui.checkBox(L"color").checked(2))
		{
			Circle(420, 300, 40).draw(Palette::Blue);
		}
	}
}
```

## ラジオボタン
![ラジオボタン](resource/GUI/radiobutton.png "ラジオボタン")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.add(L"color", GUIRadioButton::Create({ L"Red", L"Green", L"Blue" }));

	while (System::Update())
	{
		if (gui.radioButton(L"color").checked(0))
		{
			Circle(220, 300, 40).draw(Palette::Red);
		}

		if (gui.radioButton(L"color").checked(1))
		{
			Circle(320, 300, 40).draw(Palette::Green);
		}

		if (gui.radioButton(L"color").checked(2))
		{
			Circle(420, 300, 40).draw(Palette::Blue);
		}
	}
}
```

## テキストフィールド
![テキストフィールド](resource/GUI/textfield.png "テキストフィールド")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	
	// 最大 6 文字に設定
	gui.add(L"text", GUITextField::Create(6));

	const Font font(30);

	while (System::Update())
	{
		font(gui.textField(L"text").text).drawCenter(Window::Center());
	}
}
```

## カラーパレット
![カラーパレット](resource/GUI/colorpalette.png "カラーパレット")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	GUI gui(GUIStyle::Default);
	gui.setTitle(L"色の選択");
	gui.add(L"color", GUIColorPalette::Create(Color(255, 127, 0)));

	while (System::Update())
	{
		Graphics::SetBackground(gui.colorPalette(L"color").color);
	}
}
```

[← 前の章へ戻る](Binary.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Asset.md)