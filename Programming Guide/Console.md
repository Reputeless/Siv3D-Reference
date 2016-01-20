# Console

コンソールウィンドウを開き、標準入出力を扱えるようにします。

## コンソールウィンドウを開いて標準入出力を扱う

```cpp
# include <Siv3D.hpp>

void Main()
{
	Console::Open();

	std::wcout << L"Siv3D\n";

	int32 n;

	std::wcin >> n;

	Println(n);

	while (System::Update())
	{

	}
}
```

## コンソールウィンドウを閉じる
アプリケーションの終了時には自動的にコンソールウィンドウが閉じられますが、それ以外のタイミングで閉じたい場合には `Console::Close()` を呼びます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Console::Open();

	std::wcout << L"Siv3D\n";

	int32 n;

	std::wcin >> n;

	Println(n);

	Console::Close();

	while (System::Update())
	{

	}
}
```
