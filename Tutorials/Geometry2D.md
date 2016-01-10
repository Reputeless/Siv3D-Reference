# 11. 図形のあたり判定

## 図形とカーソル
![図形とカーソル](resource/Geometry2D/mouseover.gif "図形とカーソル")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Rect rect(20, 20, 200, 100);

	const Circle circle(150, 300, 100);

	const Polygon star
	{
		{ 430, 100 },{ 470, 240 },
		{ 610, 240 },{ 505, 325 },
		{ 545, 460 },{ 430, 380 },
		{ 315, 460 },{ 355, 325 },
		{ 250, 240 },{ 390, 240 }
	};

	while (System::Update())
	{
		// 長方形の上にカーソルがあるか
		const bool r = rect.mouseOver;

		// 円の上にカーソルがあるか
		const bool c = circle.mouseOver;

		// 多角形の上にカーソルがあるか
		const bool s = star.mouseOver;

		// カーソルが重なっていたら赤、そうでなかったら黄色で図形を描く
		rect.draw(r ? Palette::Red : Palette::Yellow);

		circle.draw(c ? Palette::Red : Palette::Yellow);

		star.draw(s ? Palette::Red : Palette::Yellow);
	}
}
```

## 図形とクリック
![XXXXXXXX図形とクリックXXXXx](resource/Geometry2D/pressed.gif "図形とクリック")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Rect rect(20, 20, 200, 100);

	const Circle circle(150, 300, 100);

	const Polygon star
	{
		{ 430, 100 },{ 470, 240 },
		{ 610, 240 },{ 505, 325 },
		{ 545, 460 },{ 430, 380 },
		{ 315, 460 },{ 355, 325 },
		{ 250, 240 },{ 390, 240 }
	};

	while (System::Update())
	{
		// 長方形がマウスの左ボタンで押されているか
		const bool r = rect.leftPressed;

		// 円がマウスの左ボタンで押されているか
		const bool c = circle.leftPressed;

		// 多角形がマウスの左ボタンで押されているか
		const bool s = star.leftPressed;

		// マウスの左ボタンで押されていたら赤、そうでなかったら黄色で図形を描く
		rect.draw(r ? Palette::Red : Palette::Yellow);

		circle.draw(c ? Palette::Red : Palette::Yellow);

		star.draw(s ? Palette::Red : Palette::Yellow);
	}
}
```

## 図形 vs 図形 | 交差
![図形 vs 図形 | 交差](resource/Geometry2D/intersects.gif "図形 vs 図形 | 交差")  
図形.intersects(図形) を使うと、`Point`, `Rect`, `Circle`, `Line`, `Triangle`, `Quad`, `Polygon` 等さまざまな図形同士であたり判定ができます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Rect rect(20, 20, 200, 100);

	const Circle circle(150, 300, 100);

	const Polygon star
	{
		{ 430, 100 },{ 470, 240 },
		{ 610, 240 },{ 505, 325 },
		{ 545, 460 },{ 430, 380 },
		{ 315, 460 },{ 355, 325 },
		{ 250, 240 },{ 390, 240 }
	};

	while (System::Update())
	{
		// 円（プレイヤーとする）
		const Circle player(Mouse::Pos(), 30);

		// プレイヤーが長方形と重なっているか
		const bool r = player.intersects(rect);

		// プレイヤーが円と重なっているか
		const bool c = player.intersects(circle);

		// プレイヤーが多角形と重なっているか
		const bool s = player.intersects(star);

		// プレイヤーと重なっていたら赤、そうでなかったら黄色で図形を描く
		rect.draw(r ? Palette::Red : Palette::Yellow);

		circle.draw(c ? Palette::Red : Palette::Yellow);

		star.draw(s ? Palette::Red : Palette::Yellow);

		player.draw();
	}
}
```

## 図形 vs 図形 | 包含
![図形 vs 図形 | 包含](resource/Geometry2D/contains.gif "図形 vs 図形 | 包含")  
一部の図形は、図形.contains(図形) を使って、図形が包含されているかを判定できます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Window::SetPos(770, 385);
	const Rect rect(20, 20, 200, 100);

	const Circle circle(150, 300, 100);

	const Polygon star
	{
		{ 430, 100 },{ 470, 240 },
		{ 610, 240 },{ 505, 325 },
		{ 545, 460 },{ 430, 380 },
		{ 315, 460 },{ 355, 325 },
		{ 250, 240 },{ 390, 240 }
	};

	while (System::Update())
	{
		// 円（プレイヤーとする）
		const Circle player(Mouse::Pos(), 30);

		// プレイヤーが長方形と重なっているか
		const bool r = rect.contains(player);

		// プレイヤーが円と重なっているか
		const bool c = circle.contains(player);

		// プレイヤーが多角形と重なっているか
		const bool s = star.contains(player);

		// プレイヤーと重なっていたら赤、そうでなかったら黄色で図形を描く
		rect.draw(r ? Palette::Red : Palette::Yellow);

		circle.draw(c ? Palette::Red : Palette::Yellow);

		star.draw(s ? Palette::Red : Palette::Yellow);

		player.draw();
	}
}
```

[← 前の章へ戻る](Window.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Random.md)