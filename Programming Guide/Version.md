# Version

## ライブラリのバージョンを調べる  
マクロ `Siv3DVersion` が Siv3D ライブラリのバージョン文字列を、`Siv3DVersionID` が数値形式のバージョン ID を示します。バージョン ID は新しいリリースほど大きい数になります。

```cpp
# include <Siv3D.hpp>

void Main()
{
	Println(Siv3DVersion);

	Println(Siv3DVersionID);

	WaitKey();
}
```
