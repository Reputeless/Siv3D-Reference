# 14. ドラッグ & ドロップ

## ドロップされたアイテム
![ドロップされたアイテム](resource/Dragdrop/dragdrop.png "ドロップされたアイテム")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 何かがドロップされたら
		if (Dragdrop::HasItems())
		{
			// ドロップされたすべてのアイテムを取得
			const Array<FilePath> items = Dragdrop::GetFilePaths();

			for (const auto& item : items)
			{
				Println(item);
			}
		}
	}
}
```

## ドロップされた位置

```cpp
# include <Siv3D.hpp>

void Main()
{
	Point pos(0, 0);

	Array<FilePath> items;

	while (System::Update())
	{
		if (Dragdrop::HasItems())
		{
			items = Dragdrop::GetFilePaths();

			// ドロップされた位置
			pos = Dragdrop::GetPos();
		}

		if (!items.empty())
		{
			Circle(pos, 20).draw();
		}
	}
}
```

## ドロップを無効にする

```cpp
# include <Siv3D.hpp>

void Main()
{
	Dragdrop::SetEnabled(false);

	while (System::Update())
	{

	}
}
```

[← 前の章へ戻る](Dialog.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](System.md)
