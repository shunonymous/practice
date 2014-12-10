// -*- coding:utf-8-unix -*-
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost::program_options;

int main(int argc, char* argv[])
{
	// オプションの定義を行う
	// 後でマージ出来る
	options_description options1("オプション群1");
	options_description options2("オプション群2");
	options_description options3("オプション群3");
	options_description options4("オプション群4");

	// オプションは add_options() 以降に operator() を連結させて追加
	// 「,」の手前に正式名，後ろに省略名を記述（省略可）
	options1.add_options()
		("option1",						"オプション1")
		("option2,b",						"オプション2")
	;

	// option=*** で受け取る値の型を設定できる．
	// また default_value でデフォルト値も設定可
	options2.add_options()
		("option3,c",	value<int>(),				"オプション3")
		("option4,d",	value<string>(),			"オプション4")
		("option5,e",	value<int>()->default_value(10),	"オプション5")
	;

	// option=*** の値を受け取る変数を指定もできる．
	int option6;
	string option7;
	options3.add_options()
		("option6,f",	value<int>(&option6),			"オプション6")
		("option7,g",	value<string>(&option7),		"オプション7")
	;

	// 同じオプションを複数使って格納することも出来る
	options4.add_options()
		("option8",	value<vector<string> >(),		"オプション8")
	;

	// オプションの定義をマージ出来る
	options1.add(options2).add(options3);

	// オプションの値を読み込む変数
	variables_map values;

	// 色々な例外をキャッチできる（例はcatchブロック内に記述）
	try {
		// parse_command_line でコマンドライン引数をパースし，
		// この結果を store で variable_maps に格納する
		store(parse_command_line(argc, argv, options1), values);

		// コマンドライン引数だけでなく，
		// 外部ファイルからもオプションを読み込むことが出来る．
		// この際は parse_config_file を用いてパースする．
		ifstream ifs("config.txt");
		store(parse_config_file(ifs, options4), values);

		// notify を呼び出すことで values に値が格納される
		notify(values);

		// オプションの有無は count で調べる
		if (!values.count("option1") && !values.count("option2")) {
			// options_description は標準出力に投げることが出来る
			cout << options1 << endl;
			cout << options4 << endl;
		}
		if (values.count("option1")) {
			cout << "option1 が指定されました" << endl;
		}
		if (values.count("option2")) {
			cout << "option2 が指定されました" << endl;
		}

		// as<型名>()で値を取り出すことが出来る
		cout << "option3: " << values["option3"].as<int>()	<< endl;
		cout << "option4: " << values["option4"].as<string>()	<< endl;
		cout << "option5: " << values["option5"].as<int>()	<< endl;

		// 変数で受け取ったものには勿論値が格納されている
		cout << "option6: " << option6				<< endl;
		cout << "option7: " << option7				<< endl;

		// 複数データを受け取った物も使用可
		cout << "option8: ";
		vector<string> option8( values["option8"].as<vector<string> >() );
		for (vector<string>::iterator it = option8.begin(); it != option8.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;

	} catch (exception &e) {
		// 格納されていないのにも関わらず values["***"] を呼ぶと，
		//	 boost::bad_any_cast: failed conversion using boost::any_cast
		// が表示される．
		// 定義していないオプション --*** を呼ぶと，
		//	unknown option ***
		// が表示される．
		cout << e.what() << endl;
	}

	return 0;
}
