# アプリ終了の確認
![アプリ終了の確認](resource/Exit/Exit.png "アプリ終了の確認")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	GUI gui(GUIStyle::Default);
	gui.setTitle(L"タイトル");
	gui.addln(GUIText::Create(L"終了しますか？"));
	gui.add(L"yes", GUIButton::Create(L"はい"));
	gui.add(L"no", GUIButton::Create(L"いいえ"));
	gui.setCenter(Window::Center());
	gui.hide();

	System::SetExitEvent(WindowEvent::Manual);

	while (System::Update())
	{
		if ((System::GetPreviousEvent() & WindowEvent::CloseButton)
			|| (System::GetPreviousEvent() & WindowEvent::EscapeKey))
		{
			gui.show();
		}

		if (gui.button(L"yes").pushed)
		{
			System::Exit();
		}
		else if (gui.button(L"no").pushed)
		{
			gui.hide();
		}
	}
}
```
