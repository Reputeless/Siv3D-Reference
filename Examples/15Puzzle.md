# 15 パズル
![15 パズル](resource/15Puzzle/15Puzzle.gif "15 パズル")  
イラスト: <a href="http://www.pixiv.net/member.php?id=583587" target="_blank">古古米</a> さん
```cpp
# include <Siv3D.hpp>

bool Swappable(int32 a, int32 b)
{
	return (a / 4 == b / 4 && Abs(a - b) == 1) || (a % 4 == b % 4 && Abs(a - b) == 4);
}

void Main()
{
	const Texture texture = Dialog::OpenTexture(TextureDesc::Mipped);
	const int32 pieceSize = 100;
	Optional<int32> grabbed;
	std::array<Optional<int32>, 16> pieces = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	for (int32 i = 0; i < 10000; ++i)
	{
		const int32 a = Random(0, 15);
		const int32 b = a + RandomSelect({ -4, -1, 1, 4 });

		if (pieces[a] && InRange(b, 0, 15) && !pieces[b] && Swappable(a, b))
		{
			std::swap(pieces[a], pieces[b]);
		}
	}

	while (System::Update())
	{
		if (!Input::MouseL.pressed)
		{
			grabbed = none;
		}

		for (auto i : step(16))
		{
			const Rect pieceRect(i % 4 * pieceSize, i / 4 * pieceSize, pieceSize, pieceSize);

			if (!pieces[i])
			{
				if (grabbed && pieceRect.mouseOver && Swappable(i, grabbed.value()))
				{
					std::swap(pieces[i], pieces[grabbed.value()]);
					grabbed = none;
				}

				continue;
			}

			const int32 offset = pieces[i].value();
			pieceRect(texture.uv(offset % 4 * 0.25, offset / 4 * 0.25, 0.25, 0.25)).draw();

			if (pieceRect.leftPressed)
			{
				grabbed = i;
				pieceRect.draw({ 255, 0, 0, 80 });
			}

			pieceRect.drawFrame();
		}

		texture.resize(200, 200).draw(440, 200);
	}
}
```
