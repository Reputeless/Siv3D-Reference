# 22. Web カメラ

## 利用可能な Web カメラの一覧を取得する

```cpp
# include <Siv3D.hpp>

void Main()
{
	for (const auto& camera : WebcamManager::Enumerate())
	{
        // デバイス ID とカメラの名前を表示
		Println(camera.deviceID, L": ", camera.name);
	}

	WaitKey();
}
```

## カメラの画像を表示する
`DynamicTexture` は特殊な `Texture` で、内容を更新することができます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Webcam webcam;

	// デバイス ID: 0 の Web カメラを起動
	if (!webcam.open(0, Size(640, 480)))
	{
		// 失敗したら終了
		return;
	}

	// 撮影開始
	if (!webcam.start())
	{
		return;
	}

	// 空の動的テクスチャ
	DynamicTexture texture;

	while (System::Update())
	{
		// カメラが新しい画像を撮影したら
		if (webcam.hasNewFrame())
		{
			// 動的テクスチャをカメラの画像で更新
			webcam.getFrame(texture);
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
```

## カメラの画像を左右反転して表示する

```cpp
# include <Siv3D.hpp>

void Main()
{
	Webcam webcam;

	if (!webcam.open(0, Size(640, 480)))
	{
		return;
	}

	if (!webcam.start())
	{
		return;
	}

	DynamicTexture texture;

	while (System::Update())
	{
		if (webcam.hasNewFrame())
		{
			webcam.getFrame(texture);
		}

		if (texture)
		{
			// テクスチャを
			// 左右反転して描く
			texture.mirror().draw();
		}
	}
}
```

## カメラの画像を加工する

```cpp
# include <Siv3D.hpp>

void Main()
{
	Webcam webcam;

	if (!webcam.open(0, Size(640, 480)))
	{
		return;
	}

	if (!webcam.start())
	{
		return;
	}

	// 空の画像
	Image image;

	// 空の動的テクスチャ
	DynamicTexture texture;

	while (System::Update())
	{
		if (webcam.hasNewFrame())
		{
			// Image をカメラの画像で更新
			webcam.getFrame(image);

			if (Input::KeyM.pressed)
			{
				image.mosaic(15, 15);
			}

			if (Input::KeyS.pressed)
			{
				image.spread(20, 20);
			}

			if (Input::KeyN.pressed)
			{
				image.negate();
			}

			if (Input::KeyG.pressed)
			{
				image.grayscale();
			}

			if (Input::KeyT.pressed)
			{
				image.threshold(128);
			}

			// 動的テクスチャを更新
			texture.fill(image);
		}

		if (texture)
		{
			texture.mirror().draw();
		}
	}
}
```

## カメラの画像を保存する

```cpp
# include <Siv3D.hpp>

void Main()
{
	Webcam webcam;

	if (!webcam.open(0, Size(640, 480)))
	{
		return;
	}

	if (!webcam.start())
	{
		return;
	}

	// 空の画像
	Image image;

	DynamicTexture texture;

	while (System::Update())
	{
		if (webcam.hasNewFrame())
		{
			webcam.getFrame(image);

			texture.fill(image);
		}

		if (texture)
		{
			texture.draw();
		}

		if (image && Input::MouseL.clicked)
		{
			// 画像を保存
			image.save(L"photo.jpg");
		}
	}
}
```

[← 前の章へ戻る](Image.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Recorder.md)