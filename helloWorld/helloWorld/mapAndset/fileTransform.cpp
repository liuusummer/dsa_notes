/* 给定一个string 将其转换为另一个string */
/* 程序输入是两个文件 
	第一个文件保存转换规则 用来转换第二个文件中的文本
	每条规则由部分构成：一个可能出现在输入文件中的单词和一个用来替换它的短语
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

// word_transform 管理整个过程 两个参数绑定到转换规则和要转换的文本
void word_transform(ifstream &, ifstream &);

// buildMap 读取转换规则文件，并创建一个map,用于保存每个单词到其转换内容的映射
map<string, string> buildMap(ifstream &);

// transform接受一个string,如果存在转换规则，返回转换后的内容
const string &transform(const string &, const map<string, string> &);

int main() {
	ifstream trans("D:\\dsa_notes\\helloWorld\\helloWorld\\mapAndset\\trans.txt");
	ifstream input("D:\\dsa_notes\\helloWorld\\helloWorld\\mapAndset\\input.txt");
	word_transform(trans,input);
	return 0;
}
void word_transform(ifstream &map_file, ifstream &input) {
	auto trans_map = buildMap(map_file);
	string text;
	while (getline(input, text)) {
		istringstream stream(text);  // 绑定每一行到string流
		string word;
		bool firstworld = true;  // 控制在单词间打一个空格
		while (stream >> word) {
			if (firstworld) {
				firstworld = false;
			}
			else {
				cout << " ";
			}
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}
// 建立转换映射
map<string, string> buildMap(ifstream &map_file) {
	map<string, string> trans_map;
	string key;  // 要转换的单词
	string value; // 替换后的内容
	while (map_file >> key && getline(map_file, value)) {
		// 读取第一个单词给key 后续的内容给value
		
		if (value.size() > 1) {  // 有转换规则
			trans_map[key] = value.substr(1);   // 去掉key和value间的空格
		}
		else {
			throw runtime_error("no ruler for " + key);
		}
	}
	return trans_map;
}

// 实际转换工作 
// 如果s在map中，用对应的value替换，否则返回s本身
const string &transform(const string &s, const map<string, string> &trans_map) {
	auto map_it = trans_map.find(s);
	if (map_it == trans_map.end()) {
		// 没有转换规则
		return s;
	}
	else {
		return map_it->second;  // 使用替换短语
	}
}