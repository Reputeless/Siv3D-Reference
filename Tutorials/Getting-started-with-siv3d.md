# 1. Siv3D の基本

## 最小限のプログラム

Siv3D のロゴを表示してすぐに終了する、一番短くて簡単なプログラムです。

```cpp
# include <Siv3D.hpp>

void Main()
{

}
```

## ウィンドウを表示しよう
![ウィンドウ](resource/Getting-started-with-siv3d/window.png "ウィンドウを表示しよう")  
**メインループ** `while (System::Update())` を書くと、  
**ウィンドウが閉じられる**か、**Esc キーが押される**までアプリケーションが実行し続けます。  
メインループは 1 フレームで 1 周、一般的なパソコンでは 1 秒間に最大 60 周実行されます。  
メインループ内にプログラムを書くことで、毎フレーム継続して絵を表示したり、入力を処理したりできます。

```cpp
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{

	}
}
```

## 画面の座標

ウィンドウの黒い部分が画面（**クライアント領域**）です。  
Siv3D ではクライアント領域に図形や画像を表示できます。  
クライアント領域上の位置を表す**座標**は一番左上が (0,0)、**右方向が +X**, **下方向が +Y** です。  
クライアント領域の大きさは、特に指定しない限り、**幅 640 ピクセル**, **高さ 480 ピクセル** です。  
そのときの右下の座標は (639,479) です。  

```cpp
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```

## XXXXXX

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```

## XXXXXX

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```

[次の章へ進む →](Draw-shape.md)
