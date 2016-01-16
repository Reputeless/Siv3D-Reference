# ファイルの埋め込み

画像や音声、テキストファイルを .exe ファイルに埋め込み、プログラムでロードする方法を解説します。

## .exe ファイルにファイルを埋め込む

プロジェクトのフォルダにある Resource.rc をメモ帳で開きます。  
※ Visual Studio で開くと設定が難しいです

デフォルトでは以下のように記述されています。
```cpp
// Siv3D Engine Rsource
64000	FILE	"Engine/LogMessages.txt"
64080	FILE	"Engine/Assets/engine_textures.s3a"
64600	FILE	"Engine/Fonts/umeplus-p-gothic.zip"
64604	FILE	"Engine/Fonts/mplus-1p-medium.zip"
64700	FILE	"Engine/Shaders/D3D11/Sprite.vs"
64701	FILE	"Engine/Shaders/D3D11/FullScreenTriangle.vs"
64702	FILE	"Engine/Shaders/D3D11/DeferredMesh.vs"
64703	FILE	"Engine/Shaders/D3D11/LightAccumulation.vs"
64704	FILE	"Engine/Shaders/D3D11/ForwardMesh.vs"
64705	FILE	"Engine/Shaders/D3D11/ForwardParticle.vs"
64706	FILE	"Engine/Shaders/D3D11/ForwardLine3D.vs"
64800	FILE	"Engine/Shaders/D3D11/Shape.ps"
64801	FILE	"Engine/Shaders/D3D11/Shape_Stencil.ps"
64802	FILE	"Engine/Shaders/D3D11/Sprite.ps"
64803	FILE	"Engine/Shaders/D3D11/Sprite_Stencil.ps"
64804	FILE	"Engine/Shaders/D3D11/Sprite_Font.ps"
64805	FILE	"Engine/Shaders/D3D11/FullScreenTriangle1xMSAA.ps"
64806	FILE	"Engine/Shaders/D3D11/FullScreenTriangle2xMSAA.ps"
64807	FILE	"Engine/Shaders/D3D11/FullScreenTriangle4xMSAA.ps"
64808	FILE	"Engine/Shaders/D3D11/FullScreenTriangle1xMSAA_Linear.ps"
64809	FILE	"Engine/Shaders/D3D11/FullScreenTriangle2xMSAA_Linear.ps"
64810	FILE	"Engine/Shaders/D3D11/FullScreenTriangle4xMSAA_Linear.ps"
64811	FILE	"Engine/Shaders/D3D11/DeferredMesh.ps"
64812	FILE	"Engine/Shaders/D3D11/DeferredMesh_Textured.ps"
64813	FILE	"Engine/Shaders/D3D11/LightAccumulation_NoFog.ps"
64814	FILE	"Engine/Shaders/D3D11/LightAccumulation_LinearFog.ps"
64815	FILE	"Engine/Shaders/D3D11/LightAccumulation_ExponentialFog.ps"
64816	FILE	"Engine/Shaders/D3D11/LightAccumulation_SquaredExponentialFog.ps"
64817	FILE	"Engine/Shaders/D3D11/LightAccumulation_HeightFog.ps"
64818	FILE	"Engine/Shaders/D3D11/DeferredFinalize.ps"
64819	FILE	"Engine/Shaders/D3D11/ForwardMesh.ps"
64820	FILE	"Engine/Shaders/D3D11/ForwardMesh_Textured.ps"
64821	FILE	"Engine/Shaders/D3D11/ForwardLine3D.ps"
64822	FILE	"Engine/Shaders/D3D11/FXAA_None.ps"
64823	FILE	"Engine/Shaders/D3D11/FXAA_Q20.ps"
64824	FILE	"Engine/Shaders/D3D11/FXAA_Q25.ps"
64825	FILE	"Engine/Shaders/D3D11/FXAA_Q39.ps"

// Optional
64040	FILE	"Engine/Objdetect/facePhoto.zip"
64041	FILE	"Engine/Objdetect/faceAnime.zip"
64601	FILE	"Engine/Fonts/mplus-1p-thin.zip"
64602	FILE	"Engine/Fonts/mplus-1p-light.zip"
64603	FILE	"Engine/Fonts/mplus-1p-regular.zip"
64605	FILE	"Engine/Fonts/mplus-1p-bold.zip"
64606	FILE	"Engine/Fonts/mplus-1p-heavy.zip"
64607	FILE	"Engine/Fonts/mplus-1p-black.zip"

// App Resource
100		ICON	"Icon.ico"
101		FILE	"Engine/Splash.png"

```

`//` で始まる行はコメントです。  
それ以外の行は `リソース番号　リソース区分　埋め込むファイルへのパス` の 3 項目で構成される **埋め込みリソース情報** が記述されています。  
デフォルトではエンジン用のファイルの埋め込が設定されています。新しくファイルを埋め込むには、埋め込みたいファイルについての記述を `リソース番号(1000～63999)    FILE   "(パス)"` という形式で追加します。

例
```
1000    FILE    "Example/Windmill.png"
1001    FILE    "Example/風の丘.mp3"
// 数字は順番通りでなくてもよい
1100    FILE    "Example/test.txt"
```

Resource.ec の変更を保存し、プロジェクトをビルドすると、該当ファイルが .exe に埋め込まれます。


## 埋め込んだファイルをプログラムでロードする
.exe に埋め込んだファイルのパスは `/リソース番号` になります。プログラムでこれまでファイル名を指定していた部分を置き換えます。

例
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"/1000");

	const Sound sound(L"/1001");

	const String text = TextReader(L"/1100").readAll();

	sound.play();

	Println(text);

	while (System::Update())
	{
		texture.draw();
	}
}
```

## 埋め込みファイルが存在するかのチェック
FileSystem の関数に `/リソース番号` のパスを指定した際の挙動です（上記の例のように `/1000` が存在します）

```cpp
# include <Siv3D.hpp>

void Main()
{
	Println(FileSystem::Exists(L"/1000"));	// true
	Println(FileSystem::Exists(L"/2000"));	// false
	Println(FileSystem::Exists(L"Example/Windmill.png"));	// true

	Println(FileSystem::IsResource(L"/1000"));	// true
	Println(FileSystem::IsResource(L"/2000"));	// false
	Println(FileSystem::IsResource(L"Example/Windmill.png"));	// false

	Println(FileSystem::IsFile(L"/1000"));	// true
	Println(FileSystem::IsFile(L"/2000"));	// false
	Println(FileSystem::IsFile(L"Example/Windmill.png"));	// true

	WaitKey();
}

```


