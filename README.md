# LocalEtc for C++

## 概要
文字コード差異等を入出力で吸収する、Windows/Linux共通で使用できるC++支援プログラム

実行動作例（ExampleLocalEtc）と一緒に格納しておく

## 機能
- **標準出力・標準エラー、ファイル読み書き** : 文字コードを指定したら後は関数が処理する
- **OSアクセス（起動引数、ファイルCopy等、環境変数取得）** : Windows/Linux共通
- **UTF-8文字列処理** : 内部はUTF-8のstringで動作するためUTF-8用の文字列関数追加
- **一般関数** : 標準化された関数にないが広範囲で使いたい関数を追加
- **以上をWindowsとLinuxで共通に使用できる**

文字コードの対応については  
- Shift-JIS / UTF-8（BOMあり・なし） / UTF-16（BOMあり）に対応
- 文字コードの違いを吸収するため、内部はUTF-8のみで処理したらよい

既存ソフト（join_logo_scp）Unicode対応のため作成したもので、
既存ソースを最小限の変更で対応できるように考慮。

## 使い方
### ビルド方法
1. C++17環境に`LocalEtc.cpp`, `LocalEtc.hpp`を追加する
2. コンパイルでは`LocalEtc.cpp`も追加して、一緒にリンクする

#### 実行動作例(ExampleLocalEtc)のビルドファイル
- `ExampleLocalEtc.sln` (WindowsのVisual Studio 2022)
- `makefile` （Linuxのmake）  

### 記述
1. `#include "LocalEtc.hpp"` を使用するソースに追加する
2. 呼び出し先は全部LocalEtcの名前空間に存在するため、次のどちらかでアクセスする
   - `using namespace LocalEtc;`を定義する
   - 個別に`LocalEtc::`を付加して使用する
3. コマンド詳細は`LocalEtc使用メモ.txt`を参照

- 既存ソースに対応させる場合、cout/cerr/ifstream/ofstreamを使っていたら変更量が少なく対応しやすい
- 文字列はstring変数で呼び出されること前提の作成（wstringではない。 << の使用が面倒）

### コマンド記述例
- 動作としては文字コードの違いを吸収で、内部動作はUTF-8に統一している
- 定数文字列はUTF-8設定してu8は省略。省略せずu8を付けるとc++20では型指定も付けないとstringはエラーになる

標準出力に事前設定された文字コードで出力（coutをlcoutに変更で対応）  
```c++
lcout << "文字列出力" << std::endl
```

指定文字コードでファイル出力（ofstreamをLocalOfsに変更で対応。文字コード設定部分のみ追加）  
```c++
string fname = "ファイル名.txt";
LocalOfs ofs;
int num = LSys.getUtfNumFromStr("UTF8"); // デフォルト文字コードから変更する場合の追加行
ofs.setUtfNum(num);      // デフォルト文字コードから変更する場合の追加行
ofs.open(fname);
if ( !ofs ) return;
string buf = "書き込みデータ\n";
ofs << buf;
ofs.close();
```

文字コードを自動認識してファイル読み込み（ifstreamをLocalIfsに変更で対応）
```c++
string fname = "ファイル名.txt";
LocalIfs ifs(fname);
if ( !ifs ) return;
string buf;
if ( !getline(ifs,buf) ) return;  // データなしはreturn
ifs.close();
```

環境変数取得（LSys.（名前空間はLocalEtc）はOS・文字コード違いを吸収する処理）
```c++
string strVal;
bool success = LSys.getEnvString(strVal, "CLI_IN_PATH");
```
## ライセンス
自由に役立てたらと思いますが、明確化して MITライセンス で提供します。
