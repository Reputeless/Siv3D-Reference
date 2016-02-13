# 開発中の機能

## Siv3D February 2016 
- 新機能
 - <b>パイプサーバー</b> (Thanks zenito9970)
 - Line::reversed()
 - Line3D::reversed()
 - QuadraticBezierPath と CubicBezierPath にデフォルトコンストラクタを追加
 
- パフォーマンス改善
 -  
 
- バグ修正
 - CustomImage から DynamicTexture を初期化できなかったバグを修正
 - Wave::Wave(const SecondsF&) のバグを修正
 - Box2D の lib のパスが誤っていた問題を修正 (Thanks tsuzu)
 - VideoPlayer::operaotr bool() が定義されていなかったバグを修正

- 仕様変更
 -  
 
- その他
 - libwebp のバージョンを 0.4.3 から 0.5.0 に更新
  

## Planned for Siv3D February 2016
- 32bit/64bit 両対応
- Mesh::Create~ で作成できる 3D 形状を追加
- JSON, CSV のファイルトラッキングのオプション
- ムービーのピクセルアスペクト比取得
- ZIPReader のバグ修正
  

## Planned for Later
