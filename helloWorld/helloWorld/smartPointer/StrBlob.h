#ifndef StrBlob_h_
#define StrBlob_h_
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <iterator>
class StrBlobPtr;  // ��Ҫ��ǰ������
class StrBlob{
	friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;

	// print()
	void print()const{
		if (size() == 0) {
			std::cerr << "error.\n";
		}
		std::ostream_iterator<std::string> it(std::cout, " ");
		std::copy(data->begin(), data->end(), it);
	}


	// default constructor
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }
	// ��Ӻ�ɾ��Ԫ��
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();

	// ����begin end����
	StrBlobPtr begin();
	StrBlobPtr end();
	
	

	// Ԫ�ط���
	std::string &front();
	std::string &back();

	const std::string &front() const {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	const std::string &back() const {
		check(0, "back on empty StrBlob");
		return data->back();
	}

private:
	std::shared_ptr<std::vector<std::string>> data;
	// ���data[i]���Ϸ� �׳�һ���쳣
	void check(size_type i, const std::string &msg)const;
};

StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>()) {
}
StrBlob::StrBlob(std::initializer_list<std::string> il) :
	data(std::make_shared<std::vector<std::string>>(il)) {
}

void StrBlob::check(size_type i, const std::string &msg)const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}
std::string &StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}
std::string &StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

class StrBlobPtr {
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0)
		:wptr(a.data),curr(sz) {
	}
	std::string &deref()const;
	StrBlobPtr &incr(); // ǰ׺����
private:
	// �����ɹ���check����һ��ָ��vector��shard_ptr
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string &)const;

	// ����һ��weak_ptr ��ζ�ŵײ�vector���ܻᱻ����
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;  // �������еĵ�ǰλ��
};

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg)const {
	auto ret = wptr.lock(); // vector�Ƿ񻹴���
	if (!ret) {   // vector�����٣�lock()����һ����ָ��
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size()) {
		throw std::out_of_range(msg);
	}
	return ret;  // ���򷵻�ָ��vector��shared_ptr
}

std::string &StrBlobPtr::deref()const {
	auto p = check(curr, "deference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
	// ���curr�Ѿ�ָ������β��λ�ã��Ͳ��ܵ�����
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

// ����begin end����
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}



#endif