# Version

### ライブラリのバージョンを調べる  
マクロ `Siv3DVersion` は Siv3D ライブラリのバージョン文字列を、  
マクロ `Siv3DVersionID` は数値形式のバージョン ID を示します。  
バージョン ID は新しいリリースほど大きい数になります。

```cpp
# include <Siv3D.hpp>

void Main()
{
	Println(Siv3DVersion);

	Println(Siv3DVersionID);

	WaitKey();
}
```

### Siv3DVersion と Siv3DVersionID の対応表

| ライブラリのバージョン | Siv3DVersion | Siv3DVersionID |
|:-------------|:-------------|:-----:|
| Siv3D January 2016             | L"January 2016" | 20160110 |
