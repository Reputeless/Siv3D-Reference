# MIDI ビジュアライザー
![MIDI ビジュアライザー](resource/MIDIVisualizer/MIDIVisualizer.png "MIDI ビジュアライザー") 
```cpp
# include <Siv3D.hpp>

struct Note
{
	uint32 ch;
	uint32 noteNumber;
	int32 startMillisec;
	int32 lengthMillisec;

	double alpha;
	bool barPassed;
	bool onBar;
};

void Main()
{
	Window::Resize(1280, 720);

	Midi::Open(Dialog::GetOpenMidi().value());
	const auto score = Midi::GetScore();
	Array<Note> noteRects;
	uint32 minPitch = 127, maxPitch = 0;

	for (auto ch : step(static_cast<uint32>(score.size())))
	{
		for (const auto& note : score[ch])
		{
			noteRects.push_back({ ch, note.noteNumber, note.startMillisec, note.lengthMillisec, 1.0, false, false });
			minPitch = Min(minPitch, note.noteNumber);
			maxPitch = Max(maxPitch, note.noteNumber);
		}
	}

	while (System::Update())
	{
		const double scale = 0.2;
		const int32 offset = 160;
		const int32 offsetMillisec = static_cast<int32>(offset / scale);
		const RectF line(offset - 1, 0, 6, Window::Height());
		const double blockHeight = static_cast<double>(Window::Height()) / (maxPitch - minPitch + 1);

		if (!Midi::IsPlaying())
		{
			for (auto& note : noteRects)
			{
				note.alpha = 1.0;
				note.barPassed = false;
				note.onBar = false;
			}
		}

		if (Input::MouseL.clicked)
		{
			Midi::Play();
		}

		const double pos = (Midi::GetPosSec() * 1000 - 100)* scale;
		const int32 bar = static_cast<int32>(Midi::GetPosSec() * 1000 - 100);
		const int32 left = bar - offsetMillisec;
		const int32 right = static_cast<int32>(left + Window::Width() / scale);

		Array<size_t> visibleNoteIndices;
		size_t index = 0;

		for (auto& note : noteRects)
		{
			if (right < note.startMillisec || (note.startMillisec + note.lengthMillisec) < left)
			{
				++index;
				continue;
			}

			note.onBar = note.startMillisec <= bar && bar <= (note.startMillisec + note.lengthMillisec);
			note.barPassed = note.startMillisec <= bar;

			if (note.barPassed)
			{
				note.alpha *= note.onBar ? 0.98 : 0.85;
			}

			visibleNoteIndices.push_back(index++);
		}

		Graphics2D::SetBlendState(BlendState::Default);

		for (auto& i : visibleNoteIndices)
		{
			const auto& note = noteRects[i];

			if (!note.barPassed)
			{
				const RectF r(note.startMillisec * scale + offset - pos, (maxPitch - note.noteNumber) * blockHeight, note.lengthMillisec * scale, blockHeight);
				RoundRect(r, 4).draw(ColorF(0.2, 0.25, 0.3));
			}
		}

		Graphics2D::SetBlendState(BlendState::Additive);

		for (auto& i : visibleNoteIndices)
		{
			const auto& note = noteRects[i];

			if (note.barPassed)
			{
				const RectF r(note.startMillisec * scale + offset - pos, (maxPitch - note.noteNumber) * blockHeight, note.lengthMillisec * scale, blockHeight);
				RoundRect(r, 5).drawShadow({ 0, 0 }, 12 + note.alpha * 8, 2 + note.alpha * 8, HSV(30 + note.ch * 100, 0.5, 1).toColorF(note.alpha*0.4));
			}
		}

		for (auto& i : visibleNoteIndices)
		{
			const auto& note = noteRects[i];

			if (note.barPassed)
			{
				const RectF r(note.startMillisec * scale + offset - pos, (maxPitch - note.noteNumber) * blockHeight, note.lengthMillisec * scale, blockHeight);
				RoundRect(r, 4).draw(HSV(30 + note.ch * 100, 1, 1).toColorF(note.alpha));
			}
		}

		line.draw(Alpha(20));
	}
}
```
