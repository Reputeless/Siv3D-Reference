# Plot3D
![Plot3D](resource/Plot3D/Plot3D.png "Plot3D") 
```cpp
# include <Siv3D.hpp>

void Plot3D(const ParsedExpression& f, MeshData& meshData)
{
	for (auto& v : meshData.vertices)
	{
		v.position.y = static_cast<float>(f.evaluateOpt({
				{ L"x", v.position.x }, { L"y", v.position.z } }).value_or(0.0));
	}

	meshData.computeNormals();
}

void Main()
{
	Graphics::SetBackground(Color(120, 180, 160));

	const String defaultExpression = L"5 * sin(sqrt(x^2+y^2)+0.0001) / (sqrt(x^2+y^2)+0.0001)";
	MeshData meshData = MeshData::Grid(25, 100);
	Plot3D(ParsedExpression(defaultExpression), meshData);
	DynamicMesh mesh(meshData);

	GUI gui(GUIStyle::Default);
	gui.addln(L"exp", GUITextArea::Create(2, 32));
	gui.add(L"grid", GUIToggleSwitch::Create(L"グリッド非表示", L"グリッド表示", false));
	gui.textArea(L"exp").setText(defaultExpression);

	while (System::Update())
	{
		if (!gui.textArea(L"exp").active)
		{
			Graphics3D::FreeCamera();
		}

		if (gui.textArea(L"exp").hasChanged)
		{
			if (const ParsedExpression exp{ gui.textArea(L"exp").text })
			{
				gui.textArea(L"exp").style.color = Palette::Black;
				Plot3D(exp, meshData);
				mesh.fillVertices(meshData.vertices);
			}
			else
			{
				gui.textArea(L"exp").style.color = Palette::Red;
			}
		}

		if (mesh)
		{
			if (gui.toggleSwitch(L"grid").isRight)
			{
				RasterizerState raster = RasterizerState::WireframeCullBack;
				raster.depthBias = 10000;
				Graphics3D::SetRasterizerState(raster);

				mesh.draw(Palette::Black);

				Graphics3D::SetRasterizerState(RasterizerState::Default3D);
			}

			mesh.draw();
		}
	}
}
```
