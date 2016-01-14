# Siv3D January 2016 おもな新機能サンプル (随時追加予定）

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

