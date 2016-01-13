# マイク入力スペクトラム
![マイク入力スペクトラム](resource/RecorderSpectrum/RecorderSpectrum.gif "マイク入力スペクトラム") 
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

		font(L"{:.1f}Hz"_fmt, fft.resolution() * mouseX).draw(Mouse::Pos().moveBy(0, -50));
	}
}
```
