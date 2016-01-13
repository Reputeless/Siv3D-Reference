# 3D 交差判定
![3D 交差判定](resource/Intersection3D/Intersection3D.png "3D 交差判定")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Array<Box> boxes;

	for (auto i : step(50))
	{
		boxes.emplace_back(RandomVec3({ -20, 20 }, { -20, 20 }, { -20, 20 }), 3.0);

		boxes[i].rotation.rotateRollPitchYaw(Random(Pi), Random(Pi), Random(Pi));
	}

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		for (auto& box : boxes)
		{
			box.rotation.rotateRollPitchYaw(0.01, 0.01, 0.01);
		}

		for (const auto& box : boxes)
		{
			box.draw(box.intersects(Mouse::Ray()) ? Palette::Yellow : Palette::White);
		}
	}
}
```
