# 23. マイク入力

## 利用可能な録音デバイスの一覧を取得する

```cpp
# include <Siv3D.hpp>

void Main()
{
	for (const auto& recorder : RecorderManager::Enumerate())
	{
		// デバイス ID と録音デバイスの名前を表示
		Println(recorder.deviceID, L": ", recorder.name);
	}

	WaitKey();
}
```

## 録音する

```cpp
# include <Siv3D.hpp>

void Main()
{
	Recorder recorder;

	// デバイス ID: 0 の録音デバイスで 5 秒間の録音用バッファを確保
	if (!recorder.open(0, 5s))
	{
		return;
	}

	if (!recorder.start())
	{
		return;
	}

	while (System::Update())
	{
		// バッファいっぱいまで録音が完了したら
		if (recorder.isEnded())
		{
			System::Exit();
		}
	}

	// 録音した音声を保存
	recorder.getWave().save(L"Tutorial-Recorder.wav");
}
```

## 録音設定を変える

```cpp
# include <Siv3D.hpp>

void Main()
{
	Recorder recorder;

	// サンプリングレート 11.025kHz で録音（デフォルトは 44.1kHz）
	if (!recorder.open(0, 5s, RecordingFormat::S11025))
	{
		return;
	}

	if (!recorder.start())
	{
		return;
	}

	while (System::Update())
	{
		// バッファいっぱいまで録音が完了したら
		if (recorder.isEnded())
		{
			System::Exit();
		}
	}

	// 録音した音声を保存
	recorder.getWave().save(L"Tutorial-Recorder.wav");
}
```

## 録音位置の取得
![録音位置の取得](resource/Recorder/pos.png "録音位置の取得")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	Recorder recorder;

	if (!recorder.open(0, 5s))
	{
		return;
	}

	if (!recorder.start())
	{
		return;
	}

	while (System::Update())
	{
		font(L"録音サンプル数: ", recorder.getPosSample()).draw();
	}

	// 録音した音声を保存
	recorder.getWave().save(L"Tutorial-Recorder.wav");
}
```

## 録音をループする
![録音をループする](resource/Recorder/loop.png "録音をループする")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	Recorder recorder;

	// loop を true に設定
	if (!recorder.open(0, 5s, RecordingFormat::S44100, true))
	{
		return;
	}

	if (!recorder.start())
	{
		return;
	}

	while (System::Update())
	{
		font(L"録音サンプル数: ", recorder.getPosSample()).draw();
	}

	// 録音した音声を保存
	recorder.getWave().save(L"Tutorial-Recorder.wav");
}
```

## 録音した波形の解析 | 振幅
![録音した波形の解析 | 振幅](resource/Recorder/amplitude.png "録音した波形の解析 | 振幅")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	Recorder recorder;

	if (!recorder.open(0, 5s, RecordingFormat::S44100, true))
	{
		return;
	}

	if (!recorder.start())
	{
		return;
	}

	while (System::Update())
	{
		const double max = recorder.getMaxAmplitude();
		const double ave = recorder.getAverageAmplitude();

		font(L"最大振幅: ", max).draw();
		RectF(0, 50, max * Window::Width(), 30).draw();

		font(L"平均振幅: ", ave).draw(0, 100);
		RectF(0, 150, ave * Window::Width(), 30).draw();
	}
}
```

## 録音した波形の解析 | FFT
![録音した波形の解析 | FFT](resource/Recorder/fft.gif "録音した波形の解析 | FFT")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1024, 320);

	const Font font(30);

	Recorder recorder;

	if (!recorder.open(0, 5s, RecordingFormat::S44100, true))
	{
		return;
	}

	if (!recorder.start())
	{
		return;
	}

	while (System::Update())
	{
		const auto fft = FFT::Analyze(recorder);

		for (auto i : step(1024))
		{
			RectF(i, Window::Height(), 1, -Pow(fft.buffer[i], 0.5) * 500).draw(HSV(i));
		}

		const int32 mouseX = Mouse::Pos().x;

		Rect(mouseX, 0, 1, Window::Height()).draw();

		font(L"{:.1f}Hz"_fmt, fft.resolution() * mouseX)
			.draw(Mouse::Pos().moveBy(0, -50));
	}
```

[← 前の章へ戻る](Webcam.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Stopwatch.md)