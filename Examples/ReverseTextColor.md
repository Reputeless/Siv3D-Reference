# 文字色の反転
![文字色の反転](resource/ReverseTextColor/ReverseTextColor.gif "文字色の反転") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(70, Typeface::Light);

	const Color color(40, 120, 220);

	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		const Circle circle(Mouse::Pos(), 80);

		Graphics2D::SetStencilState(StencilState::None);

		circle.draw(color);

		Graphics2D::SetStencilValue(1);

		Graphics2D::SetStencilState(StencilState::Replace);

		circle.draw();

		Graphics2D::SetStencilState(StencilState::Test(StencilFunc::NotEqual));

		font(L"Siv3D Engine").drawCenter(160, color);

		Graphics2D::SetStencilState(StencilState::Test(StencilFunc::Equal));

		font(L"Siv3D Engine").drawCenter(160, Palette::White);
	}
}
```
