#ifndef Query_base_h_
#define Query_base_h_
#include <string>
#include <memory>
#include "textQuery.h"
// 抽象基类 具体查询类型从中派生 所有成员都是private的
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;   // 用于val函数
	virtual ~Query_base() = default;
private:
	// eval 返回与当前Query匹配的QueryResult
	virtual QueryResult eval(const TextQuery &)const = 0;

	// rep 是表示查询的一个string
	virtual std::string rep()const = 0;
};

// 这是一个管理Query_base继承体系的接口类
class Query {
	// 这些运算符需要访问接受shared_ptr的构造函数  该函数是私有的
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);

public :
	Query(const std::string &);  // 构建一个新的Query
	// 接口函数  调用对应的Query_base操作
	QueryResult eval(const TextQuery &t)const {
		return q->eval(t);
	}
	std::string rep()const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query) :q(query) {};
	std::shared_ptr<Query_base> q;
};
std::ostream &operator <<(std::ostream &os, const Query &query) {
	return os << query.rep();
}

// WordQuery类
class WordQuery :public Query_base {
	friend class Query; // Query 使用WordQuery的构造函数
	WordQuery(const std::string &s):query_word(s){}
	// 具体的类：WordQuery将定义所有继承而来的纯虚函数
	QueryResult eval(const TextQuery &t)const {
		return t.query(query_word);
	}
	std::string rep()const { return query_world; }
	std::string query_word;   // 要查找的单词
};

// Query构造函数
inline Query::Query(const std::string &s) :q(new WordQuery(s)){
}

// NotQuery类
class NotQuery :public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q) :query(q) {}

	std::string rep()const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery &)const;
	Query query;
};
inline Query operator~(const Query &operand) {
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

// BinaryQuery  抽象基类
class BinaryQuery :public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) :
		lhs(l), rhs(r), opSym(s) {
	}
	// 抽象类：BinaryQuery不定义eval
	std::string rep() const {
		return "(" + lhs.rep() + " " + opSym + " "
			rhs.rep() + ")";
	}
	Query lhs, rhs;  // 左侧和右侧运算对象
	std::string opSym;	// 运算符的名字
};
// AndQuery 类
class AndQuery :public BinaryQuery {
	friend Query operator &(const Query &, const Query &);
	AndQuery(const Query &l, const Query &r) :
		BinaryQuery(l, r, "&") {
	}
	// 继承rep
	QueryResult eval(const TextQuery &)const;
};
inline Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

// OrQuery 类
class OrQuery :public BinaryQuery {
	friend Query operator | (const Query &, const Query &);
	OrQuery(const Query &l, const Query &r) :
		BinaryQuery(l, r, "|") {
	}
	// 继承rep
	QueryResult eval(const TextQuery &)const;
};
inline Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
#endif