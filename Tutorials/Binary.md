# 18. バイナリファイル
**バイナリファイル** は、データをテキストではなく **バイナリデータ** で扱います。  
例えば 123 という int 型の数値は、`L"123"` という 3 文字（NULL 終端を含めると 8 バイト) の文字列ではなく、`00000000000000000000000001111011` というビット列で表される 4 バイトのデータとして扱います。  
データをファイルに保存する際、テキスト形式で保存すると、テキストから数値、数値からテキストへの変換にコストがかかり、必要なサイズも大きくなります。一方、バイナリデータとして扱えば変換のコストはかかりませんし、最小限のデータサイズしか必要としません。  
int や double 型などのプリミティブ型や、プリミティブ型で構成された trivially copyable なクラス (Point, Vec2, Rect, Color) などは容易にバイナリデータとして扱えますが、Array や String など、ポインタで内部データを管理するデータ型をバイナリデータとして扱うのには苦労が伴います。**シリアライズ機能** を使うと、Array や String, その他いくつかの Siv3D の trivially copyable でないクラスをバイナリデータとして扱えるようになります。独自に定義した型をシリアライズに対応させることもできます。

## バイナリファイルの書き込み

```cpp
# include <Siv3D.hpp>

struct Something
{
	int32 a, b, c, d;
};

void Main()
{
	const Something s = { 10, 20, 30, 40 };

	BinaryWriter writer(L"Tutorial-Binary.bin");

	// 4 バイト
	writer.write(12345);

	// 8 バイト
	writer.write(3.1415);

	// 16 バイト
	writer.write(s);
}
```

## バイナリファイルの読み込み

```cpp
# include <Siv3D.hpp>

struct Something
{
	int32 a, b, c, d;
};

void Main()
{
	// 書き込みのサンプルで作成したファイル
	BinaryReader reader(L"Tutorial-Binary.bin");

	int32 n;

	double f;

	Something s;

	reader.read(n);

	reader.read(f);

	reader.read(s);

	Println(n);

	Println(f);

	Println(s.d);

	WaitKey();
}
```

## 読み込み位置の移動

```cpp
# include <Siv3D.hpp>

void Main()
{
	// 書き込みのサンプルで作成したファイル
	BinaryReader reader(L"Tutorial-Binary.bin");

	reader.setPos(24);

	int32 d;
	
	reader.read(d);

	Println(d);

	WaitKey();
}
```

## String をバイナリファイルで扱う

```cpp
# include <Siv3D.hpp>

void Main()
{
	const String s = L"Siv3D Engine";
	const uint64 length = s.length;

	BinaryWriter writer(L"Tutorial-Binary.bin");
	writer.write(length);
	writer.write(s.data(), length * sizeof(wchar));
	writer.close();


	BinaryReader reader(L"Tutorial-Binary.bin");

	String s2;
	size_t length2 = 0;

	reader.read(length2);

	s2.resize(length2);

	reader.read(&s2[0], s2.length * sizeof(wchar));

	Println(s2);

	WaitKey();
}
```

## String をバイナリファイルで扱う（シリアライズ機能）

```cpp
# include <Siv3D.hpp>

void Main()
{
	const String s = L"Siv3D Engine";
	Serializer<BinaryWriter> writer(L"Tutorial-Serializer.bin");
	writer(s);
	writer.getWriter().close();

	Deserializer<BinaryReader> reader(L"Tutorial-Serializer.bin");
	String s2;
	reader(s2);
	Println(s2);

	WaitKey();
}
```

## 独自に定義した型をシリアライズに対応させる

```cpp
# include <Siv3D.hpp>

struct Monster
{
	String name;

	int32 id;

	double size;

	// このようなメンバ関数を定義する
	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(name, id, size);
	}
};

void Main()
{
	const Monster monster = { L"Goblin", 123, 1.2 };
	Serializer<BinaryWriter> writer(L"Tutorial-Serializer.bin");
	writer(monster);
	writer.getWriter().close();

	Deserializer<BinaryReader> reader(L"Tutorial-Serializer.bin");
	Monster m;
	reader(m);
	Println(m.name);
	Println(m.id);
	Println(m.size);

	WaitKey();
}
```

[← 前の章へ戻る](Text-data.md)　|　[- 目次 -](Index.md)　|　[次の章へ進む →](GUI.md)