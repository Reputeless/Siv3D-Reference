# 開発中の機能

## Siv3D March 2016 
- 新機能
 - <b>32bit/64bit 両対応</b>
 - <b>パイプサーバー</b> (Thanks zenito9970)
 - <b>Forward Rendering での Viewport 設定</b>
 - <b>MeshData で作成できる 3D 形状を追加</b>
 - Line::reversed() (Thanks pctg_x8)
 - Line3D::reversed() (Thanks pctg_x8)
 - QuadraticBezierPath と CubicBezierPath にデフォルトコンストラクタを追加

- バグ修正
 - CustomImage から DynamicTexture を初期化できなかったバグを修正
 - Wave::Wave(const SecondsF&) のバグを修正
 - Box2D の lib のパスが誤っていた問題を修正 (Thanks tsuzu)
 - VideoPlayer::operaotr bool() が定義されていなかったバグを修正
 - Asset の UnregisterByTag で assert が発生するバグを修正 (Thanks rinifisu)
 - ZIPReader::extractAll() のバグを修正 (Thanks asachun)

- 仕様変更
 -  y 座標のみを引数にとる Font::drawCenter(), regionCenter(), DrawableString::drawCenter(), regionCenter() を廃止
 
- その他
 - libwebp のバージョンを 0.4.3 から 0.5.0 に更新
  
## Planned for Siv3D March 2016
- その他バグ修正
  

## Planned for Later
