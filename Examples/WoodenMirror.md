# Wooden Mirror
![Wooden Mirror](resource/WoodenMirror/WoodenMirror.png "Wooden Mirror")  
<a href="http://www.smoothware.com/danny/woodenmirror.html" target="_blank">Daniel Rozin / Wooden Mirror</a> 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Webcam webcam(0);
	
	if (!webcam.start())
	{
		return;
	}

	Graphics3D::SetLight(0, Light::Directional({ 0.0, 0.5, -1.0 }, ColorF(1.2)));

	// 適当な木目のテクスチャを用意
	const Texture texture = Dialog::OpenTexture(TextureDesc::For3D);
	
	Image image, image2;

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		if (webcam.hasNewFrame())
		{
			webcam.getFrame(image);

			Imaging::Scale(image, image2, 64, 48);

			Imaging::Grayscale(image2, image2);

			Imaging::Mirror(image2, image2);
		}

		for (auto p : step(image2.size))
			Box({ p.x - 32, 24 - p.y, 0 }, { 1.0, 1.0, 0.15 }, Quaternion::Pitch(0.6 - (255 - image2[p.y][p.x].r) / 160.0))
			.draw(texture);
	}
}
```
