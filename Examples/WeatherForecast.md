# 天気予報
![天気予報](resource/WeatherForecast/WeatherForecast.png "天気予報")  
<a href="http://www.jma.go.jp/jp/yoho/000_telop_tomorrow.html" target="_blank">気象庁サイト</a> から最新の天気予報図をダウンロードして表示します。
```cpp
# include <Siv3D.hpp>

void Main()
{
	HTTPClient client;

	ByteArray data;

	if (!client.download(L"http://www.jma.go.jp/jp/yoho/images/000_telop_tomorrow.png", data))
	{
		return;
	}

	const Texture texture(std::move(data));

	while (System::Update())
	{
		texture.draw();
	}
}
```
