# MIDI シーケンサー
![MIDI シーケンサー](resource/MidiSequencer/MidiSequencer.png "MIDI シーケンサー") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(480, 480);
	Graphics::SetBackground(Palette::White);
	Midi::SendMessage(MidiMessage::SetInstrument(0, GMInstrument::MusicBox));

	const Array<uint8> midis{ 86, 84, 83, 81, 79, 77, 76, 74, 72, 71, 69, 67, 65, 64, 62, 60 };
	const int32 dotSize = 30;

	Grid<bool> dots(16, 16);
	int32 previousLine = 0;

	while (System::Update())
	{
		const int32 currentLine = Time::MillisecSince1601() / 160 % 16;

		if (currentLine != previousLine)
		{
			for (auto i : step(dots.height))
			{
				Midi::SendMessage(dots[i][currentLine] ?
					MidiMessage::NoteOn(0, midis[i]) : MidiMessage::NoteOff(0, midis[i]));
			}

			previousLine = currentLine;
		}

		for (auto p : step({ dots.width, dots.height }))
		{
			Rect rect(p * dotSize, dotSize, dotSize);

			if (rect.leftClicked)
			{
				dots[p.y][p.x] = !dots[p.y][p.x];
			}

			const Color color = HSV(40, 0.2 + dots[p.y][p.x] * 0.8 - (p.x == currentLine) * 0.2, 0.9 + dots[p.y][p.x] * 0.1);

			rect.stretched(-1).draw(color);
		}
	}
}
```
