# シーン切り替え(シルエット)
![シーン切り替え(シルエット)](resource/SceneChangeSilhouette/SceneChangeSilhouette.png "シーン切り替え(シルエット)") 
```cpp
# include <Siv3D.hpp>
# include <HamFramework.hpp>

using MyApp = SceneManager<String>;

void Fade(double t, bool in)
{
	if (t > 0.75)
	{
		Window::ClientRect().draw(ColorF(0.0));
		return;
	}

	t *= (1 / 0.75);

	Graphics2D::SetStencilState(StencilState::Replace);
	Graphics2D::SetStencilValue(1);

	TextureAsset(L"siv3d-kun")
		.scale(4 * EaseIn(Easing::Quad, 1 - t))
		.rotate((in ? (1.0 - t) : t) * 10)
		.drawAt(Window::Center());

	Graphics2D::SetStencilState(StencilState::Test(StencilFunc::NotEqual));
	Window::ClientRect().draw(ColorF(0.0, t * 4.0));
	Graphics2D::SetStencilState(StencilState::Default);
}

void FadeIn(double t)
{
	Fade(1.0 - t, true);
}

void FadeOut(double t)
{
	Fade(t, false);
}

struct Title : MyApp::Scene
{
	void init() override
	{
		Graphics::SetBackground(Palette::Seagreen);
	}

	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Game1", 3500);
	}

	void draw() const override {}

	void drawFadeOut(double t) const override
	{
		FadeOut(t);
	}
};

struct Game1 : MyApp::Scene
{
	void init() override
	{
		Graphics::SetBackground(Palette::Skyblue);
	}

	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Game2", 3500);
	}

	void draw() const override
	{
		for (auto p : step({ 8, 6 }))
		{
			Circle(p * 80 + Point(40, 40), 20).draw(HSV(0, 1.0 - p.y / 5.0, 1.0));
		}
	}

	void drawFadeIn(double t) const override
	{
		draw();
		FadeIn(t);
	}

	void drawFadeOut(double t) const override
	{
		draw();
		FadeOut(t);
	}
};

struct Game2 : MyApp::Scene
{
	void init() override
	{
		Graphics::SetBackground(Palette::Orange);
	}

	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Game1", 3500);
	}

	void draw() const override
	{
		for (auto p : step({ 8, 6 }))
		{
			Rect(40).setCenter(p * 80 + Point(40, 40)).draw(HSV(180, 1.0 - p.y / 5.0, 1.0));
		}
	}

	void drawFadeIn(double t) const override
	{
		draw();
		FadeIn(t);
	}

	void drawFadeOut(double t) const override
	{
		draw();
		FadeOut(t);
	}
};

void Main()
{
	TextureAsset::Register(L"siv3d-kun", L"Example/siv3d-kun.png");

	MyApp manager;
	manager.add<Title>(L"Title");
	manager.add<Game1>(L"Game1");
	manager.add<Game2>(L"Game2");

	while (System::Update())
	{
		if (!manager.updateAndDraw())
			break;
	}
}
```
