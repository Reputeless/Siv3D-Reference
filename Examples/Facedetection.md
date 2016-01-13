# 顔検出

## 写真から顔を検出する

イラスト: <a href="http://www.pixiv.net/member.php?id=583587" target="_blank">古古米</a> さん
```cpp
# include <Siv3D.hpp>

void Main()
{
	Webcam webcam(0);

	if (!webcam.start())
	{
		return;
	}

	Image image;

	DynamicTexture texture;

	while (System::Update())
	{
		if (webcam.hasNewFrame())
		{
			webcam.getFrame(image);

			for (const auto rect : Imaging::DetectFaces(image, CascadeType::Photo, 3, { 40, 40 }))
			{
				rect.overwriteFrame(image, 3, 3, Palette::Red);
			}

			texture.fill(image);
		}

		if (texture)
		{
			texture.mirror().draw();
		}
	}
}
```
## イラストから顔を検出する
![イラストから顔を検出する](resource/Facedetection/FacedetectionAnime.png "イラストから顔を検出する")  
イラスト: <a href="http://www.pixiv.net/member.php?id=583587" target="_blank">古古米</a> さん
```cpp
# include <Siv3D.hpp>

void Main()
{
	Texture texture;

	while (System::Update())
	{
		if (Dragdrop::HasItems())
		{
			if (Image image{ Dragdrop::GetFilePaths()[0] })
			{
				for (const auto rect : Imaging::DetectFaces(image, CascadeType::Anime))
				{
					rect.overwriteFrame(image, 3, 3, Palette::Red);
				}

				texture = Texture(image);

				Window::Resize(texture.size);
			}
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
```
