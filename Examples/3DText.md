# 3D テキスト
![3D テキスト](resource/3DText/3DText.png "3D テキスト") 
```cpp
# include <Siv3D.hpp>

Image CreateTextImage(const Font& font, const String& str)
{
	Image image(font.region(str).size, Color(255, 0));

	font.overwrite(image, str, { 0, 0 }, Palette::White);

	return image;
}

void DrawTextParticle(const Texture& texture, const Vec3& pos, double scale, const ColorF& color)
{
	const double scaleY = scale;
	const double scaleX = scaleY * (1.0 * texture.width / texture.height);

	Particle particle(pos, { scaleX, scaleY }, color);

	Graphics3D::DrawParticlesForward({ particle }, texture);
}

void Main()
{
	const Font font(48, Typeface::Heavy);
	const Texture textureEarth(L"Example/Earth.jpg", TextureDesc::For3D);
	const Texture textureParticle(L"Example/Particle.png", TextureDesc::For3D);
	const Texture textureTokyo(CreateTextImage(font, L"Tokyo"), TextureDesc::For3D);
	const Texture textureNewYork(CreateTextImage(font, L"New York"), TextureDesc::For3D);
	const Texture textureLondon(CreateTextImage(font, L"London"), TextureDesc::For3D);

	Graphics3D::SetSamplerStateForward(SamplerState::ClampAniso);
	Graphics3D::SetBlendStateForward(BlendState::Additive);
	Graphics3D::SetDepthStateForward(DepthState::None);

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		DrawTextParticle(textureTokyo, { 31, 2, 8 }, 4.0, ColorF(1.0, 0.0, 1.0));

		DrawTextParticle(textureNewYork, { -16, 2, 9 }, 4.0, ColorF(1.0, 1.0, 0.0));

		DrawTextParticle(textureLondon, { 0, 2, 11.5 }, 4.0, ColorF(0.0, 1.0, 1.0));

		Array<Particle> particles;

		particles.emplace_back(Vec3(31, 0, 8), 2.0, ColorF(1.0, 0.0, 1.0));

		particles.emplace_back(Vec3(-16, 0, 9), 2.0, ColorF(1.0, 1.0, 0.0));

		particles.emplace_back(Vec3(0, 0, 11.5), 2.0, ColorF(0.0, 1.0, 1.0));

		Graphics3D::DrawParticlesForward(particles, textureParticle);

		Plane(80, 40).draw(textureEarth);
	}
}
```
