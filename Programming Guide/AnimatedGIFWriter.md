# AnimatedGIFWriter

一連の `Image` から GIF アニメーションファイルを作成できます。

### AnimatedGIFWriter の使用例

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(40);
	const Size size(180, 120);
	Image image(size);

	AnimatedGIFWriter gifWriter(L"animation.gif", size, false);

	for (auto i : step(60))
	{
		image.fill(HSV(i * 2, 0.5, 1.0));

		Circle(size / 2, i * 2).writeFrame(image, 0, 10, Palette::White);

		font(i / 10).writeCenter(image);

		gifWriter.writeFrame(image, 10);
	}
}
```
作成される GIF アニメーション 
  
![alt text](resource/AnimatedGIFWriter/animation.gif "animation.gif")
