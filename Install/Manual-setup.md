# 手動でのセットアップ

## 1. インストール
- <a href="#" target="_blank">Siv3D Package をダウンロード</a> し、適当なディレクトリに解凍します（あとで移動させることはできません）

- 環境変数 `SIV3D_20160110` に、解凍したフォルダ内にある Inc や Lib の **親フォルダ** のパスを指定します
 - 例: `C:\Users\UserName\Documents\Siv3DPackage(January2016)\Siv3DPackage(January2016)`

- 解凍したフォルダ内にある `Siv3D(January2016).zip` を `ドキュメント/Visual Studio 2015/Templates/ProjectTemplates/` 内にコピーします

以上でインストールは完了です。アンインストールはこの逆の手順です。  

## 2. プロジェクトの作成
- Visual Studio 2015 を起動し、メニューから | ファイル | → | 新しいプロジェクト | を選択します

- | ▼テンプレート | → | ▼Visual C++ | の一覧にある | Siv3D(January2016) | を選択します

-  プロジェクト名を入力して | OK | を押します

- Main.cpp に以下のコードか用意されているので、ビルド・実行します
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

## 3. Siv3D を楽しもう

まずは チュートリアル を読んで、基本的な機能とプログラムの書き方を覚えましょう。


