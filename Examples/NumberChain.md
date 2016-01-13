# 数つなぎ
![数つなぎ](resource/NumberChain/NumberChain.png "数つなぎ") 
```cpp
# include <Siv3D.hpp>

const double circleR = 30;

struct Ripple : IEffect
{
	Vec2 m_pos;

	Ripple(const Vec2& pos) : m_pos(pos) {}

	bool update(double t) override
	{
		Circle(m_pos, circleR + t * 200).drawFrame(2, 0, ColorF(0.2, 0.5, 1.0, 1.0 - t*2.5));
		return t < 0.4;
	}
};

struct Bubble
{
	Circle circle;
	int32 number;
	bool hasRing = false;

	void draw() const
	{
		circle.draw();

		if (hasRing)
		{
			circle.drawFrame(2, 0, Color(60, 160, 250));
		}

		FontAsset(L"bubble")(number + 1).drawCenter(circle.center, Color(10));
	}
};

bool CheckBubbles(const Array<Bubble>& bubbles)
{
	for (auto i : step(bubbles.size()))
	{
		for (auto k : step(bubbles.size()))
		{
			if (i != k && bubbles[i].circle.stretched(5).intersects(bubbles[k].circle.stretched(5)))
			{
				return false;
			}
		}
	}

	return true;
}

Array<Bubble> MakeBubbles(int count)
{
	Array<Bubble> bubbles(count);

	do
	{
		for (auto i : step(count))
		{
			bubbles[i].number = i;
			bubbles[i].circle.set(RandomVec2(Circle(Window::Center(), Window::Width() / 2 - circleR)), circleR);
		}
	} while (!CheckBubbles(bubbles));

	return bubbles;
}

void Main()
{
	Graphics::SetBackground(Palette::White);
	Window::Resize(720, 720);
	FontAsset::Register(L"bubble", 20, Typeface::Light);

	int32 highScore = 0;
	int32 stage = 1;
	int32 targetBubble = 1;
	int32 targetTime = 8000;
	int32 currentBubble = 0;
	Array<Bubble> bubbles = MakeBubbles(targetBubble);

	const Array<uint8> midis{ 72, 74, 76, 77, 79, 81, 83, 84, 86, 88, 89, 91, 93, 95, 96 };
	Midi::SendMessage(MidiMessage::SetInstrument(0, GMInstrument::Glockenspiel));

	Effect effect;
	Stopwatch stopwatch(true);

	while (System::Update())
	{
		RectF(Window::Width(), static_cast<double>(Window::Height()) * stopwatch.ms() / targetTime).draw(HSV(stage * 30, 0.2, 1.0));

		for (auto& bubble : bubbles)
		{
			if (bubble.number == currentBubble && !bubble.hasRing && bubble.circle.stretched(10).mouseOver)
			{
				bubble.hasRing = true;
				++currentBubble;
				effect.add<Ripple>(bubble.circle.center);
				Midi::SendMessage(MidiMessage::NoteOn(0, midis[bubble.number]));
			}

			Circular c = Circular(bubble.circle.center.movedBy(-Window::Center()));
			c.theta += bubble.number % 2 ? 0.002 : -0.002;
			bubble.circle.setPos(Vec2(c).movedBy(Window::Center()));
		}

		for (int i = 0; i < currentBubble - 1; ++i)
		{
			Line(bubbles[i].circle.center, bubbles[i + 1].circle.center).draw(2.0, Palette::Orange);
		}

		const bool failed = stopwatch.ms() > targetTime;

		if (currentBubble == targetBubble || failed)
		{
			stage = failed ? 1 : ++stage;
			highScore = Max(highScore, stage);
			
			Window::SetTitle(L"Stage {} (High score: {})"_fmt, stage, highScore);

			currentBubble = 0;
			targetBubble = Min(stage, 15);
			bubbles = MakeBubbles(targetBubble);
			targetTime = stage <= 15 ? 8000 : 8000 - Min((stage - 15) * 50, 2000);
			stopwatch.restart();
		}

		for (const auto& bubble : bubbles)
		{
			bubble.draw();
		}

		effect.update();
	}
}
```
