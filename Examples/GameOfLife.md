# ライフゲーム
![ライフゲーム](resource/GameOfLife/GameOfLife.png "ライフゲーム") 
```cpp
# include <Siv3D.hpp>

template <class Type>
class CellularAutomaton
{
public:

	using type = Type;

	// 近傍と自身の情報
	struct Neighbors
	{
		Type tl, t, tr, l, c, r, bl, b, br;
	};

	// 自身と近傍の値から、次の世代の値を決める関数
	using RuleFuncType = std::function<Type(const Neighbors&)>;

	// セルの値を色に変換する関数
	using ColorFuncType = std::function<Color(const Type&)>;

	// width:	セルの個数（横）
	// height:	セルの個数（縦）
	// cellsize:	セルの大きさ（ピクセル）
	// rule:	セルの更新のルール
	// colorRule: 色の表現のルール
	CellularAutomaton(
		int32 width,
		int32 height,
		RuleFuncType rule,
		ColorFuncType colorRule
		)
		: m_image(width, height, Palette::Black)
		, m_texture(m_image)
		, m_data((width + 2)*(height + 2))
		, m_tmpData((width + 2)*(height + 2))
		, m_width(width)
		, m_height(height)
		, m_ruleFunction(rule)
		, m_colorFunction(colorRule) {}

	int32 width() const
	{
		return m_width;
	}

	int32 height() const
	{
		return m_height;
	}

	Type getPixel(int32 y, int32 x) const
	{
		return m_data[getStride()*(y + 1) + (x + 1)];
	}

	void setPixel(int32 y, int32 x, Type value)
	{
		m_data[getStride()*(y + 1) + (x + 1)] = value;
	}

	void setRule(RuleFuncType rule)
	{
		m_ruleFunction = rule;
	}

	void setColorRule(ColorFuncType rule)
	{
		m_colorFunction = rule;
	}

	void update()
	{
		// すべてのセルを更新
		for (auto y : step(m_height))
		{
			for (auto x : step(m_width))
			{
				Neighbors n;
				n.tl = getPixel(y - 1, x - 1);
				n.t = getPixel(y - 1, x);
				n.tr = getPixel(y - 1, x + 1);
				n.l = getPixel(y, x - 1);
				n.c = getPixel(y, x);
				n.r = getPixel(y, x + 1);
				n.bl = getPixel(y + 1, x - 1);
				n.b = getPixel(y + 1, x);
				n.br = getPixel(y + 1, x + 1);

				setPixelTemp(y, x, m_ruleFunction(n));
			}
		}

		m_data = m_tmpData;

		// Image を更新
		for (auto y : step(m_height))
		{
			for (auto x : step(m_width))
			{
				m_image[y][x] = m_colorFunction(getPixel(y, x));
			}
		}

		// 動的テクスチャをイメージで更新
		m_texture.fill(m_image);
	}

	const Texture& getTexture()
	{
		return m_texture;
	}

private:

	Image m_image;

	DynamicTexture m_texture;

	Array<Type> m_data, m_tmpData;

	int32 m_width, m_height;

	RuleFuncType m_ruleFunction;

	ColorFuncType m_colorFunction;

	int32 getStride() const
	{
		return m_width + 2;
	}

	void setPixelTemp(int32 y, int32 x, Type value)
	{
		m_tmpData[getStride()*(y + 1) + (x + 1)] = value;
	}
};

using Simulation = CellularAutomaton<int>;

// セルの状態をランダムに 0 か 1 にする
void Reset(Simulation& simulation)
{
	for (auto y : step(simulation.height()))
	{
		for (auto x : step(simulation.width()))
		{
			simulation.setPixel(y, x, Random(1));
		}
	}
}

void Main()
{
	//
	// 誕生: 死んでいるセル (0) の周囲に 3 つの生きているセル (1) があれば次の時間ステップでは生きる (1 になる)。
	// 維持: 生きているセル (1) の周囲に 2 つか 3 つの生きているセル (1) があれば次の世代でも生き残る (1 のままである)。
	// 死亡: 上以外の場合には次の世代では死ぬ (「0」になる)。
	// http://ja.wikipedia.org/wiki/セル・オートマトン より
	//
	const auto Rule = [](const Simulation::Neighbors& n)
	{
		const int32 sum = n.tl + n.t + n.tr + n.l + n.r + n.bl + n.b + n.br;

		if (n.c == 0 && sum == 3)
		{
			return 1;
		}
		else if (n.c == 1 && (sum == 2 || sum == 3))
		{
			return 1;
		}

		return 0;
	};

	// 1 なら緑、0 なら黒
	const auto ColorRule = [](Simulation::type v)
	{
		return v ? Palette::Lime : Palette::Black;
	};

	Simulation simulation{ 160, 120, Rule, ColorRule };

	Reset(simulation);

	Graphics2D::SetSamplerState(SamplerState::ClampPoint);

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			Reset(simulation);
		}

		if (System::FrameCount() % 5 == 0)
		{
			simulation.update();
		}

		simulation.getTexture().scale(4.0).draw();
	}
}
```

# 14 行でライフゲーム
![14 行でライフゲーム](resource/GameOfLife/GameOfLife.png "14 行でライフゲーム") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics2D::SetSamplerState(SamplerState::ClampPoint);
	Image img(128, 96, [](auto) { return Color(Random(1), 0, 0); });
	DynamicTexture tex;

	while (System::Update())
	{
		for (auto b : step(img.size))
		{
			int32 s = 0;
			for (auto d : step({ -1, -1 }, { 3, 3 }))
				s += img.getPixel<ImageAddressMode::Wrap>(b + d).r;

			img[b].b = (s == 3) || (img[b].r && s == 4);
		}

		tex.fill(img.forEach([](Color& p) { p.g = (p.r = p.b) ? 255 : 0; }));

		tex.scale(5).draw();

		System::Sleep(0.1s);
	}
}
```
