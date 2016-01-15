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

## using namespace s3d::Math を無効にする
Siv3D.hpp をインクルードする前にマクロ `NO_MATH_USING` を定義すると、`using namespace s3d::Math` が無効になります。
```cpp
# define NO_MATH_USING
# include <Siv3D.hpp>

void Main()
{
	Println(Math::Sin(Math::Pi));
	
	WaitKey();
}
```

## using namespace ham を無効にする
HamFramework.hpp をインクルードする前にマクロ `NO_HAM_USING` を定義すると、`using namespace ham` が無効になります。
```cpp
# include <Siv3D.hpp>
# define NO_HAM_USING
# include <HamFramework.hpp>

using MyApp = ham::SceneManager<String>;

struct Game : MyApp::Scene
{
	void update() {}

	void draw() const {}
};

void Main()
{
	MyApp manager(ham::SceneManagerOption::ShowSceneName);
	manager.add<Game>(L"Game");

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
```
