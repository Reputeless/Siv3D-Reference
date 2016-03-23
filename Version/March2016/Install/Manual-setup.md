# 手動インストール

## 1. インストール
- <a href="http://siv3d.jp/downloads/Siv3D/Siv3DPackage(March2016).zip" target="_blank">Siv3D Package をダウンロード</a>し、適当なディレクトリに解凍します（インストール後はフォルダを移動できません）

- ユーザ環境変数 `SIV3D_20160310` を作成し、解凍したフォルダ内にある Inc や Lib の **親フォルダ** のパスを指定します
 - 例: `C:\Users\UserName\Documents\Siv3DPackage(March2016)\Siv3DPackage(March2016)`　(<a href="resource/env7.png" target="_blank">設定画面の例</a>)

- 解凍したフォルダ内にある `Siv3D(March2016).zip` を `ドキュメント/Visual Studio 2015/Templates/ProjectTemplates` フォルダ内にコピーします

以上でインストールは完了です。アンインストールはこの逆の手順です。  

## 2. プロジェクトの作成
- Visual Studio 2015 を起動し、メニューから | ファイル | → | 新規作成 | → | プロジェクト | を選択します

- | ▼テンプレート | → | ▼Visual C++ | の一覧にある | Siv3D(March2016) | を選択します

-  プロジェクト名を入力して | OK | を押します　(<a href="Troubleshooting.md" target="_blank">※作成に失敗する場合</a>) 

- Main.cpp に以下のコードか用意されているので、ビルド・実行します　(<a href="Troubleshooting.md" target="_blank">※Main.cpp が見つからない、ビルドに失敗する場合</a>) 
 
```cpp
# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font(L"ようこそ、Siv3D の世界へ！").draw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
```
おめでとうございます！最初の Siv3D プログラムが動きました。  
<a href="../../../README.md" target="_blank">トップページ</a> に戻り、チュートリアルに進んでください。

