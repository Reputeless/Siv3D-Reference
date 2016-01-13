# 付箋
![付箋](resource/Postit/Postit.png "付箋") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);

	const Font font(18, Typeface::Light);

	const Array<String> texts =
	{
		L"Siv3D", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10",
	};

	while (System::Update())
	{
		for (auto p : step({ 2, 5 }))
		{
			const Rect rect(60 + p.x * 280, 40 + p.y * 80, 220, 60);

			Graphics2D::SetTransform(Mat3x2::Rotate(Radians(2), rect.pos));

			rect.drawShadow({ 1, 1 }, 12, -1, ColorF(0, 0.4));

			Graphics2D::SetTransform(Mat3x2::Identity());

			rect.draw(HSV((p.x * 5 + p.y) * 30, 0.5, 1.0));

			font(texts[p.x * 5 + p.y]).draw(rect.pos.movedBy(20, 12), Palette::Black);
		}
	}
}
```
