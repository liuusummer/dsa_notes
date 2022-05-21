// textQuery.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。
#ifndef textQuery_h_
#define textQuery_h_
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

class QueryResult;  //为了定义query的返回类型
class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream &);
	QueryResult query(const string &)const;

private:
	shared_ptr<vector<string>> file; // 输入文件
	// 每个单词到行号集合的映射
	map<string, shared_ptr<set<line_no>>> wm;
};

// TextQuery 构造函数
TextQuery::TextQuery(ifstream &is):file(new vector<string>) {
	string text;
	while (getline(is, text)) {
		file->push_back(text);
		int n = file->size() - 1;   // 当前的行号
		// 拆分每一行
		istringstream line(text);
		string word;
		while (line >> word) {
			// 对每一个单词
			// 如果单词不在map中 以之为下标在map中插入一项
			auto &lines = wm[word];  // lines是shared_ptr类型
			if (!lines) {  // 在第一次遇到这个单词时，此指针为空
				lines.reset(new set<line_no>);
			}
			lines->insert(n);
		}
	}
}

class QueryResult {
	friend ostream &print(ostream &, const QueryResult &);
public:
	QueryResult(string s,
		shared_ptr<set<TextQuery::line_no>> p,
		shared_ptr<vector<string>> f)
		:sought(s), lines(p), file(f) {
	};


private:
	string sought;  // 查询单词
	shared_ptr<set<TextQuery::line_no>> lines;  // 出现的行号
	shared_ptr<vector<string>> file;   // 输入文件
};

QueryResult TextQuery::query(const string&s)const {
	// 定义一个局部static对象：它是一个指向空的行号set的shared_ptr
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	// 当没有查询到指定的单词时候   返回此指针
	auto loc = wm.find(s);
	if (loc == wm.end()) {
		return QueryResult(s, nodata, file);
	}
	else {
		return QueryResult(s,loc->second,file);
	} 
}
ostream &print(ostream &, const QueryResult &);
ostream &print(ostream &os, const QueryResult &qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " " << "time(s):\n";
	for (auto num : *qr.lines) {   // qr.lines是set<line_no>的shared_ptr
									// *qr.lines解引用  num是每一个行号 
		os << "\t(line " << num + 1 << " ) "
			<< *(qr.file->begin() + num) << endl;
	}
	return os;
}


#endif