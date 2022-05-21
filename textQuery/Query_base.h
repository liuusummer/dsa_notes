#ifndef Query_base_h_
#define Query_base_h_
#include <string>
#include <memory>
#include "textQuery.h"
// ������� �����ѯ���ʹ������� ���г�Ա����private��
class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;   // ����val����
	virtual ~Query_base() = default;
private:
	// eval �����뵱ǰQueryƥ���QueryResult
	virtual QueryResult eval(const TextQuery &)const = 0;

	// rep �Ǳ�ʾ��ѯ��һ��string
	virtual std::string rep()const = 0;
};

// ����һ������Query_base�̳���ϵ�Ľӿ���
class Query {
	// ��Щ�������Ҫ���ʽ���shared_ptr�Ĺ��캯��  �ú�����˽�е�
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);

public :
	Query(const std::string &);  // ����һ���µ�Query
	// �ӿں���  ���ö�Ӧ��Query_base����
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

// WordQuery��
class WordQuery :public Query_base {
	friend class Query; // Query ʹ��WordQuery�Ĺ��캯��
	WordQuery(const std::string &s):query_word(s){}
	// ������ࣺWordQuery���������м̳ж����Ĵ��麯��
	QueryResult eval(const TextQuery &t)const {
		return t.query(query_word);
	}
	std::string rep()const { return query_world; }
	std::string query_word;   // Ҫ���ҵĵ���
};

// Query���캯��
inline Query::Query(const std::string &s) :q(new WordQuery(s)){
}

// NotQuery��
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

// BinaryQuery  �������
class BinaryQuery :public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) :
		lhs(l), rhs(r), opSym(s) {
	}
	// �����ࣺBinaryQuery������eval
	std::string rep() const {
		return "(" + lhs.rep() + " " + opSym + " "
			rhs.rep() + ")";
	}
	Query lhs, rhs;  // �����Ҳ��������
	std::string opSym;	// �����������
};
// AndQuery ��
class AndQuery :public BinaryQuery {
	friend Query operator &(const Query &, const Query &);
	AndQuery(const Query &l, const Query &r) :
		BinaryQuery(l, r, "&") {
	}
	// �̳�rep
	QueryResult eval(const TextQuery &)const;
};
inline Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

// OrQuery ��
class OrQuery :public BinaryQuery {
	friend Query operator | (const Query &, const Query &);
	OrQuery(const Query &l, const Query &r) :
		BinaryQuery(l, r, "|") {
	}
	// �̳�rep
	QueryResult eval(const TextQuery &)const;
};
inline Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
#endif