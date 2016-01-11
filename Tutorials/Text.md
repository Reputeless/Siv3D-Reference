# 16. テキストファイル

## テキストファイルを作成して文字列を書き込む

```cpp
# include <Siv3D.hpp>

void Main()
{
	TextWriter writer(L"Tutorial-TextWriter.txt");

	writer.write(L"Siv");

	writer.write(L"3D");

	writer.writeln(L" Engine");

	writer.writeln(L"TextWriter");
}
```
作成される Tutorial-TextWriter.txt
> Siv3D Engine  
> TextWriter

## テキストファイルにデータを書き込む
`Format()` や `Println()` と同じように、数値を文字列に変換できます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	TextWriter writer(L"Tutorial-TextWriter.txt");

	writer.writeln(L"Siv3D Engine");

	writer.writeln(12345);

	writer.writeln(L"円周率は ", Pi);

	writer.writeln(Vec2(10, 20));
}
```
作成される Tutorial-TextWriter.txt
> Siv3D Engine  
> 12345  
> 円周率は 3.14159  
> (10,20)  

## テキストファイルから 1 文字ずつ読み取る

```cpp
# include <Siv3D.hpp>

void Main()
{
	TextReader reader(L"Example/test.txt");

	wchar ch;

	while (reader.readChar(ch))
	{
		Print(ch);
	}

	WaitKey();
}
```

## テキストファイルから 1 行ずつ読み取る

```cpp
# include <Siv3D.hpp>

void Main()
{
	TextReader reader(L"Example/test.txt");

	String line;

	while (reader.readLine(line))
	{
		Println(line);
	}

	WaitKey();
}
```

## テキストファイルの中身を全部読み込む

```cpp
# include <Siv3D.hpp>

void Main()
{
	TextReader reader(L"Example/test.txt");

	const String s = reader.readAll();

	Println(s);

	WaitKey();
}
```

[← 前の章へ戻る](System.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Text-data.md)