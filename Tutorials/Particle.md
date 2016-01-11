# 30. パーティクル

## 3D パーティクル
![3D パーティクル](resource/Particle/particle.png "3D パーティクル")  
3D パーティクルは常にカメラのほうを向いて描画されます。  
`Graphics3D::DrawParticlesForward()` は `Array<Particle>` で定義されたパーティクルを Forward Rendering で描画します。  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const int32 w = 80, h = 80;

	Array<Particle> particles(w * h);

	for (int32 y = 0; y < h; ++y)
	{
		for (int32 x = 0; x < w; ++x)
		{
			const Vec3 pos(x - w / 2, Random(10.0), y - h / 2);

			const ColorF color = HSV(pos.y * 20.0);

			particles[y * w + x] = Particle(pos, 0.5, color);
		}
	}

	const Texture texture(L"Example/Particle.png", TextureDesc::For3D);

	Graphics3D::SetBlendStateForward(BlendState::Additive);
	Graphics3D::SetDepthStateForward(DepthState::TestOnly);

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		Graphics3D::DrawParticlesForward(particles, texture);
	}
}
```

## 3D パーティクルのアニメーション
![3D パーティクルのアニメーション](resource/Particle/animation.png "3D パーティクルのアニメーション")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(20, 40, 60));
	Graphics3D::SetLight(0, Light::None());

	const Texture textureGrass(L"Example/Grass.jpg", TextureDesc::For3D);

	Array<Particle> particles(400);

	for (auto& particle : particles)
	{
		const Vec3 pos = RandomVec3({ -20, 20 }, { -0.2, 4 }, { -20, 20 });

		particle = Particle(pos, 0.2, ColorF(1.0, 0.6, 0.0));
	}

	const Texture texture(L"Example/Particle.png", TextureDesc::For3D);

	Graphics3D::SetBlendStateForward(BlendState::Additive);
	Graphics3D::SetDepthStateForward(DepthState::TestOnly);

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		for (auto& particle : particles)
		{
			particle.pos.y += 0.01f;

			if (4.0 < particle.pos.y)
			{
				particle.pos.y -= 4.2f;
			}

			const float s = 1.0f - (Abs(2.0f - particle.pos.y) / 2.0f);
			particle.scaling.x = particle.scaling.y = 0.2f * s;
			particle.color.w = s;
		}

		Plane(40).draw(textureGrass);

		Graphics3D::DrawParticlesForward(particles, texture);
	}
}
```

[← 前の章へ戻る](Graphics3D.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Screen-capture.md)