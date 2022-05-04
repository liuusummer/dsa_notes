#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

string trimStr(string s) {  // �Ե��ʵĴ��� 
				// ��д�л���Сд  ȥ�����еı��
	constexpr char *punctuations{ "\"'`:*_-;,.?!()[]{}" };
	for (auto &c : s) {
		if (c >= 'A' && c <= 'Z') {
			c -= 'A' - 'a';   // ��д����Сд
		}
	}
	auto bg = s.find_first_not_of(punctuations);
	if (bg == string::npos) {
		return "";   // ȫ�Ǳ��  ���ؿմ�
	}
	auto ed = s.find_last_not_of(punctuations);
	return s.substr(bg, ed - bg + 1);
}
// ���ʼ���
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
	
	// �ļ� ������������vector
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