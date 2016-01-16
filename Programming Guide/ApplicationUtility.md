# ApplicationUtility
テキストや値を、画面に手軽に表示するためのユーティリティです。

## Print

```cpp
# include <Siv3D.hpp>

void Main()
{
	Print(L"Hello, Siv3D!");

	Print(12345);

	Print(Vec3(1, 2, 3));

	Print(L"プログラミング", 10 + 10);

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			Print(DateTime::Now(), L' ');
		}
	}
}
```

## Println

```cpp

```

## ClearPrint

```cpp

```

## WaitKey

```cpp

```

## PutText

```cpp

```
