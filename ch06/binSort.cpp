/*��������*/
// error
#include <iostream>
#include <string>
#include "chain.h"
using std::string;
using std::endl;
struct StudentRecord {
	int score;
	string *name;

	// ���� !=
	int operator!=(const StudentRecord &t)const {
		return (score != t.score);
	}
	// ����StudentRecord��int������ת��
	/* ����ת���������ڽ�������ת��Ϊ�������� */
	operator int() const { return score; }
};
std::ostream &operator<<(std::ostream &out,const StudentRecord &t) {
	out << t.score << " " << *t.name << endl;
	return out;
}
void binSort(chain<StudentRecord> &theChain, int range) {
	// ��StudentRecord��score����

	// �����ӳ�ʼ��
	chain<StudentRecord> *bin;
	bin = new chain<StudentRecord>[range + 1];

	// ��ѧ����¼��������ȡ�����Ž���Ӧ������
	int numberOfElements = theChain.size();
	for (int i = 1; i <= numberOfElements; i++) {
		auto x = theChain.get(0);
		theChain.erase(0);
		// ���ݷ��������Ž��ĸ�����
		bin[x.score].insert(0, x);
	}

	// ���������ռ�Ԫ�� �Ż�theChain
	for (int j = range; j >= 0; j--) {
		while (bin[j].empty() != 0) {
			auto x = bin[j].get(0);
			bin[j].erase(0);
			theChain.insert(0, x);
		}
	}
	delete[]bin;
}

int main() {
	StudentRecord s;
	chain<StudentRecord> c;
	for (int i = 2; i <= 20; i=i+2) {
		s.score = i / 2;
		s.name = new string(s.score,'a');
		c.insert(0, s);
	}
	cout << "The unsorted chain is " << endl;
	cout << " " << c << endl;
	binSort(c, 10);
	cout << "The sorted chain is " << endl;
	cout << " " << c << endl;
} 
