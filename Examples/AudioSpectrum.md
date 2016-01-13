# オーディオスペクトラム
![オーディオスペクトラム](resource/AudioSpectrum/AudioSpectrum.png "オーディオスペクトラム") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Sound sound = Dialog::OpenSound();

	sound.play();

	while (System::Update())
	{
		const auto fft = FFT::Analyze(sound);

		for (auto i : step(320))
		{
			RectF(i * 2, Window::Height(), 2, -Pow(fft.buffer[i], 0.6) * 1000).draw(HSV(240 - i));
		}
	}
}
```
