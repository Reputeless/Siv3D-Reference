# 26. ファイルダウンロード

## ファイルをダウンロードする（同期）
![ファイルをダウンロードする（同期）](resource/HTTPClient/download.png "ファイルをダウンロードする（同期）")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	// インターネットに接続されているかをチェック
	if (!Internet::IsConnected())
	{
		return;
	}

	const FilePath url = L"http://eoimages.gsfc.nasa.gov/images/imagerecords/1000/1133/AS17-148-22727.jpg";

	const FilePath savePath = L"Tutorial-Download.jpg";

	HTTPClient client;

	// ダウンロード（同期）
	if (!client.download(url, savePath))
	{
		return;
	}

	const Texture texture(savePath);

	while (System::Update())
	{
		texture.draw();
	}
}
```

## 非同期ダウンロードの進行状況を取得する
![非同期ダウンロードの進行状況を取得する](resource/HTTPClient/downloadasync.png "非同期ダウンロードの進行状況を取得する")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	if (!Internet::IsConnected())
	{
		return;
	}

	const Font font(20);

	const FilePath url = L"http://eoimages.gsfc.nasa.gov/images/imagerecords/4000/4882/AS11-44-6548_lrg.jpg";
	const FilePath savePath = L"Tutorial-Download2.jpg";

	HTTPClient client;

	// ダウンロード（非同期）
	if (!client.downloadAsync(url, savePath))
	{
		return;
	}

	// まだダウンロードされていないので、この時点では読み込まない
	Texture texture;

	while (System::Update())
	{
		if (texture)
		{
			texture.scale(0.5).draw();
		}

		if (Input::KeyC.clicked)
		{
			// 実行中のダウンロードの中止
			client.cannelDownload();
		}

		const DownloadProgress progress = client.retreiveProgress();

		if (progress.status == DownloadStatus::Working)
		{
			const double p = progress.getProgress().value_or(0.5);

			RectF(p * 640, 80).draw();

			font(0_dp, p * 100, L'%').drawCenter(400);
		}
		else if (progress.status == DownloadStatus::Succeeded)
		{
			texture = Texture(savePath);
		}
		else if (progress.status == DownloadStatus::None)
		{
			font(L"ダウンロード中のファイルはありません。").drawCenter(400);
		}
	}
}
```

[← 前の章へ戻る](HSV.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](Draw-3d.md)