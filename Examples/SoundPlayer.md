# 音楽プレイヤー
![音楽プレイヤー](resource/SoundPlayer/SoundPlayer.gif "音楽プレイヤー") 
```cpp
# include <Siv3D.hpp>

class SoundPlayer
{
private:

	GUI m_gui;

	Sound m_sound;

public:

	SoundPlayer()
		: m_gui(GUIStyle::Default)
	{
		m_gui.add(L"PlayButton", GUIButton::Create(L"Play"));

		m_gui.add(L"PauseButton", GUIButton::Create(L"Pause"));

		m_gui.addln(L"OpenButton", GUIButton::Create(L"Open"));

		m_gui.add(L"Slider", GUISlider::Create(0.0, 1.0, 0.0, 500));

		m_gui.setPos((Window::Width() - m_gui.getRect().w) / 2, 360);
	}

	void update()
	{
		m_gui.button(L"PlayButton").enabled = (m_sound && !m_sound.isPlaying());

		m_gui.button(L"PauseButton").enabled = m_sound.isPlaying();

		if (m_gui.button(L"PlayButton").pushed)
		{
			m_sound.play();
		}
		else if (m_gui.button(L"PauseButton").pushed)
		{
			m_sound.pause();
		}
		else if (m_gui.button(L"OpenButton").pushed)
		{
			m_sound.pause();

			m_sound = Dialog::OpenSound();
		}

		if (m_gui.slider(L"Slider").hasChanged)
		{
			m_sound.setPosSec(m_sound.lengthSec() * m_gui.slider(L"Slider").value);
		}

		m_gui.slider(L"Slider").setValue(m_sound.streamPosSec() / m_sound.lengthSec());
	}

	void drawVisualizer() const
	{
		if (!m_sound.isPlaying())
		{
			return;
		}

		const auto fft = FFT::Analyze(m_sound);

		for (int32 i = 0; i < 640; ++i)
		{
			const double size = Pow(fft.buffer[i], 0.6) * 500;

			RectF(i, 200 + size, 1, -size * 2).draw(HSV(240 - i));
		}
	}
};

void Main()
{
	Graphics::SetBackground(Color(70, 80, 170));

	SoundPlayer soundPlayer;

	while (System::Update())
	{
		soundPlayer.update();

		soundPlayer.drawVisualizer();
	}
}
```
