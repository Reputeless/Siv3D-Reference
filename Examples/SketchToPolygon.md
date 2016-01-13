# Sketch to Polygon
![Sketch to Polygon](resource/SketchToPolygon/SketchToPolygon.gif "Sketch to Polygon")  
「スケッチ」と「Image to Polygon」の組み合わせです。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Image image(Window::Size(), Color(0, 0));

	DynamicTexture texture(image);

	Array<Polygon> polygons;

	while (System::Update())
	{
		if (Input::MouseL.pressed)
		{
			const Point from = Input::MouseL.clicked ? Mouse::Pos() : Mouse::PreviousPos();

			Line(from, Mouse::Pos()).overwrite(image, 6, Palette::Green);

			texture.fill(image);
		}
		else if (Input::MouseL.released)
		{
			const Polygon polygon = Imaging::FindExternalContour(image, true);

			if (polygon.num_vertices > 0)
			{
				const Polygon simplePolygon = polygon.simplified(2.0);

				polygons.push_back(simplePolygon);

				image.fill(Color(0, 0));

				texture.fill(image);
			}
		}

		for (const auto& polygon : polygons)
		{
			polygon.draw();

			polygon.drawWireframe(1.0, Palette::Blue);
		}

		texture.draw();
	}
}
```
