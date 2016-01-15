# Siv3D January 2016 おもな新機能サンプル (随時追加予定）

## ベジェ曲線
![ベジェ曲線](resource/Bezier.gif "ベジェ曲線")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Window::SetPos(770, 383);

	const double speed = 2.0;
	Rect rectA(100, 100, 100), rectB(300, 200, 100);
	bool grabbedA = false, grabbedB = false;
	CubicBezier bezier(Vec2(100, 400), Vec2(200, 400), Vec2(200, 100), Vec2(300, 100));
	CubicBezierPath path(bezier);

	while (System::Update())
	{
		if (rectA.leftClicked)
		{
			grabbedA = true;
		}
		else if (rectB.leftClicked)
		{
			grabbedB = true;
		}

		if (grabbedA)
		{
			rectA.moveBy(Mouse::Delta());
		}
		else if (grabbedB)
		{
			rectB.moveBy(Mouse::Delta());
		}

		if (Input::MouseL.released)
		{
			grabbedA = grabbedB = false;
		}

		bezier.p0 = (rectA.center.x < rectB.center.x ? (rectA.tr + rectA.br) : (rectA.tl + rectA.bl)) / 2;
		bezier.p3 = (rectB.center.x < rectA.center.x ? (rectB.tr + rectB.br) : (rectB.tl + rectB.bl)) / 2;
		bezier.p1.set(bezier.p3.x, bezier.p0.y);
		bezier.p2.set(bezier.p0.x, bezier.p3.y);
		path.set(bezier);

		double r = path.advance(speed, 40);

		if (r >= 1.0 || IsNaN(r))
		{
			path.set(r = 0.0);
		}

		bezier.draw(2);

		RoundRect(rectA, 4).draw(Palette::Deepskyblue);
		RoundRect(rectB, 4).draw(Palette::Deepskyblue);
		
		Circle(bezier.p0, 6).draw(Color(160, 200, 255, 200));
		Circle(bezier.p3, 6).draw(Color(160, 200, 255, 200));

		Circle(bezier.getPos(r), 10).draw(Palette::Orange);
	}
}
```

## 手書き文字認識
![手書き文字認識](resource/Handwriting.gif "手書き文字認識") 
```cpp
# include <Siv3D.hpp>

void Main()
{
    const HandwritingRecognizer recognizer(L"Example/Hiragana.model");
    const Font font(34);

    Image image(400, 400, Palette::White);

    DynamicTexture texture(image);

    Array<Array<Point>> pointsList;

    while (System::Update())
    {
        texture.draw();

        if (Input::MouseL.pressed)
        {
            if (Input::MouseL.clicked)
            {
                pointsList.emplace_back();
            }

            pointsList.back().push_back(Mouse::Pos());

            const Point from = Input::MouseL.clicked ? Mouse::Pos() : Mouse::PreviousPos();

            Line(from, Mouse::Pos()).overwrite(image, 8, Palette::Blue);

            texture.fill(image);
        }

        if (Input::MouseR.clicked)
        {
            pointsList.clear();

            image.fill(Palette::White);

            texture.fill(image);
        }

        const auto results = recognizer.recognize(image.size, pointsList);

        for (auto i : step(int(results.size())))
        {
            const String text = results[i].character;

            const double score = results[i].score;

            const Rect rect(440, 20 + i * 70, 120, 60);

            rect.draw(HSV(40, 1.0, Saturate(score + 1.0)));

            font(text).drawCenter(rect.center, Palette::Black);
        }
    }
}
```

## Mesh 描画時のカスタムシェーダ
![Mesh 描画時のカスタムシェーダ](resource/Terrain.png "Mesh 描画時のカスタムシェーダ") 
```cpp
# include <Siv3D.hpp>

void Main()
{
    Window::Resize(1280, 720);
    Graphics::SetBackground(Color(40, 150, 255));
    Graphics3D::SetAmbientLight(ColorF(0.2, 0.3, 0.4));
    Graphics3D::SetFog(Fog::SquaredExponential(Color(40, 150, 255), 0.002));

    const VertexShader vsTerrain(L"Example/Shaders/Terrain3D.hlsl");
    const PixelShader psTerrain(L"Example/Shaders/Terrain3D.hlsl");
    if (!vsTerrain || !psTerrain)
    {
        return;
    }

    const Texture textureGround(L"Example/grass.jpg", TextureDesc::For3D);
    const Mesh terrainBase(MeshData::TerrainBase(160));
    RenderTexture heightMap{ 512, 512, ColorF(0), TextureFormat::R32_Float };

    const Texture texture(Image(64, 64, [](Point p)
    {
        return ColorF(Pow(1 - Vec2(p).distanceFrom(Vec2(32, 32)) / (32 * 1.4142), 4));
    }));

    while (System::Update())
    {
        Graphics3D::FreeCamera();

        if ((Input::MouseL | Input::MouseR).pressed)
        {
            Graphics2D::SetRenderTarget(heightMap);
            Graphics2D::SetBlendState(Input::MouseL.pressed ? BlendState::Additive : BlendState::Subtractive);

            texture.scale(2.5).drawAt(Mouse::Pos() - Point(1280 - 512 - 10, 10), ColorF(0.2));

            Graphics2D::SetBlendState(BlendState::Default);
            Graphics2D::SetRenderTarget(Graphics::GetSwapChainTexture());
        }

        Graphics3D::BeginVS(vsTerrain);
        Graphics3D::BeginPS(psTerrain);
        Graphics3D::SetTexture(ShaderStage::Vertex, 0, heightMap);
        Graphics3D::SetSamplerState(ShaderStage::Vertex, 0, SamplerState::ClampLinear);

        terrainBase.draw(textureGround);

        Graphics3D::SetTexture(ShaderStage::Vertex, 0, none);
        Graphics3D::EndPS();
        Graphics3D::EndVS();

        heightMap.draw(1280 - 512 - 10, 10, ColorF(0.3, 0.9));
    }
}
```
