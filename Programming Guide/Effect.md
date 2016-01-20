# Effect

`IEffect` を継承したクラスは、`Effect` オブジェクトにエフェクトとして登録できます。  
`IEffect::update(t)` にはエフェクトの経過時間（秒）が引数で与えられるので、これをもとにエフェクトの表現を実装します。  
`IEffect::update()` が `false` を返すか、登録後 10 秒経過すると、該当エフェクトは削除されます。  

## エフェクトの実装サンプル

```cpp
# include <Siv3D.hpp>

struct Snow : IEffect
{
	struct Particle
	{
		Vec2 pos, v0;
	};

	Array<Particle> m_particles;

	Snow(const Point& pos, int32 count)
		: m_particles(count)
	{
		for (auto& particle : m_particles)
		{
			const Vec2 v = Circular(Random(10.0, 80.0), Random(TwoPi));
			particle.pos = pos + v;
			particle.v0 = v * 2.0;
		}
	}

	bool update(double t) override
	{
		for (const auto& particle : m_particles)
		{
			const Vec2 pos = particle.pos + particle.v0 * t + 0.5* t*t * Vec2(0, 320);

			Circle(pos, 1).draw(HSV(pos.y / 4.0, 0.6, 1.0).toColorF(1.0 - t));
		}

		return t < 1.0;
	}
};

struct TextEffect : IEffect
{
	const Font m_font;

	const int32 m_value;

	const Vec2 m_from;

	TextEffect(const Font& font, int value, const Vec2& from)
		: m_font(font)
		, m_value(value)
		, m_from(from) {}

	bool update(double t) override
	{
		if (t >= 1.0)
		{
			return false;
		}

		const double alpha = 1.0 - t;

		const double h = m_value > 80 ? 0.0 : m_value > 50 ? 20.0 : 60.0;

		m_font(m_value).drawCenter(m_from + Vec2(0, -40 * t), HSV(h).toColorF(alpha));

		return true;
	}
};

void Main()
{
	Effect effect;

	const Font font(40, Typeface::Heavy);

	while (System::Update())
	{
		ClearPrint();

		Println(L"マウス右ボタンでスローモーション");

		Println(L"Effects: ", effect.num_effects);

		if (Input::MouseL.clicked)
		{
			effect.add<TextEffect>(font, Random(0, 100), Mouse::Pos());
		}

		const int count = Input::MouseR.pressed ? 10 : 30;

		effect.add<Snow>(Mouse::Pos(), count);

		effect.setSpeed(Input::MouseR.pressed ? 0.333 : 1.0);

		effect.update();
	}
}
```
