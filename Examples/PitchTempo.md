# テンポとピッチの変更
![テンポとピッチの変更](resource/PitchTempo/PitchTempo.png "テンポとピッチの変更") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Sound sound = Dialog::OpenSound();

	if (!sound)
	{
		return;
	}

	sound.play();

	while (System::Update())
	{
		Line(0, 240, 640, 240).drawArrow(4, { 20, 20 });
		Line(320, 480, 320, 0).drawArrow(4, { 20, 20 });

		const Point pos = Mouse::Pos();
		Circle(pos, 20).draw(Palette::Orange);

		const double tempo = Exp2((pos.x - 320) / 240.0);
		const double pitch = -(pos.y - 240) / 80.0;

		sound.changeTempo(tempo);
		sound.changePitchSemitones(pitch);

		PutText(L"tempo: {}\npitch: {}"_fmt, tempo, pitch).from(20, 20);
	}
}
```
