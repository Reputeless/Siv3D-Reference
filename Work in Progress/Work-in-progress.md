# 開発中の機能

## Siv3D June 2016 

- 新機能
 - **日本語と英語の文章の読み上げ機能** 
 - Serial::readBytes() を追加 (Thanks はむくん)
 - Quaternion コンストラクタのオーバーロードを追加 (Thanks はむくん)

- バグ修正
 - Font 使用時のメモリリークを修正 (Thanks KICKER)
 - RenderTarget 切り替え後、最後に使っていた Texture が直後に描画できなかった問題を修正 (Thanks oigami)
 - TextWriter::clear() がクラッシュすることがあった問題を修正 (Thanks ポテトサラダ)

- 仕様変更
 -  LineInt::draw() の引数を変更
 
- その他
 - 内部で使用する Boost のバージョンを 1.59.0 から 1.61.0 に更新

## Planned for Later
- フォルダダイアログの改善 (Thanks @aini_bellwood)
- HTTPClient の改善 (Thanks Tsuzu)
- Webcam の改善 (Thanks うたまろ)
- CSVReader の改善 (Thanks papas)
