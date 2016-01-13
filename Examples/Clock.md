# 時計

## 時計 1
![時計 1](resource/Clock/Clock1.gif "時計 1") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::Seagreen);

	const Font font(45, Typeface::Light);

	// 時計盤の中心
	const Vec2 center(320, 210);

	while (System::Update())
	{
		Circle(center, 8).draw();

		for (auto i : step(12))
		{
			Circle(center + Circular(170, Radians(i * 30)), i % 3 ? 10 : 15).draw();
		}

		// 現在時刻
		const DateTime time = DateTime::Now();

		// 時針
		const double hourRadian = (time.hour*60.0 + time.minute) / 720.0 * TwoPi;
		Line(center, center + Circular(120, hourRadian)).draw(12);

		// 分針
		const double minuteRadian = time.minute / 60.0 * TwoPi;
		Line(center, center + Circular(160, minuteRadian)).draw(8);

		// 秒針
		const double secondRadian = time.second / 60.0 * TwoPi;
		Line(center, center + Circular(170, secondRadian)).draw(2);

		font(time.format(L"HH:mm")).drawCenter(390);
	}
}
```

## 時計 2
![時計 2](resource/Clock/Clock2.gif "時計 2") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);

	const Font font(45, Typeface::Light);

	const Vec2 center = Window::Center();

	while (System::Update())
	{
		const DateTime time = DateTime::Now();

		const int32 ms = (time.hour * 60 * 60 * 1000) + (time.minute * 60 * 1000) + (time.second * 1000 + time.milliseconds);

		const double h = (ms % (12 * 60 * 60 * 1000)) / (12 * 60.0 * 60.0 * 1000.0)*TwoPi;

		const double m = (ms % (60 * 60 * 1000)) / (60.0 * 60.0 * 1000.0)*TwoPi;

		const double s = (ms % (60 * 1000)) / (60.0 * 1000.0)*TwoPi;

		Graphics2D::SetStencilState(StencilState::None);

		Circle(center, 400).drawArc(s + 0.05, TwoPi - 0.1, 240.5, 0.0, Color(40, 150, 255));

		Circle(center, 160).drawArc(m + 0.05, TwoPi - 0.1, 80.5, 0.0, Color(40, 120, 220));

		Circle(center, 80).drawArc(h + 0.05, TwoPi - 0.1, 60.5, 0.0, Color(40, 90, 180));

		Graphics2D::SetStencilValue(1);

		Graphics2D::SetStencilState(StencilState::Replace);

		Circle(center, 400).drawArc(s + 0.05, TwoPi - 0.1, 240.5, 0.0);

		Graphics2D::SetStencilState(StencilState::Test(StencilFunc::NotEqual));

		font(time.format(L"HH:mm")).drawCenter(390, Color(40, 150, 255));

		Graphics2D::SetStencilState(StencilState::Test(StencilFunc::Equal));

		font(time.format(L"HH:mm")).drawCenter(390);
	}
}
```
