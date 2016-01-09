# Addon

`IAddon` を継承したクラスは、Siv3D エンジンにアドオンとして登録できます。  
アドオンとして登録されたクラスは `System::Update()` のたびに自動的に `update()` が呼ばれるようになり、ユーザが更新用の関数を呼ぶ手間を省けます。  
`LeapMotion Addon` はアドオンの仕組みを利用して実装されています。

### アドオンの使用例

```cpp
# include <Siv3D.hpp>

class FPS_On_Title : public IAddon
{
private:

	String m_baseTitle;

	String m_previousTitle;

public:

	static const String name()
	{
		return String(L"FPS_On_Title");
	}

	String getName() const override
	{
		return name();
	}

	bool init() override
	{
		m_previousTitle = m_baseTitle = Window::GetTitle();
		
		return true;
	}

	bool update() override
	{
		const String currentTitle = Window::GetTitle();

		if (currentTitle != m_previousTitle)
		{
			m_baseTitle = currentTitle;
		}

		m_previousTitle = Format(L"{} ({}FPS)"_fmt, m_baseTitle, Profiler::FPS());

		Window::SetTitle(m_previousTitle);

		return true;
	}
};

void Main()
{
	Println(Addon::IsRegistered<FPS_On_Title>());

	Addon::Register<FPS_On_Title>();

	Println(Addon::IsRegistered<FPS_On_Title>());

	while (System::Update())
	{
		if (Input::MouseL.clicked)
		{
			Window::SetTitle(L"My App");
		}

		if (Input::MouseR.clicked)
		{
			Window::SetTitle(L"My Game");
		}

		if (Input::KeyU.clicked)
		{
			Addon::Unregister<FPS_On_Title>();

			Window::SetTitle(L"My Work");

			Println(Addon::IsRegistered<FPS_On_Title>());
		}
	}
}
```
