# Glitch
![Glitch](resource/Glitch/Glitch.png "Glitch")  
JPEG データを部分的に破壊して画像にエラーを起こします。
```cpp
#include <Siv3D.hpp>

void Main()
{
	const Image image = Dialog::OpenImage();

	if (!image)
	{
		return;
	}

	const int32 noiseCount = image.num_pixels / 4000;
	const Array<uint8> original = image.encodeJPEG(90).asArray();

	DynamicTexture texture(image);
	Window::Resize(texture.size);

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			Array<uint8> memory(original);

			for (int32 i = 0; i < noiseCount; ++i)
			{
				memory[Random(630u, static_cast<uint32>(memory.size() - 1))] = static_cast<uint8>(Random(255));
			}

			texture.fill(Image(ByteArray(std::move(memory))));
		}

		texture.draw();
	}
}
```
