# 対称定規
![対称定規](resource/DrawingSymmetry/DrawingSymmetry.gif "対称定規") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	const int32 N = 12;

	Image image(Window::Size(), Color(20, 40, 60));

	DynamicTexture texture(image);

	Mouse::SetTransform(Mat3x2::Translate(Window::Center()));

	while (System::Update())
	{
		if (Input::MouseL.pressed)
		{
			for (auto i : step(N))
			{
				Circular cs[2] = { Input::MouseL.clicked ? Mouse::Pos() : Mouse::PreviousPos(), Mouse::Pos() };

				for (auto& c : cs)
				{
					c.theta = i % 2 ? -c.theta - TwoPi / N * (i - 1) : c.theta + TwoPi / N * i;
				}

				Line(cs[0], cs[1]).moveBy(Window::Center()).overwrite(image, 2, HSV(System::FrameCount(), 0.5, 1.0));
			}

			texture.tryFill(image);
		}
		else if (Input::MouseR.clicked)
		{
			image.fill(Color(20, 40, 60));

			texture.fill(image);
		}

		texture.draw();
	}
}
```
