# シーン管理

## 基本
![基本](resource/SceneManager/SceneManager1.png "基本") 
```cpp
# include <Siv3D.hpp>
# include <HamFramework.hpp>

struct GameData
{
	int32 t;
};

// シーンのキーの型と、共有データの型を指定
using MyApp = SceneManager<String, GameData>;

struct Title : MyApp::Scene
{
	// クラスの初期化時に一度だけ呼ばれる（省略可）
	void init() override
	{

	}

	// 毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (Input::MouseL.clicked)
		{
			// 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
			changeScene(L"Game", 2000);
		}

		// 共有データにアクセスできる
		m_data->t;
	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{

	}
};

struct Game : MyApp::Scene
{
	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Result", 2000);
	}

	void draw() const override
	{

	}
};

struct Result : MyApp::Scene
{
	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Title", 2000);
	}

	void draw() const override
	{

	}
};

void Main()
{
	MyApp manager(SceneManagerOption::ShowSceneName);

	// SceneManagerOption::ShowSceneName を外せばシーン名のデバッグ表示は消える
	//MyApp manager;

	// フェードイン・アウト時の色
	manager.setFadeColor(Palette::White);

	// シーンを設定
	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");

	// 特に指定しなければ、一番最初に追加したシーンから開始
	// 別のシーンから始めたい場合は init()
	//manager.init(L"Game");

	while (System::Update())
	{
		if (!manager.updateAndDraw())
			break;
	}
}
```

## 応用
![応用](resource/SceneManager/SceneManager2.png "応用") 
```cpp
# include <Siv3D.hpp>
# include <HamFramework.hpp>

struct Spark : IEffect
{
	Array<std::pair<Vec2, Vec2>> m_particles;

	Spark(const Point& pos, const Point& size) : m_particles(50)
	{
		for (auto& particle : m_particles)
		{
			particle.second = Circular(Random(40.0), Random(TwoPi));
			particle.first = pos.movedBy(Random(-size.x / 2, size.x / 2), Random(-size.y / 2, size.y / 2));
		}
	}

	bool update(double t) override
	{
		for (const auto& particle : m_particles)
		{
			const Vec2 pos = particle.first + particle.second * t + 0.5* t*t * Vec2(0, 120);
			Triangle(pos, 8.0, particle.second.x).draw(HSV(pos.y - 40).toColorF(1.0 - t));
		}

		return t < 1.0;
	}
};

struct GameData
{
	int32 currentScore = 0;
	int32 highScore = 0;
};

using MyApp = SceneManager<String, GameData>;

struct Title : MyApp::Scene
{
	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Game");
	}

	void draw() const override
	{
		FontAsset(L"Title")(L"BREAKOUT").drawCenter(100);
	}
};

struct Game : MyApp::Scene
{
	const Sound m_sound{ L"Example/Sound.mp3" };
	const Point m_blockSize{ 40, 20 };
	const double m_speed{ 8.0 };
	Rect m_wall{ 60, 10 };
	Circle m_ball{ 320, 400, 8 };
	Vec2 m_ballSpeed{ 0, -m_speed };
	Array<Rect> m_blocks;
	Effect m_effect;
	bool m_gameOver = false;

	void init() override
	{
		m_data->currentScore = 0;

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < Window::Width() / m_blockSize.x; ++x)
			{
				m_blocks.emplace_back(x*m_blockSize.x, 60 + y*m_blockSize.y, m_blockSize);
			}
		}
	}

	void updateFadeIn(double) override
	{
		m_wall.setCenter(Mouse::Pos().x, 420);
	}

	void update() override
	{
		m_ball.moveBy(m_ballSpeed);
		m_wall.setCenter(Mouse::Pos().x, 420);

		for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it)
		{
			if (it->intersects(m_ball))
			{
				(it->bottom.intersects(m_ball) || it->top.intersects(m_ball)
					? m_ballSpeed.y : m_ballSpeed.x) *= -1;

				++m_data->currentScore;
				m_sound.playMulti();
				m_effect.add<Spark>(it->center, m_blockSize);
				m_blocks.erase(it);
				break;
			}
		}

		if (m_ball.y<0 && m_ballSpeed.y<0)
		{
			m_ballSpeed.y *= -1;
		}

		if ((m_ball.x < 0 && m_ballSpeed.x < 0) || (Window::Width() < m_ball.x && m_ballSpeed.x > 0))
		{
			m_ballSpeed.x *= -1;
		}

		if (m_ballSpeed.y>0 && m_wall.intersects(m_ball))
		{
			m_ballSpeed = Vec2((m_ball.x - m_wall.center.x) / 8, -m_ballSpeed.y).normalized()*m_speed;
		}

		if (m_blocks.empty() || m_ball.y > Window::Height())
		{
			for (auto const& block : m_blocks)
			{
				m_effect.add<Spark>(block.center, m_blockSize);
			}

			m_effect.setSpeed(0.3);
			changeScene(L"Result", 4000);
			m_gameOver = true;
		}
	}

	void draw() const override
	{
		if (!m_gameOver)
		{
			for (auto const& block : m_blocks)
			{
				block.stretched(-1).draw(HSV(block.y - 40));
			}
		}

		m_ball.draw();
		m_wall.draw();
		m_effect.update();
	}
};

struct Result : MyApp::Scene
{
	void init() override
	{
		m_data->highScore = Max(m_data->highScore, m_data->currentScore);
	}

	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Title");
	}

	void draw() const override
	{
		FontAsset(L"Score")(L"Score: ", m_data->currentScore).draw(100, 100);
		FontAsset(L"Score")(L"High score: ", m_data->highScore).draw(100, 160);
	}
};

void Main()
{
	FontAsset::Register(L"Title", 60);
	FontAsset::Register(L"Score", 40);

	MyApp manager;
	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");

	while (System::Update())
	{
		if (!manager.updateAndDraw())
			break;
	}
}
```
