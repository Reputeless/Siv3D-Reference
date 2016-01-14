# Namespace

ライブラリの名前空間の使用を設定します。

## using namespace s3d を無効にする
Siv3D.hpp をインクルードする前にマクロ `NO_S3D_USING` を定義すると、`using namespace s3d` が無効になります。
```cpp
# define NO_S3D_USING
# include <Siv3D.hpp>

void Main()
{
	while (s3d::System::Update())
	{
		s3d::Circle(s3d::Mouse::Pos(), 50).draw();
	}
}
```
