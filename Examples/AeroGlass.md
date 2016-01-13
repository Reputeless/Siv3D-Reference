# Aero Glass エフェクト
![Aero Glass エフェクト](resource/AeroGlass/AeroGlass.png "Aero Glass エフェクト")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Image image = Dialog::OpenImage();
	const Texture texture(image);
	const Texture textureGaussian(image.gaussianBlurred(20, 20));

	Window::Resize(image.size);

	while (System::Update())
	{
		texture.draw();

		const RectF rect(Mouse::Pos(), 300, 200);

		textureGaussian(rect).draw(rect.pos);

		rect.draw(Color(255, 160));

		rect.drawFrame(1);
	}
}
```
