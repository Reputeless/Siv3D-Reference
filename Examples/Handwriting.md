# 手書き文字認識
![手書き文字認識](resource/Handwriting/Handwriting.gif "手書き文字認識") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	const HandwritingRecognizer recognizer(L"Example/Hiragana.model");
	const Font font(34);

	Image image(400, 400, Palette::White);
	
	DynamicTexture texture(image);

	Array<Array<Point>> pointsList;

	while (System::Update())
	{
		texture.draw();

		if (Input::MouseL.pressed)
		{
			if (Input::MouseL.clicked)
			{
				pointsList.emplace_back();
			}

			pointsList.back().push_back(Mouse::Pos());

			const Point from = Input::MouseL.clicked ? Mouse::Pos() : Mouse::PreviousPos();

			Line(from, Mouse::Pos()).overwrite(image, 8, Palette::Blue);

			texture.fill(image);
		}

		if (Input::MouseR.clicked)
		{
			pointsList.clear();
			
			image.fill(Palette::White);
			
			texture.fill(image);
		}

		const auto results = recognizer.recognize(image.size, pointsList);

		for (auto i : step(int(results.size())))
		{
			const String text = results[i].character;

			const double score = results[i].score;

			const Rect rect(440, 20 + i * 70, 120, 60);

			rect.draw(HSV(40, 1.0, Saturate(score + 1.0)));

			font(text).drawCenter(rect.center, Palette::Black);
		}
	}
}
```
