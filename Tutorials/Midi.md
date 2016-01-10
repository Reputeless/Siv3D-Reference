# 9. MIDI の再生

## 再生する

```cpp
# include <Siv3D.hpp>

void Main()
{
	// MIDI をオープンする
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		// コンピュータ－が MIDI の再生に対応していないか、
		// ファイルのオープンに失敗したら終了
		return;
	}

	// オープンした MIDI を再生開始
	Midi::Play();

	while (System::Update())
	{

	}
}
```

## 一時停止する

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	while (System::Update())
	{
		// [P] キーがクリックされたら
		if (Input::KeyP.clicked)
		{
			// 再生中だったら
			if (Midi::IsPlaying())
			{
				// 一時停止
				Midi::Pause();
			}
			else
			{
				// 再生
				Midi::Play();
			}
		}
	}
}
```

## 一時停止する

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	while (System::Update())
	{
		// [P] キーがクリックされたら
		if (Input::KeyP.clicked)
		{
			// 再生中だったら
			if (Midi::IsPlaying())
			{
				// 一時停止
				Midi::Pause();
			}
			else
			{
				// 再生
				Midi::Play();
			}
		}
	}
}
```

## 停止して曲の先頭に戻る

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	while (System::Update())
	{
		if (Input::KeyP.clicked)
		{
			if (Midi::IsPlaying())
			{
				// 停止して曲の先頭に戻る
				Midi::Stop();
			}
			else
			{
				// 再生
				Midi::Play();
			}
		}
	}
}
```

## 音量を変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	// デフォルトの音量は 1.0
	Midi::Play();

	while (System::Update())
	{
		if (Input::Key0.clicked)
		{
			// 音量 0（無音）
			Midi::SetVolume(0.0);
		}

		if (Input::Key1.clicked)
		{
			Midi::SetVolume(0.2);
		}

		if (Input::Key2.clicked)
		{
			Midi::SetVolume(0.5);
		}

		if (Input::Key3.clicked)
		{
			// 音量 1.0 （デフォルト）
			Midi::SetVolume(1.0);	
		}
	}
}
```

## テンポを変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	Midi::Play();

	while (System::Update())
	{
		if (Input::Key1.clicked)
		{
			// 0.5 倍速
			Midi::SetTempo(0.5);
		}

		if (Input::Key2.clicked)
		{
			// 通常のテンポ
			Midi::SetTempo(1.0);
		}

		if (Input::Key3.clicked)
		{
			// 1.5 倍速
			Midi::SetTempo(1.5);
		}
	}
}
```

## ピッチを変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	Midi::Play();

	while (System::Update())
	{
		if (Input::Key1.clicked)
		{
			// -6
			Midi::SetPitch(-6.0);
		}

		if (Input::Key2.clicked)
		{
			// 通常のピッチ
			Midi::SetPitch(0.0);
		}

		if (Input::Key3.clicked)
		{
			// +6
			Midi::SetPitch(6.0);
		}
	}
}
```

## 再生位置を取得する
![再生位置を取得する](resource/Midi/pos.png "再生位置を取得する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	Midi::Play();

	while (System::Update())
	{
		// 曲の長さ（秒）
		const int32 length = static_cast<int32>(Midi::GetLengthSec());

		// 現在の再生位置（秒）
		const int32 pos = static_cast<int32>(Midi::GetPosSec());

		// 再生位置を表示
		font(pos, L" 秒 /", length, L" 秒").draw();
	}
}
```

## 再生位置を変更する
![再生位置を変更する](resource/Midi/setpos.png "再生位置を変更する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	Midi::Play();

	while (System::Update())
	{
		const int32 length = static_cast<int32>(Midi::GetLengthSec());

		const int32 pos = static_cast<int32>(Midi::GetPosSec());

		font(pos, L" 秒 /", length, L" 秒").draw();

		if (Input::Key0.clicked)
		{
			// 曲の先頭に移動
			Midi::SetPosSec(0.0);
		}

		if (Input::Key1.clicked)
		{
			// 曲の 20 % の位置に移動
			// 位置は 秒 で指定する
			Midi::SetPosSec(Midi::GetLengthSec() * 0.2);
		}

		if (Input::Key2.clicked)
		{
			// 曲の真ん中に移動
			Midi::SetPosSec(Midi::GetLengthSec() * 0.5);
		}
	}
}
```

## ループ再生する
![ループ再生する](resource/Midi/playloop.png "ループ再生する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	if (!Midi::Open(L"Example/Prokofiev.mid"))
	{
		return;
	}

	// ループ再生する
	Midi::PlayLoop();

	while (System::Update())
	{
		const int32 length = static_cast<int32>(Midi::GetLengthSec());

		const int32 pos = static_cast<int32>(Midi::GetPosSec());

		font(pos, L" 秒 /", length, L" 秒").draw();
	}
}
```

## MIDI メッセージを使って演奏する
MIDI 規格に沿ってメッセージを送信することで音楽を演奏できます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Array<std::pair<Key, GMInstrument>> instruments
	{
		{ Input::Key1, GMInstrument::Piano1 },
		{ Input::Key2, GMInstrument::Marimba },
		{ Input::Key3, GMInstrument::Harmonica },
		{ Input::Key4, GMInstrument::JazzGuitar },
		{ Input::Key5, GMInstrument::Violin },
		{ Input::Key6, GMInstrument::VoiceOohs },
		{ Input::Key7, GMInstrument::FrenchHorn },
		{ Input::Key8, GMInstrument::SquareWave },
	};

	const Array<std::pair<Key, PitchName>> keys
	{
		{ Input::KeyA, PitchName::C4 },
		{ Input::KeyS, PitchName::D4 },
		{ Input::KeyD, PitchName::E4 },
		{ Input::KeyF, PitchName::F4 },
		{ Input::KeyG, PitchName::G4 },
		{ Input::KeyH, PitchName::A4 },
		{ Input::KeyJ, PitchName::B4 },
		{ Input::KeyK, PitchName::C5 },
	};

	while (System::Update())
	{
		for (const auto& instrument : instruments)
		{
			if (instrument.first.clicked)
			{
				Midi::SendMessage(MidiMessage::SetInstrument(0, instrument.second));
			}
		}

		for (const auto& key : keys)
		{
			if (key.first.clicked)
			{
				Midi::SendMessage(MidiMessage::NoteOn(0, key.second));
			}
			else if (key.first.released)
			{
				Midi::SendMessage(MidiMessage::NoteOff(0, key.second));
			}
		}
	}
}
```

[← 前の章へ戻る](Sound.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Window.md)