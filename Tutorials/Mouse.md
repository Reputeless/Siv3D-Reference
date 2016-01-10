# 7. マウス入力

## カーソルの位置
![カーソルの位置](resource/Mouse/pos.png "カーソルの位置")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	while (System::Update())
	{
		// 現在のカーソルの位置
		const Point pos = Mouse::Pos();

		// カーソルの位置に黄色の円を書く
		Circle(pos, 15).draw(Palette::Yellow);

		// カーソルの位置を数字で表示
		font(pos).draw();
	}
}
```

## ボタンがクリックされた
![ボタンがクリックされた](resource/Mouse/clicked.png "ボタンがクリックされた")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	int32 count = 0;

	while (System::Update())
	{
		// マウスの左ボタンがクリックされたら
		if (Input::MouseL.clicked)
		{
			++count;
		}

		// マウスの右ボタンがクリックされたら
		if (Input::MouseR.clicked)
		{
			--count;
		}

		font(count, L'回').draw();
	}
}
```

## ボタンが押されている
![ボタンが押されている](resource/Mouse/pressed.png "ボタンが押されている")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	int count = 0;

	while (System::Update())
	{
		// マウスの左ボタンが押されていたら
		if (Input::MouseL.pressed)
		{
			++count;
		}

		// マウスの右ボタンが押されていたら
		if (Input::MouseR.pressed)
		{
			--count;
		}

		font(count, L'回').draw();
	}
}
```

## ボタンが離された
![ボタンが離された](resource/Mouse/released.png "ボタンが離された")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	int count = 0;

	while (System::Update())
	{
		// マウスの左ボタンが離されたら
		if (Input::MouseL.released)
		{
			++count;
		}

		// マウスの右ボタンが離されたら
		if (Input::MouseR.released)
		{
			--count;
		}

		font(count, L'回').draw();
	}
}
```

## カーソルの移動量
![カーソルの移動量](resource/Mouse/delta.png "カーソルの移動量")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	Point pos(200, 200);

	while (System::Update())
	{
		// 前フレームからのカーソルの移動量
		const Point delta = Mouse::Delta();

		pos += delta;

		Circle(pos, 15).draw(Palette::Yellow);

		// 移動量を数字で表示
		font(delta).draw();
	}
}
```

## ホイールの回転
![ホイールの回転](resource/Mouse/wheel.png "ホイールの回転")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Point pos(200, 200);

	while (System::Update())
	{
		// 縦方向のホイール回転量
		const int32 wheelY = Mouse::Wheel();

		// 横方向のホイール回転量
		const int32 wheelX = Mouse::WheelH();

		pos.y += wheelY;
		pos.x += wheelX;

		// ホイールを動かすと、黄色い四角が動く
		Rect(pos, 100, 100).draw(Palette::Yellow);
	}
}
```

## キーとの組み合わせ
![キーとの組み合わせ](resource/Mouse/combine.png "キーとの組み合わせ")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const auto ok = Input::KeyZ
		| Input::KeySpace
		| Input::KeyEnter
		| Input::MouseL;

	while (System::Update())
	{
		if (ok.pressed)
		{
			Circle(100, 100, 100).draw();
		}
	}
}
```

[← 前の章へ戻る](Key.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Sound.md)