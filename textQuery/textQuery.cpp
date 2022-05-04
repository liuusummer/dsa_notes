// textQuery.cpp: 定义应用程序的入口点。
//

#include "textQuery.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 先编写使用类的程序 再实现类
// class TextQuery
// class QueryResult
void runQueries(ifstream &infile) {
	// infile 是一个ifstream，指向我们要处理的文件
	TextQuery tq(infile);  // 保存文件并建立查询map
	// 提示输入要查询的单词 完成查询并打印结果
	while (true) {
		cout << "enter word to look for,or q to quit: ";
		string s;
		// 若遇到文件尾 或 用户输入了'q'循环终止
		if(!(cin >> s) || s == "q") {
			break; // 终止
		}
		print(cout, tq.query(s)) << endl;
	}

}


int main()
{
	cout << "Hello CMake." << endl;
	ifstream fin("D:\\dsa_notes\\textQuery\\input.txt");

	runQueries(fin);
	
	return 0;
}
