// ExampleLocalEtc.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
// LocalEtcの使用例です。
// cout/ifstream/ofstream を lcout/LocalIfs/LocalOfs に置き換えで文字コード処理を実現しています。
//
// このプログラムは文字コードを指定してファイルの読み書きを行う例です。引数はソース最後あたりを参照
// コマンドライン動作で、Windows/Linux共通のソースです(C++17使用)
//
// Visual StudioはコンパイルのUTF-8設定(/utf-8)で文字定数の前につけるu8を省略
// （u8を付けるとc++20では型指定も付けないとstringではエラーになるので積極的に省略）
//

#include "LocalEtc.hpp"
using namespace LocalEtc;

int main(int argc, char* argv[])
{
	// 標準出力／標準エラーの文字コードを変更する場合はコメントを外す
	//std::string strSys = "UTF8";
	//LSys.setSysUtfNum( LSys.getUtfNumFromStr(strSys) );

	// 起動時引数取得
    std::vector<std::string> listArg = LSys.getMainArg(argc, argv);

	if ( listArg.size() == 4 ){		// ファイル書き込み処理
		int numUtf = LSys.getUtfNumFromStr(listArg[2]);  // 文字列から文字コード番号取得
		if ( numUtf < 0 ){		// 文字列異常
			lcout << "文字コードが異常です : " << listArg[2] << std::endl;
			return 1;
		}
		LocalOfs ofs;		// ofstreamをLocalOfsに置き換え
		ofs.setUtfNum(numUtf);		// ファイルの文字コード設定（デフォルト設定で使う場合は不要）
		ofs.open(listArg[1]);	// open
//		ofs.open(listArg[1], std::ios::app);	// append
		if ( !ofs ){
			lcout << "書き込み失敗 : " << listArg[1] << std::endl;
			return 1;
		}
		ofs << listArg[3] << std::endl;		// 書き込み
		ofs.close();
		// 名前空間は全部LocalEtcなので、LocalEtc::付加も可能
		LocalEtc::lcout << "書き込み成功\n";
	}
	else if ( listArg.size() == 2 ){		// ファイル読み込み処理
		LocalIfs ifs(listArg[1]);		// ifstreamをLocalIfsに置き換え
		if ( !ifs ){  // 読み込み失敗
			lcout << "ファイルがありません : " << listArg[1] << std::endl;
			return 1;
		}
		std::string buf;
		if ( !getline(ifs,buf) ){
			lcout << "ファイル内にデータがありません\n";
			 return 1;  // データなし
		}
		ifs.close();
		int numUtf = ifs.getUtfNum();	// 読み込みファイルの文字コード取得（open以降で取得可能）
		lcout << sformat("ファイルの文字コード選択は %s です\n", LSys.getUtfStrFromNum(numUtf).c_str());
		lcout << "1行取得データ：" << buf << std::endl;
		lcout << sformat("文字列長は %d です\n", LStr.getStrLen(buf));
	}
	else{
		// UTF-8設定なければ定数文字列に u8 付加が必要
		lcout << u8"ファイル名のみはread、出力文字列まで付加したらwrite\n";
		lcout << "ExampleLocalEtc ファイル名 文字コード 出力文字列\n";
		lcout << "ExampleLocalEtc ファイル名\n";
		lcout << "  文字コード: STD UTF8 UTF16 SJIS UTF8N \n";
		return 1;
	}
	return 0;
}
