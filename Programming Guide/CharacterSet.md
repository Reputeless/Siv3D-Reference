# CharacterSet
マルチバイト文字列や Unicode 文字列の相互変換や、パーセントエンコードを行います。

## 文字列変換早見表

|                  | std::string へ    | std::wstring へ | String へ | const char* へ           | const wchar* へ        |
|:----------------:|:----------------:|:---------------:|:---------:|:------------------------:|:---------------------:|
| std::string から  | =                | Widen().str()   | Widen()   | std::string::c_str()     | Widen().c_str()       |
| std::wstring から | Narrow()         | =               | =         | Narrow().c_str()         | std::wstring::c_str() |
| String から       | String::narrow() | String::str()   | =         | String::narrow().c_str() | String::c_str()       |


## std::string から String に変換する

```cpp

```

## std::wstring から String に変換する

```cpp

```

## String から std::string に変換する

```cpp

```

## String から std::wstring に変換する

```cpp

```

## String から const char* に変換する

```cpp

```

## String から const wchar_t* に変換する

```cpp

```

## UTF8 から String に変換する

```cpp

```

## String から UTF8 に変換する

```cpp

```

## UTF32 から String に変換する

```cpp

```

## String から UTF32 に変換する

```cpp

```

## 文字列をパーセントエンコードする

```cpp

```

## ASCII 文字で構成されたマルチバイト文字列を String に変換する

```cpp

```

## ASCII 文字で構成された String を std::string に変換する

```cpp

```
