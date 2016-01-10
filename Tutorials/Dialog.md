# 13. ダイアログ

## 色を選択する

```cpp
# include <Siv3D.hpp>

void Main()
{
	Color color = Palette::White;

	Graphics::SetBackground(color);

	while (System::Update())
	{
		if (Input::KeyC.clicked)
		{
			// カラーダイアログを開いて、色を選択させる
			// キャンセルされた場合は引数の color を返す
			color = Dialog::GetColor(color);

			Graphics::SetBackground(color);
		}
	}
}
```

## テクスチャを開く

```cpp
# include <Siv3D.hpp>

void Main()
{
	// ダイアログで選択した画像ファイルからテクスチャを作成する
	const Texture texture = Dialog::OpenTexture();

	while (System::Update())
	{
		texture.draw();
	}
}
```

## サウンドを開く

```cpp
# include <Siv3D.hpp>

void Main()
{
	// ダイアログで選択した音楽ファイルからサウンドを作成する
	const Sound sound = Dialog::OpenSound();

	sound.play();

	while (System::Update())
	{

	}
}
```

## オープンする画像ファイルのパスを取得する

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::KeyO.clicked)
		{
			// ダイアログで画像ファイルが選択されたら
			if (const auto open = Dialog::GetOpenImage())
			{
				// ファイルのパス
				Println(open.value());
			}
		}
	}
}
```

## 名前を付けて画像を保存する

```cpp
# include <Siv3D.hpp>

void Main()
{
	// 青で塗りつぶしたイメージを作成
	const Image image(100, 100, Palette::Blue);

	while (System::Update())
	{
		if (Input::KeyS.clicked)
		{
			// ダイアログで保存するファイル名が入力されたら
			if (const auto save = Dialog::GetSaveImage())
			{
				// ファイルパス
				const FilePath filepath = save.value();

				// 指定したファイルパスに画像を保存
				image.save(filepath);
			}
		}
	}
}
```

## ファイルダイアログに表示するファイルの拡張子をカスタマイズする

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::Key1.clicked)
		{
			// txt, ini, csv
			if (const auto open = Dialog::GetOpen({ ExtensionFilter::Text, ExtensionFilter::INI, ExtensionFilter::CSV }))
			{
				Println(open.value());
			}
		}

		if (Input::Key2.clicked)
		{
			// html/htm
			if (const auto open = Dialog::GetOpen({ { L"HTML ファイル (*.html;*.htm)", L"*.html;*.htm" } }))
			{
				Println(open.value());
			}
		}

		if (Input::Key3.clicked)
		{
			// 独自の拡張子 .aaa
			if (const auto open = Dialog::GetOpen({ { L"説明 (*.aaa)", L"*.aaa" } }))
			{
				Println(open.value());
			}
		}
	}
}
```

## フォルダを選択する

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::KeyF.clicked)
		{
			// ダイアログでフォルダが選択されたら
			if (const auto folder = Dialog::GetFolder())
			{
				// フォルダ名
				Println(folder.value());
			}
		}
	}
}
```

## フォントを選択する

```cpp
# include <Siv3D.hpp>

void Main()
{
	// 選択されなかった場合のデフォルトのフォントを Meiryo, 16 にする
	const FontProperty fontProperty = Dialog::GetFont(FontProperty(L"Meiryo", 16));

	const Font font(fontProperty.size, fontProperty.name, fontProperty.style);

	while (System::Update())
	{
		font(L"Siv3D Engine").draw();
	}
}
```

[← 前の章へ戻る](Random.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Dragdrop.md)