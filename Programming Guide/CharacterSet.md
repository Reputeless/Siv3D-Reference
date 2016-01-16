# CharacterSet
マルチバイト文字列や Unicode 文字列の相互変換や、パーセントエンコードを行います。

## 文字列変換早見表

|                  | std::string へ    | std::wstring へ | String へ | const char* へ           | const wchar* へ        |
|:----------------:|:----------------:|:---------------:|:---------:|:------------------------:|:---------------------:|
| std::string から  | =                | Widen().str()   | Widen()   | std::string::c_str()     | Widen().c_str()       |
| std::wstring から | Narrow()         | =               | =         | Narrow().c_str()         | std::wstring::c_str() |
| String から       | String::narrow() | String::str()   | =         | String::narrow().c_str() | String::c_str()       |


## std::string から String に変換する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const std::string s1 = "いろはにほへと";

	const String s2 = Widen(s1);

	Println(s2);

	WaitKey();
}
```

## std::wstring から String に変換する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const std::wstring s1 = L"いろはにほへと";

	const String s2 = s1;

	Println(s2);

	WaitKey();
}
```

## String から std::string に変換する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const String s1 = L"いろはにほへと";

	const std::string s2 = s1.narrow();

	Println(s2 == "いろはにほへと");

	WaitKey();
}
```

## String から std::wstring に変換する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const String s1 = L"いろはにほへと";

	const std::wstring s2 = s1.str();

	Println(s2 == L"いろはにほへと");

	WaitKey();
}
```

## String から const char* に変換する

```cpp
# include <Siv3D.hpp>

std::string Str(const char* str)
{
	return std::string(str);
}

void Main()
{
	const String s1 = L"いろはにほへと";

	const std::string s2 = Str(s1.narrow().c_str());

	Println(Widen(s2));

	WaitKey();
}
```

## String から const wchar_t* に変換する

```cpp
# include <Siv3D.hpp>

std::wstring Str(const wchar_t* str)
{
	return std::wstring(str);
}

void Main()
{
	const String s1 = L"いろはにほへと";

	const std::wstring s2 = Str(s1.c_str());

	Println(s2);

	WaitKey();
}
```

## UTF8 から String に変換する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const String text = L"ABCDEF%E3%81%84%E3%82%8D%E3%81%AF%E3%81%AB%E3%81%BB%E3%81%B8%E3%81%A8";

	std::string utf8;

	// UTF-8 URL デコード
	for (size_t i = 0; i < text.length; ++i)
	{
		if (text[i] == L'%')
		{
			const String code = { text[i + 1], text[i + 2] };

			utf8.push_back(FromString<uint8>(code, 16));

			i += 2;
		}
		else
		{
			utf8.push_back(static_cast<uint8>(text[i]));
		}
	}

	Println(FromUTF8(utf8));

	WaitKey();
}
```

## String から UTF8 に変換する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const String text = L"いろはにほへと";

	const String unreserved(L"-._~");

	String encoded;

	// UTF-8 URL エンコード
	for (auto ch : ToUTF8(text))
	{
		if (IsAlnum(ch) || unreserved.includes(ch))
		{
			encoded.push_back(ch);
		}
		else
		{
			encoded.push_back(L'%');

			encoded.append(Pad(ToHex<uint8>(ch), { 2, L'0' }).upper());
		}
	}

	Println(encoded);

	WaitKey();
}
```

## 文字列をパーセントエンコードする

```cpp
# include <Siv3D.hpp>

void Main()
{
	Println(CharacterSet::PercentEncode(L"いろはにほへと"));

	WaitKey();
}
```

## ASCII 文字で構成されたマルチバイト文字列を String に変換する
`Widen` よりも高速に変換を行います。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Println(WidenAscii("Siv3D"));

	WaitKey();
}
```

## ASCII 文字で構成された String を std::string に変換する
`Narrow` よりも高速に変換を行います。
```cpp
# include <Siv3D.hpp>

void Main()
{
	const std::string str = NarrowAscii(L"Siv3D");

	Println(str == "Siv3D");

	WaitKey();
}
```
