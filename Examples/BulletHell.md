# シューティングゲーム
![シューティングゲーム](resource/BulletHell/BulletHell.png "シューティングゲーム") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Window::SetTitle(L"Siv Shooting | [Z]: shot / 十字キー: 移動");

	const Texture texture(Image(640, 960,[n = PerlinNoise()](auto p)
	{
		return HSV(220, 0.9 * n.octaveNoise0_1(p.x / 160.0, Abs(p.y / 120.0 - 4.0), 8), 0.8);
	}));

	const Font font(20);
	Array<Vec2> shots, bullets, enemies;
	Triangle player(300, 200, 20.0);
	int32 count = 0, crash = 0, score = 0, highSore = 0;

	while (System::Update())
	{
		++count;

		const int32 skyOffset = System::FrameCount() % 960 * 8;
		texture(0, -skyOffset / 2, 640, 480).draw();
		texture(0, -skyOffset, 640, 480).draw(Alpha(80));

		if (count % (24 - Min(count / 60, 18)) == 0)
			enemies.emplace_back(Random(40, 600), -40);

		Vec2 dir(Input::KeyRight.pressed - Input::KeyLeft.pressed, Input::KeyDown.pressed - Input::KeyUp.pressed);

		if (!dir.isZero())
			player.moveBy(dir.setLength(Input::KeyShift.pressed ? 4.5 : 9.0));

		player.setCentroid(Clamp(player.centroid().x, 0.0, 640.0), Clamp(player.centroid().y, 0.0, 480.0));

		if (Input::KeyZ.pressed && count % 4 == 0)
			shots.push_back(player.p0);

		for (auto& shot : shots)
			shot.y -= 8.0;

		for (auto& bullet : bullets)
			bullet.y += 4.0;

		for (auto& enemy : enemies)
		{
			enemy.y += 2.0;

			if (count % 60 == 0)
				bullets.push_back(enemy);
		}

		if (AnyOf(bullets, [=](const Vec2& b) { return player.intersects(b); })
			|| AnyOf(enemies, [=](const Vec2& e) { return e.y > 490.0; }))
		{
			count = score = 0;
			crash = 60;
		}

		Erase_if(shots, [](const Vec2& s) { return s.y < -10.0; });

		Erase_if(bullets, [](const Vec2& b) { return b.y > 490.0; });

		Erase_if(enemies, [&](const Vec2& e) {
			if (AnyOf(shots, [=](const Vec2& s) { return e.distanceFrom(s) < 20.0; }))
			{
				++score;
				return true;
			}
			else return e.y > 490.0;
		});

		for (const auto& shot : shots)
			Circle(shot, 7).drawFrame(4, 0, Palette::Orange);

		for (const auto& bullet : bullets)
			Circle(bullet, 4).draw();

		for (const auto& enemy : enemies)
			RectF(30, 30).setCenter(enemy).rotated(enemy.y / 100.0).draw(Palette::Black);

		player.draw();

		if (crash)
			Window::ClientRect().draw(Alpha(--crash * 3));

		font(L"Hi:{}\n{}"_fmt, highSore = Max(score, highSore), score).draw(20, 20);
	}
}
```
