# 長方形の影
![長方形の影](resource/BoxShadow/BoxShadow.gif "長方形の影") 
```cpp
# include <Siv3D.hpp>

Rect MakeRect(int32 x, int32 y)
{
	return{ 60 + x * 105, 30 + 105 * y, 100, 100 };
}

void Main()
{
	Graphics::SetBackground(Palette::White);

	Grid<double> z(5, 4);

	while (System::Update())
	{
		for (int32 y = 0; y < z.height; ++y)
		{
			for (int32 x = 0; x < z.width; ++x)
			{
				const Rect rect = MakeRect(x, y);

				if (!rect.mouseOver)
				{
					rect.draw(HSV(75 * (y * 4 + x), 0.7, 0.95));

					z[y][x] = Max(z[y][x] - 0.02, 0.0);
				}
			}
		}

		for (int32 y = 0; y < z.height; ++y)
		{
			for (int32 x = 0; x < z.width; ++x)
			{
				const Rect rect = MakeRect(x, y);

				if (rect.mouseOver || z[y][x])
				{
					if (rect.mouseOver)
						z[y][x] = Min(z[y][x] + 0.05, 1.0);

					const double s = z[y][x];

					RectF(rect).stretched(s * 1).drawShadow({ 0, 8 * s }, 28 * s, 6 * s);

					RectF(rect).stretched(s * 1).draw(HSV(75 * (y * 4 + x), 0.7, 0.95 + s * 0.05));
				}
			}
		}
	}
}
```
