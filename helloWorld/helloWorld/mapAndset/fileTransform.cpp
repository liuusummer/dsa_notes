/* ����һ��string ����ת��Ϊ��һ��string */
/* ���������������ļ� 
	��һ���ļ�����ת������ ����ת���ڶ����ļ��е��ı�
	ÿ�������ɲ��ֹ��ɣ�һ�����ܳ����������ļ��еĵ��ʺ�һ�������滻���Ķ���
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

// word_transform ������������ ���������󶨵�ת�������Ҫת�����ı�
void word_transform(ifstream &, ifstream &);

// buildMap ��ȡת�������ļ���������һ��map,���ڱ���ÿ�����ʵ���ת�����ݵ�ӳ��
map<string, string> buildMap(ifstream &);

// transform����һ��string,�������ת�����򣬷���ת���������
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
		istringstream stream(text);  // ��ÿһ�е�string��
		string word;
		bool firstworld = true;  // �����ڵ��ʼ��һ���ո�
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
// ����ת��ӳ��
map<string, string> buildMap(ifstream &map_file) {
	map<string, string> trans_map;
	string key;  // Ҫת���ĵ���
	string value; // �滻�������
	while (map_file >> key && getline(map_file, value)) {
		// ��ȡ��һ�����ʸ�key ���������ݸ�value
		
		if (value.size() > 1) {  // ��ת������
			trans_map[key] = value.substr(1);   // ȥ��key��value��Ŀո�
		}
		else {
			throw runtime_error("no ruler for " + key);
		}
	}
	return trans_map;
}

// ʵ��ת������ 
// ���s��map�У��ö�Ӧ��value�滻�����򷵻�s����
const string &transform(const string &s, const map<string, string> &trans_map) {
	auto map_it = trans_map.find(s);
	if (map_it == trans_map.end()) {
		// û��ת������
		return s;
	}
	else {
		return map_it->second;  // ʹ���滻����
	}
}