# リンクテキスト
![リンクテキスト](resource/LinkText/LinkText.gif "リンクテキスト")  
クリックすると Web ページを開くテキストです。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);
	const String url = L"http://play-siv3d.hateblo.jp/";
	const Font font(14, Typeface::Regular);
	const Point pos(50, 50);
	const Rect region = font(url).region(pos);
	const Color textColor(0, 90, 180);

	while (System::Update())
	{
		font(url).draw(pos, textColor);

		if (region.mouseOver)
		{
			Cursor::SetStyle(CursorStyle::Hand);

			region.bottom.draw(1.5, textColor);

			if (Input::MouseL.clicked)
			{
				Internet::LaunchWebBrowser(url);
			}
		}
		else
		{
			Cursor::SetStyle(CursorStyle::Default);
		}
	}
}
```
