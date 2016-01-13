# 3D シーン
![3D シーン](resource/3DScene/3DScene.png "3D シーン")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	std::array<Light, Graphics3D::MaxLight> lights;

	for (auto& light : lights)
	{
		const Vec3 pos{ Random(-40., 40.), 2.0, Random(-40., 40.) };

		light = Light::Point(pos, 6, HSV(Random(360)).toColorF());
	}

	const Texture texture(L"Example/Particle.png", TextureDesc::For3D);

	GUI gui(GUIStyle::Default);
	gui.add(GUIText::Create(L"ライトの数", 100));
	gui.add(L"Slider.Lights", GUISlider::Create(0, 1.0*Graphics3D::MaxLight, 10, 200));
	gui.addln(L"Text.Lights", GUIText::Create(L"10", 40));
	gui.add(GUIText::Create(L"ライトの品質", 100));
	gui.add(L"Quality", GUISlider::Create(1, 100, 100, 200));
	gui.addln(L"Quality", GUIText::Create(L"100", 40));
	gui.add(GUIText::Create(L"アンチエイリアシング"));
	gui.add(L"FXAA", GUIToggleSwitch::Create(L"Off", L"On", true));

	Graphics3D::SetBlendStateForward(BlendState::Additive);
	Graphics3D::SetDepthStateForward(DepthState::TestOnly);

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		if (Input::MouseR.clicked)
		{
			gui.show(!gui.style.visible);
		}

		if (gui.slider(L"Quality").hasChanged)
		{
			const int quality = gui.slider(L"Quality").valueInt;
			gui.text(L"Quality").text = Format(quality);
			Graphics3D::SetLightBufferQuality(quality);
		}

		if (gui.toggleSwitch(L"FXAA").hasChanged)
		{
			Graphics3D::SetAntiAliasing(gui.toggleSwitch(L"FXAA").isRight ? AntiAliasing::Low : AntiAliasing::None);
		}

		const int lightNum = gui.slider(L"Slider.Lights").valueInt;

		gui.text(L"Text.Lights").text = Format(lightNum);

		Array<Particle> particles;

		for (auto i : step(static_cast<int>(Graphics3D::MaxLight)))
		{
			if (i < lightNum)
			{
				Graphics3D::SetLight(i, lights[i]);

				particles.emplace_back(lights[i].position, 0.5, lights[i].diffuse);
			}
			else
			{
				Graphics3D::SetLight(i, Light::None());
			}
		}

		Plane(100).draw();

		for (auto x : step(10))
		{
			Box({ (x - 4) * 7, (x + 1)*0.5, 30 }, { 2, (x + 1), 2 }).draw();
		}

		for (auto x : step(5))
		{
			Cone({ (x - 2) * 15, 0, 15 }, x + 1, x + 1).draw();
		}

		for (auto x : step(5))
		{
			Sphere({ (x - 2) * 15, x + 1, -5 }, x + 1).draw();
		}

		for (auto x : step(10))
		{
			Cylinder({ (x - 4) * 7, (x + 1)*0.5, -20 }, 1.0, x + 1).draw();
		}

		Graphics3D::DrawParticlesForward(particles, texture);
	}
}
```
