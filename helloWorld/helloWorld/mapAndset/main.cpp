#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

string trimStr(string s) {  // 对单词的处理 
				// 大写切换成小写  去掉其中的标点
	constexpr char *punctuations{ "\"'`:*_-;,.?!()[]{}" };
	for (auto &c : s) {
		if (c >= 'A' && c <= 'Z') {
			c -= 'A' - 'a';   // 大写换成小写
		}
	}
	auto bg = s.find_first_not_of(punctuations);
	if (bg == string::npos) {
		return "";   // 全是标点  返回空串
	}
	auto ed = s.find_last_not_of(punctuations);
	return s.substr(bg, ed - bg + 1);
}
// 单词计数
map<string, size_t> word_count(vector<string> &words) {
	map<string, size_t> counts;
	for (const auto &word : words) {
		++counts[trimStr(word)];
	}
	return counts;
}

int main() {

	ifstream fin("D:\\dsa_notes\\helloWorld\\helloWorld\\mapAndset\\test.txt");
	if (!fin.is_open()) {
		cerr << "error!\n";
	}
	
	// 文件 流迭代器构造vector
	istream_iterator<string> it(fin), eof;
	vector<string> words(it, eof);
	for_each(words.begin(), words.end(), 
		[](string s) {cout << s << "/"; });
	auto result = word_count(words);
	for (const auto &w : result) {
		cout << endl << w.first << " occurs "
			<< w.second << " time(s)\n";
	}

}