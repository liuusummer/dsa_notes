/*箱子排序*/
// error
#include <iostream>
#include <string>
#include "chain.h"
using std::string;
using std::endl;
struct StudentRecord {
	int score;
	string *name;

	// 重载 !=
	int operator!=(const StudentRecord &t)const {
		return (score != t.score);
	}
	// 类型StudentRecord到int的类型转换
	/* 类型转换函数用于将类类型转换为其他类型 */
	operator int() const { return score; }
};
std::ostream &operator<<(std::ostream &out,const StudentRecord &t) {
	out << t.score << " " << *t.name << endl;
	return out;
}
void binSort(chain<StudentRecord> &theChain, int range) {
	// 按StudentRecord的score排序

	// 对箱子初始化
	chain<StudentRecord> *bin;
	bin = new chain<StudentRecord>[range + 1];

	// 把学生记录从链表中取出，放进对应的箱子
	int numberOfElements = theChain.size();
	for (int i = 1; i <= numberOfElements; i++) {
		auto x = theChain.get(0);
		theChain.erase(0);
		// 根据分数决定放进哪个箱子
		bin[x.score].insert(0, x);
	}

	// 从箱子中收集元素 放回theChain
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
