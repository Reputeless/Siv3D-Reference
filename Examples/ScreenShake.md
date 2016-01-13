# 画面を揺らす
![画面を揺らす](resource/ScreenShake/ScreenShake.gif "画面を揺らす") 
```cpp
# include <Siv3D.hpp>

class ScreenShake : public IEffect
{
private:

	double m_maxOffset, m_lengthMillisec;

public:

	ScreenShake(double maxOffset, double lengthMillisec)
		: m_maxOffset(maxOffset)
		, m_lengthMillisec(lengthMillisec) {}

	bool update(double timeSec) override
	{
		const double timeMillisec = timeSec * 1000.0;

		const Vec2 offset = RandomVec2(Circle(m_maxOffset * Max(1.0 - timeMillisec / m_lengthMillisec, 0.0)));

		Graphics2D::SetTransform(Mat3x2::Translate(offset));

		return timeMillisec < m_lengthMillisec;
	}
};

void Main()
{
	const Texture texture0(L"Example/Windmill.png");
	const Texture texture1(L"Example/Siv3d-kun.png");
	const Font font(15);
	Effect effect;

	while (System::Update())
	{
		if (effect.num_effects == 0 && Input::MouseL.clicked)
		{
			effect.add<ScreenShake>(16, 600);
		}

		effect.update();

		texture0.draw();
		texture1.draw(300, 0);

		Graphics2D::SetTransform(Mat3x2::Identity());

		RoundRect(40, 380, 560, 80, 3).draw(Color(20, 80, 200, 230));

		if (effect.num_effects != 0)
		{
			font(L"攻撃!").draw(60, 390);
		}
	}
}
```
