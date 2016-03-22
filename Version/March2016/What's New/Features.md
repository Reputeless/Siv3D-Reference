# Siv3D March 2016 おもな新機能サンプル

## パイプサーバー
![パイプサーバー](resource/PipeServer.png "パイプサーバー")  
```cpp

```

## Forward Rendering 時の Viewport 設定
![Forward Rendering 時の Viewport 設定](resource/Viewport.png "Forward Rendering 時の Viewport 設定")  
```cpp

```

## MeshData の形状追加
![MeshData の形状追加](resource/MeshData.png "MeshData の形状追加")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Mesh mesh1(MeshData::Torus(1, 0.3));
	const Mesh mesh2(MeshData::Dodecahedron(1));
	const Mesh mesh3(MeshData::Hemisphere(1));
	const Mesh mesh4(MeshData::Tetrahedron(1));
	const Mesh mesh5(MeshData::Icosahedron(1));
	DynamicMesh mesh6(MeshData::Rock(1, 1));

	Graphics3D::SetAmbientLight(ColorF(0.2));
	const Color color = Palette::Greenyellow;

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		if (Input::MouseR.clicked)
		{
			mesh6.fill(MeshData::Rock(1, Random(100000)));
		}

		Graphics3D::SetRasterizerState(Input::MouseL.pressed ? RasterizerState::WireframeCullNone : RasterizerState::Default3D);

		mesh1.translated(-2.5, 0, 0).draw(color);
		mesh2.translated(0, 0, 0).draw(color);
		mesh3.translated(2.5, 0, 0).draw(color);

		mesh4.translated(-1.25, 0, -2.5).draw(color);
		mesh5.translated(1.25, 0, -2.5).draw(color);

		mesh6.translated(0, 0, -4.5).draw(color);
	}
}
```
