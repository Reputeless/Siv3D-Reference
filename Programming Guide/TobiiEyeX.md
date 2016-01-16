# TobiiEyeX
視線計測デバイス Tobii EyeX を扱います。

## Tobii EyeX から視線情報を取得する

```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!TobiiEyeX::Start())
	{
		return;
	}

	EyeXState state;

	Vec2 pos(0, 0);

	while (System::Update())
	{
		if (TobiiEyeX::HasNewState())
		{
			TobiiEyeX::GetState(state);

			pos = state.clientGazePos;
		}

		Circle(pos, 20).draw();
	}
}
```
