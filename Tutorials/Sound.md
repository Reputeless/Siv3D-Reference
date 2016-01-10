# 8. サウンドの再生

## 再生する

```cpp
# include <Siv3D.hpp>

void Main()
{
	// サウンドファイルをロード
	const Sound sound(L"Example/風の丘.mp3");

	if (!sound)
	{
		// ロードに失敗したら終了
		return;
	}

	// 再生
	sound.play();

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
	const Sound sound(L"Example/風の丘.mp3");

	while (System::Update())
	{
		// [P] キーがクリックされたら
		if (Input::KeyP.clicked)
		{
			// 再生中だったら
			if (sound.isPlaying())
			{
				// 一時停止
				sound.pause();
			}
			else
			{
				// 再生
				sound.play();
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
	const Sound sound(L"Example/風の丘.mp3");

	while (System::Update())
	{
		if (Input::KeyP.clicked)
		{
			if (sound.isPlaying())
			{
				// 停止して曲の先頭に戻る
				sound.stop();
			}
			else
			{
				// 再生
				sound.play();
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
	const Sound sound(L"Example/風の丘.mp3");

	// デフォルトの音量は 1.0
	sound.play();

	while (System::Update())
	{
		// [0] キーがクリックされたら
		if (Input::Key0.clicked)
		{
			// 音量 0（無音）
			sound.setVolume(0.0);
		}

		if (Input::Key1.clicked)
		{
			sound.setVolume(0.2);
		}

		if (Input::Key2.clicked)
		{
			sound.setVolume(0.5);
		}

		if (Input::Key3.clicked)
		{
			// 音量 1.0（デフォルト）
			sound.setVolume(1.0);
		}
	}
}
```

## 再生スピードを変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Sound sound(L"Example/風の丘.mp3");

	sound.play();

	while (System::Update())
	{
		if (Input::Key1.clicked)
		{
			sound.setSpeed(0.5);	// 0.5 倍速
		}

		if (Input::Key2.clicked)
		{
			sound.setSpeed(1.0);	// 通常の速度
		}

		if (Input::Key3.clicked)
		{
			sound.setSpeed(1.5);	// 1.5 倍速
		}
	}
}
```

## 再生ピッチとテンポを変える
![再生ピッチとテンポを変える](resource/Sound/tempo.png "再生ピッチとテンポを変える")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Sound sound(L"Example/風の丘.mp3");

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

## 再生位置を取得する
![再生位置を取得する](resource/Sound/pos.png "再生位置を取得する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	const Sound sound(L"Example/風の丘.mp3");

	sound.play();

	while (System::Update())
	{
		// 曲の長さ（秒）
		const int32 length = static_cast<int32>(sound.lengthSec());

		// 現在の再生位置（秒）
		const int32 pos = static_cast<int32>(sound.streamPosSec());

		// 再生位置を表示
		font(pos, L" 秒 /", length, L" 秒").draw();
	}
}
```

## 再生位置を変更する
![再生位置を変更する](resource/Sound/setpos.png "再生位置を変更する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	const Sound sound(L"Example/風の丘.mp3");

	sound.play();

	while (System::Update())
	{
		// 曲の長さ（秒）
		const int32 length = static_cast<int32>(sound.lengthSec());

		// 現在の再生位置（秒）
		const int32 pos = static_cast<int32>(sound.streamPosSec());

		// 再生位置を表示
		font(pos, L" 秒 /", length, L" 秒").draw();

		if (Input::Key0.clicked)
		{
			sound.setPosSec(0.0); // 曲の先頭に移動
		}

		if (Input::Key1.clicked)
		{
			// 曲の 20 % の位置に移動
			// 位置は 秒 で指定する
			sound.setPosSec(sound.lengthSec() * 0.2);
		}

		if (Input::Key2.clicked)
		{
			// 曲の真ん中に移動
			sound.setPosSec(sound.lengthSec() * 0.5);
		}
	}
}
```

## ループ再生する
![ループ再生する](resource/Sound/setloop.png "ループ再生する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	const Sound sound(L"Example/風の丘.mp3");

	// ループ再生するよう設定
	sound.setLoop(true);

	sound.play();

	while (System::Update())
	{
		// 曲の長さ（秒）
		const int32 length = static_cast<int32>(sound.lengthSec());

		// 現在の再生位置（秒）
		const int32 pos = static_cast<int32>(sound.streamPosSec());

		// 再生位置を表示
		font(pos, L" 秒 /", length, L" 秒").draw();
	}
}
```

## 範囲を指定してループ再生する
![範囲を指定してループ再生する](resource/Sound/setloop2.png "範囲を指定してループ再生する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	const Sound sound(L"Example/風の丘.mp3");

	// 始点（1.5秒）と 終点（44.5秒）の間でループ再生するよう設定
	sound.setLoopBySec(true, 1.5s, 44.5s);

	sound.play();

	while (System::Update())
	{
		// 曲の長さ（秒）
		const int32 length = static_cast<int32>(sound.lengthSec());

		// 現在の再生位置（秒）
		const int32 pos = static_cast<int32>(sound.streamPosSec());

		// 再生位置を表示
		font(pos, L" 秒 /", length, L" 秒").draw();
	}
}
```

## 同じサウンドを重ねて再生する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	// 効果音
	const Sound sound(L"Example/Sound.mp3");

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			// すでに再生中でも重ねて再生
			// 音割れしないよう音量を 0.4 に下げる
			sound.playMulti(0.4);
		}
	}
}
```

## サウンドをフェードインさせる

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Sound sound(L"Example/風の丘.mp3");

	// 4.0 秒かけてフェードイン
	sound.play(4.0s);

	while (System::Update())
	{

	}
}
```

## サウンドをフェードアウトさせる

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Sound sound(L"Example/風の丘.mp3");

	sound.play();

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			// 3.0 秒かけてフェードアウト、その後 pause
			sound.pause(3.0s);
		}
	}
}
```

## マスターボリュームを設定する

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	const Sound sound(L"Example/風の丘.mp3");

	const Sound sound2(L"Example/sound.mp3");

	sound.play();

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			sound2.playMulti(0.4);
		}

		const double volume = Mouse::Pos().x / 640.0;

		MasterVoice::SetVolume(volume);

		font(volume).draw();
	}
}
```

[← 前の章へ戻る](Mouse.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Midi.md)