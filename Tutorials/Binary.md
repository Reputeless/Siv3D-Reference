# 18. バイナリファイル
バイナリファイルは、データをテキストではなく **バイナリデータ** で扱います。  
例えば 123 という int 型の数値は、`L"123"` という 3 文字（NULL 終端を含めると 8 バイト) の文字列ではなく、`00000000000000000000000001111011` というビット列で表される 4 バイトのデータとして扱います。  
データをファイルに保存する際、テキスト形式で保存すると、テキストから数値、数値からテキストへの変換にコストがかかり、必要なサイズも大きくなります。一方、バイナリデータとして扱えば変換のコストはかかりませんし、最小限のデータサイズしか必要としません。  
int や double 型などのプリミティブ型や、プリミティブ型で構成された trivially copyable なクラス (Point, Vec2, Rect, Color) などは容易にバイナリデータとして扱えますが、Array や String など、ポインタで内部のデータを管理するデータ型をバイナリデータとして扱うのは苦労が伴います。シリアライズ機能を使うと、Array や String, その他いくつかの Siv3D の trivially copyable でないクラスをバイナリデータとして扱えるようになります。

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

## XXXXX

```cpp
XXXXXXXXXXXXXXXXXXXXXX
```

[← 前の章へ戻る](Text-data.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](GUI.md)