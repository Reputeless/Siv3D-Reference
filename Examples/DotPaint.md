# ドットお絵かき
![ドットお絵かき](resource/DotPaint/DotPaint.png "ドットお絵かき") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);

	const int32 dotSize = 40;

	Grid<int32> dots(Window::Width() / dotSize, Window::Height() / dotSize);

	while (System::Update())
	{
		for (auto p : step({ dots.width, dots.height }))
		{
			Rect rect(p * dotSize, dotSize, dotSize);

			if (rect.leftClicked)
			{
				++dots[p.y][p.x] %= 4;
			}

			const Color color(240 - dots[p.y][p.x] * 70);

			rect.stretched(-1).draw(color);
		}
	}
}
```
