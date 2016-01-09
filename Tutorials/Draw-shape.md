# 2. 図形を描く

### 円を描く

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 中心 (300,200) 半径 150 の円を描く
		Circle(300, 200, 150).draw();
	}
}
```

[← 前の章へ戻る](Getting-started-with-siv3d.md)　|　[次の章へ進む →](Getting-started-with-siv3d.md)