# Twitter クライアント

## つぶやき
![つぶやき](resource/TwitterClient/TwitterClient1.png "つぶやき")  
あらかじめ <a href="https://apps.twitter.com" target="_blank">https://apps.twitter.com</a> で Twitter アプリケーションを作成し、Consumer Key (API Key) と Consumer Secret (API Secret) を取得する必要があります。
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	// Consumer Key (API Key)
	const String API_key = L"XXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	// Consumer Secret (API Secret)
	const String API_secret = L"XXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	TwitterClient twitter(API_key, API_secret);
	twitter.openTokenPage();

	GUI guiAuth(GUIStyle::Default);
	guiAuth.setTitle(L"PIN の入力");
	guiAuth.addln(L"PIN", GUITextField::Create(7));
	guiAuth.add(L"auth", GUIButton::Create(L"認証"));
	guiAuth.setPos(40, 40);

	GUI guiTweet(GUIStyle::Default);
	guiTweet.setTitle(L"ツイート");
	guiTweet.addln(L"text", GUITextArea::Create(6, 24, 140, false));
	guiTweet.add(L"tweet", GUIButton::Create(L"ツイート"));
	guiTweet.setPos(40, 200);

	while (System::Update())
	{
		guiAuth.button(L"auth").enabled = (guiAuth.textField(L"PIN").text.length == 7);
		guiTweet.button(L"tweet").enabled = !guiTweet.textArea(L"text").text.isEmpty;

		if (guiAuth.button(L"auth").pushed && twitter.verifyPIN(guiAuth.textField(L"PIN").text))
		{
			guiAuth.release();
			guiTweet.textArea(L"text").enabled = true;
		}

		if (guiTweet.button(L"tweet").pushed)
		{
			twitter.tweet(guiTweet.textArea(L"text").text);
			guiTweet.textArea(L"text").setText(L"");
		}
	}
}
```

## 画像の投稿
![画像の投稿](resource/TwitterClient/TwitterClient2.png "画像の投稿")  
```cpp
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	// Consumer Key (API Key)
	const String API_key = L"XXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	// Consumer Secret (API Secret)
	const String API_secret = L"XXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	TwitterClient twitter(API_key, API_secret);
	twitter.openTokenPage();

	GUI guiAuth(GUIStyle::Default);
	guiAuth.setTitle(L"PIN の入力");
	guiAuth.addln(L"PIN", GUITextField::Create(7));
	guiAuth.add(L"auth", GUIButton::Create(L"認証"));
	guiAuth.setPos(40, 40);

	Image image = Image(L"Example/Windmill.png");
	Image thumbnail;
	Imaging::Fit(image, thumbnail, 300, 300);

	GUI guiTweet(GUIStyle::Default);
	guiTweet.setTitle(L"ツイート");
	guiTweet.add(L"text", GUITextArea::Create(12, 12, 140, false));
	guiTweet.addln(L"image", GUITexture::Create(Texture(thumbnail)));
	guiTweet.add(L"selectImage", GUIButton::Create(L"画像を変更"));
	guiTweet.add(L"tweet", GUIButton::Create(L"画像つきでツイート"));
	guiTweet.setPos(40, 200);

	while (System::Update())
	{
		guiAuth.button(L"auth").enabled = (guiAuth.textField(L"PIN").text.length == 7);
		guiTweet.button(L"tweet").enabled = !guiTweet.textArea(L"text").text.isEmpty;

		if (guiAuth.button(L"auth").pushed && twitter.verifyPIN(guiAuth.textField(L"PIN").text))
		{
			guiAuth.release();
			guiTweet.textArea(L"text").enabled = true;
			guiTweet.setPos(40, 40);
		}

		if (guiTweet.button(L"selectImage").pushed)
		{
			image = Dialog::OpenImage();

			Imaging::Fit(image, thumbnail, 300, 300);

			guiTweet.texture(L"image").texture = Texture(thumbnail);
		}

		if (guiTweet.button(L"tweet").pushed)
		{
			twitter.tweetWithMedia(guiTweet.textArea(L"text").text, image);

			guiTweet.textArea(L"text").setText(L"");
		}
	}
}
```

## ツイートページを開く
画像は投稿できませんが Twitter アプリケーション登録は不要です。  
```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (Input::KeyT.clicked)
		{
			Twitter::OpenTweetWindow(L"Hello, Siv3D!");
		}
	}
}
```
