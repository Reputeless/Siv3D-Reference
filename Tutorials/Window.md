# 10. ウィンドウと背景

## 背景色を変える
![背景色を変える](resource/Window/background.png "背景色を変える")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	// 背景色を 白 に設定する
	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		if (Input::KeyR.clicked)
		{
			// 背景色を RGB(255, 64, 64) に設定する
			Graphics::SetBackground(Color(255, 64, 64));
		}

		if (Input::KeyG.clicked)
		{
			Graphics::SetBackground(Color(64, 255, 64));
		}

		if (Input::KeyB.clicked)
		{
			Graphics::SetBackground(Color(64, 64, 255));
		}
	}
}
```

## ウィンドウのタイトルを変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	// ウィンドウのタイトルを設定する
	Window::SetTitle(L"Game");

	while (System::Update())
	{

	}
}
```

## ウィンドウのサイズを変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	// ウィンドウサイズを 幅 300, 高さ 400 にする
	Window::Resize(300, 400);

	while (System::Update())
	{
		if (Input::KeyW.clicked)
		{
			Window::Resize(600, 200);
		}

		if (Input::KeyH.clicked)
		{
			Window::Resize(200, 600);
		}
	}
}
```

## サイズを変えられるウィンドウにする
![サイズを変えられるウィンドウにする](resource/Window/sizeable.png "サイズを変えられるウィンドウにする")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	// サイズを変えられるウィンドウにする
	Window::SetStyle(WindowStyle::Sizeable);

	while (System::Update())
	{
		font(Window::Width(), L'×', Window::Height()).draw();
	}
}
```

## ウィンドウを移動する

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			// ウィンドウを左上に移動する
			Window::ToUpperLeft();
		}

		if (Input::MouseR.clicked)
		{
			// ウィンドウを 位置 (200,100) に移動する
			Window::SetPos(200, 100);
		}
	}
}
```

## ウィンドウを中央に移動する

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			// ウィンドウを中央に移動する
			Window::Centering();
		}
	}
}
```

## ウィンドウの枠を表示しない

Esc キーで終了できます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	// 枠のないウィンドウにする
	Window::SetStyle(WindowStyle::NonFrame);

	while (System::Update())
	{

	}
}
```

## フルスクリーンモード、ウィンドウモードを切り替える

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Size targetSize(1280, 720);

	// フルスクリーン可能な解像度一覧を取得
	const Array<Size> resolutions = Graphics::GetFullScreenSize();

	for (const auto& resolution : resolutions)
	{
		Println(resolution);
	}

	const Font font(40);

	while (System::Update())
	{
		if (Input::KeyF.clicked)
		{
			// フルスクリーンモード
			if (!Window::SetFullscreen(true, targetSize))
			{
				System::Exit();
			}
		}
		
		if (Input::KeyW.clicked)
		{
			// ウィンドウモード
			if (!Window::SetFullscreen(false, targetSize))
			{
				System::Exit();
			}
		}

		Circle(Mouse::Pos(), 100).draw();

		font(Mouse::Pos()).draw();
	}
}
```

## ウィンドウのアイコンを変更する

```cpp
# include <Siv3D.hpp>

void Main()
{
	Image image(32, 32, Palette::Green);

	Window::SetIcon(image);

	while (System::Update())
	{

	}
}
```

[← 前の章へ戻る](Midi.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Geometry2D.md)