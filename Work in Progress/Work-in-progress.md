# 開発中の機能

## Siv3D August 2016 

- 新機能
 - **文章の読み上げ機能** 
 - **3D 描画時のシャドウ**
 - Serial::readBytes() を追加 (Thanks はむくん)
 - Quaternion コンストラクタのオーバーロードを追加 (Thanks はむくん)
 - フォルダダイアログで新規フォルダの作成を可能に (Thanks @aini_bellwood)
 - MeshData 関数で作成できる形状に Capsule を追加 (Thanks bigginer)
 - Quad::rotatedAt() を追加

- バグ修正
 - Font 使用時のメモリリークを修正 (Thanks KICKER)
 - RenderTarget 切り替え後、最後に使っていた Texture が直後に描画できなかった問題を修正 (Thanks oigami)
 - TextWriter::clear() がクラッシュすることがあった問題を修正 (Thanks ポテトサラダ)
 - ファイルの埋め込みで MP3 ファイルを読み込む際、Engine/dll(xXX)/libmpg123 が無いとクラッシュした不具合を修正 (Thanks @shunEnshuu)
 - PerlinNoise::octaveNoise0_1(const Vec2&, int32), PerlinNoise::octaveNoise0_1(const Vec3&, int32) の結果が正しくなかったバグを修正

- 仕様変更
 -  LineInt::draw() の引数を変更
 
- その他
 - 内部で使用する Boost のバージョンを 1.59.0 から 1.61.0 に更新

## Planned for Later
- HTTPClient の改善 (Thanks Tsuzu)
- Webcam の改善 (Thanks うたまろ)
- CSVReader の改善 (Thanks papas)
