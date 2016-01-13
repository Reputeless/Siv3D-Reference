# 画像ビューア
![画像ビューア](resource/ImageViewer/ImageViewer.png "画像ビューア")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	// 空のテクスチャ
	Texture texture;

	while (System::Update())
	{
		// 何かがドロップされた
		if (Dragdrop::HasItems())
		{
			const Array<FilePath> paths = Dragdrop::GetFilePaths();

			// テクスチャとしてロードに成功したら
			if (const Texture tmp{ paths[0] })
			{
				// テクスチャを置き換える
				texture = tmp;

				// ウィンドウをテクスチャと同じサイズにする
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
