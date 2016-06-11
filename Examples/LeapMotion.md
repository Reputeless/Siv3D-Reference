# Leap Motion

## 基本
![基本](resource/LeapMotion/LeapMotion1.gif "基本")  
コンパイル・実行のために以下の手順が必要です。
- プロジェクトのプロパティ [VC++ ディレクトリ] で、Leap Motion SDK の include ディレクトリと、プロジェクトのターゲットプラットフォームに合わせて lib/x86 または lib/x64 ディレクトリへのパスを設定する
- 実行ファイルのカレントディレクトリに Leap.dll を配置する

```cpp
# include <Siv3D.hpp>
# include <Siv3DAddon/LeapMotion.hpp>

void Main()
{
	Window::Resize(1024, 640);

	LeapMotion::RegisterAddon();

	const Font font(36), font2(18);

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		for (const auto& hand : LeapMotion::Hands())
		{
			const Vec3 scaledPos = hand.pos*0.05;

			Sphere(scaledPos, 0.5).draw(HSV(hand.id * 30).toColor());

			const Vec2 screenBase = Graphics3D::ToScreenPos(scaledPos).xy();

			font(hand.isLeft ? L"Left" : L"Right").drawCenter(screenBase.movedBy(20, -160));

			const Circle pinchCircle(screenBase.movedBy(-60, -260), 60);

			const Circle grabCircle(screenBase.movedBy(100, -260), 60);

			pinchCircle.draw(HSV(hand.id * 30).toColor(60));

			pinchCircle.drawPie(0.0, hand.pinchStrength * TwoPi, HSV(hand.id * 30));

			grabCircle.draw(HSV(hand.id * 30).toColor(60));

			grabCircle.drawPie(0.0, hand.grabStrength * TwoPi, HSV(hand.id * 30));

			font2(L"Pinch").drawCenter(pinchCircle.center);

			font2(L"Grab").drawCenter(grabCircle.center);

			for (const auto& finger : hand.fingers)
			{
				for (const auto& joint : finger.joints)
				{
					Sphere(joint*0.05, 0.2).draw(HSV(finger.id * 10).toColor());
				}
			}
		}

		Box(1).draw();
	}
}
```

## 骨格を表示
![骨格を表示](resource/LeapMotion/LeapMotion2.png "骨格を表示")  
```cpp
# include <Siv3D.hpp>
# include <Siv3DAddon/LeapMotion.hpp>

void Main()
{
	Window::Resize(1024, 640);

	LeapMotion::RegisterAddon();

	const Font font(36), font2(18);

	while (System::Update())
	{
		Graphics3D::FreeCamera();

		for (const auto& hand : LeapMotion::Hands())
		{
			const Vec3 scaledPos = hand.pos*0.05;

			Sphere(scaledPos, 0.5).draw(HSV(hand.id * 30).toColor());

			const Vec2 screenBase = Graphics3D::ToScreenPos(scaledPos).xy();

			font(hand.isLeft ? L"Left" : L"Right").drawCenter(screenBase.movedBy(20, -160));

			const Circle pinchCircle(screenBase.movedBy(-60, -260), 60);

			const Circle grabCircle(screenBase.movedBy(100, -260), 60);

			pinchCircle.draw(HSV(hand.id * 30).toColor(60));

			pinchCircle.drawPie(0.0, hand.pinchStrength * TwoPi, HSV(hand.id * 30));

			grabCircle.draw(HSV(hand.id * 30).toColor(60));

			grabCircle.drawPie(0.0, hand.grabStrength * TwoPi, HSV(hand.id * 30));

			font2(L"Pinch").drawCenter(pinchCircle.center);

			font2(L"Grab").drawCenter(grabCircle.center);

			for (const auto& finger : hand.fingers)
			{
				for (const auto& joint : finger.joints)
				{
					Sphere(joint*0.05, 0.2).draw(HSV(finger.id * 10).toColor());
				}

				const int32 begin = (finger.type == LeapMotion::FingerType::Thumb)
					|| (finger.type == LeapMotion::FingerType::Pinky) ? 0 : 1;

				for (int32 i = begin; i < 4; ++i)
				{
					Cylinder(finger.joints[i] * 0.05, finger.joints[i + 1] * 0.05, 0.1).draw();
				}
			}

			for (auto i : step(Min(4, static_cast<int32>(hand.fingers.size()))))
			{
				Cylinder(hand.fingers[i].joints[1] * 0.05, hand.fingers[i + 1].joints[1] * 0.05, 0.1).draw();
			}

			Cylinder(hand.fingers[0].joints[0] * 0.05, hand.fingers[hand.fingers.size() - 1].joints[0] * 0.05, 0.1).draw();
		}

		Box(1).draw();
	}
}
```
