# 15. アプリの状態

## 今何フレーム目かを取得する
`System::FrameCount()` は `System::Update()` が呼ばれた回数を返します。
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font(System::FrameCount(), L"フレーム目").draw();
	}
}
```

## カーソルの表示 / 非表示

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::KeyH.clicked)
		{
			Cursor::SetStyle(CursorStyle::None);
		}

		if (Input::KeyS.clicked)
		{
			Cursor::SetStyle(CursorStyle::Default);
		}

		Circle(Mouse::Pos(), 20).draw();
	}
}
```

## プログラムからアプリを終了する
`System::Exit()` を呼ぶと、次の `System::Update()` が false を返し、メインループが終了します。  
`System::Exit()` はエンジンに終了を通知するだけの関数であり、使用は必須ではありません。
```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			// 次の System::Update() が false を返す
			System::Exit();
		}
	}
}
```

## 終了イベントを設定
アプリケーションを終了する条件を設定できます。
```cpp
# include <Siv3D.hpp>

void Main()
{
	// エスケープキーか右クリックか System::Exit() で終了
	System::SetExitEvent(WindowEvent::EscapeKey | WindowEvent::RightClick);

	while (System::Update())
	{
		if (Input::KeySpace.clicked)
		{
			System::Exit();
		}
	}
}
```

## フレームレート

```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font(Profiler::FPS(), L"fps").draw();
	}
}
```

## Sleep
処理を中断する時間を指定します。
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	// 2.34 秒スリープ
	System::Sleep(2.34s);

	while (System::Update())
	{
		Circle(Mouse::Pos(), 100).draw();
	}
}
```

[← 前の章へ戻る](Dragdrop.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Text.md)