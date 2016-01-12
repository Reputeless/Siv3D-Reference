# スケッチブック
![スケッチブック](resource/Sketch/sketch.gif "スケッチブック") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Image image(Window::Size(), Palette::White);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (Input::MouseL.pressed)
		{
			const Point from = Input::MouseL.clicked ? Mouse::Pos() : Mouse::PreviousPos();

			Line(from, Mouse::Pos()).overwrite(image, 8, Palette::Orange);

			texture.fill(image);
		}

		texture.draw();
	}
}
```
