# アーカイブファイル
![アーカイブファイル](resource/ArchiveFile/ArchiveFile.png "アーカイブファイル") 
```cpp
# include <Siv3D.hpp>

void Main()
{
	// アーカイブファイルの作成（作成するときだけコメントアウト）
	// Example ディレクトリの中身を Exampkle.s3a にアーカイブ
	
	//Archive::Create(L"Example", L"Example.s3a");

	FileArchive archive(L"Example.s3a");

	if (!archive)
	{
		MessageBox::Show(L"Example.s3a のロードに失敗しました。");

		return;
	}

	for (const auto& content : archive.contents())
	{
		Println(content);
	}

	const Sound sound(archive.load(L"Example/風の丘.mp3"));

	const Texture texture(archive.load(L"Example/Windmill.png"));

	sound.play();

	while (System::Update())
	{
		texture.draw();
	}
}
```
