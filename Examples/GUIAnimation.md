# GUI のアニメーション

## メッセージボックス
![メッセージボックス](resource/GUIAnimation/GUIAnimation1.gif "メッセージボックス")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(18);
	const Point center = Window::Center();
	const Rect messageBox = Rect(300, 150).setCenter(center);
	const Rect button1 = Rect(120, 40).setCenter(center.movedBy(-70, 30));
	const Rect button2 = Rect(120, 40).setCenter(center.movedBy(70, 30));

	EasingController<double> easing(0.0, 1.0, Easing::Quart, 500.0);

	while (System::Update())
	{
		Graphics2D::SetTransform(Mat3x2::Identity());

		const double e = easing.easeOut();

		if (e != 0.0)
		{
			Graphics2D::SetTransform(Mat3x2::Translate(-center).scale(e).translate(center));
			const ColorF uiColor = AlphaF(e);

			RoundRect(messageBox, 20).draw(ColorF(0.2, 0.6, 0.4, e));
			font(L"終了しますか？").drawCenter(center.movedBy(0, -30), uiColor);

			button1.drawFrame(2, 0, uiColor);
			font(L"はい").drawCenter(button1.center, uiColor);

			button2.drawFrame(2, 0, uiColor);
			font(L"いいえ").drawCenter(button2.center, uiColor);
		}

		if (!easing.isActive())
		{
			if (e == 1.0)
			{
				if (button1.mouseOver)
					button1.draw(AlphaF(0.3));

				if (button2.mouseOver)
					button2.draw(AlphaF(0.3));

				if (button1.leftClicked)
					System::Exit();

				if (button2.leftClicked)
					easing.start();
			}
			else if (Input::MouseL.clicked)
			{
				easing.start();
			}
		}
	}
}
```

## タイトルメニュー
![タイトルメニュー](resource/GUIAnimation/GUIAnimation2.gif "タイトルメニュー")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(16, Typeface::Medium);
	const Rect messageBox = Rect(400, 320).setCenter(Window::Center());
	const Array<String> texts
	{
		L"はじめから",
		L"つづきから",
		L"オプション",
		L"クレジット",
		L"ゲームを終了"
	};

	Stopwatch stopwatch1, stopwatch2;
	uint32 selectIndex = 0;
	double start = 0, end = 0;

	while (System::Update())
	{
		Graphics2D::SetTransform(Mat3x2::Identity());

		if (Input::MouseL.clicked)
		{
			stopwatch1.start();
		}

		if (Input::MouseR.clicked)
		{
			start = end = selectIndex = 0;
			stopwatch1.reset();
		}

		if (Input::KeyUp.clicked)
		{
			start = selectIndex;
			end = selectIndex = static_cast<uint32>((selectIndex + texts.size() - 1) % texts.size());
			stopwatch2.restart();
		}

		if (Input::KeyDown.clicked)
		{
			start = selectIndex;
			end = (++selectIndex %= texts.size());
			stopwatch2.restart();
		}

		RoundRect(messageBox, 20).draw(Color(20, 30, 120));

		const double t0 = Min(stopwatch1.ms() / 500.0, 1.0);
		const double e0 = EaseOut(Easing::Quart, t0);

		if (e0 > 0.0)
		{
			{
				const double t = Min(stopwatch2.ms() / 300.0, 1.0);
				const double y = 140 + EaseOut(start, end, Easing::Quart, t) * 50;

				RectF(16 * e0, 16 * e0).setCenter(210, y).rotated(stopwatch1.ms() / 500.0).draw(AlphaF(0.9 * e0));
				RectF(180 * e0, 50).setCenter(320, y).drawShadow({ 0, 0 }, 10, 0, { 1.0, 0.2 * e0 });
			}

			for (auto i : step(texts.size()))
			{
				const double t = Saturate((static_cast<double>(stopwatch1.ms()) - i * 50) / 500.0);
				const double e = EaseOut(Easing::Quart, t);
				const Vec2 center(320, 140 + i * 50);

				Graphics2D::SetTransform(Mat3x2::Translate(-center).scale(e).translate(center));
				font(texts[i]).drawCenter(center);
			}
		}
	}
}
```
