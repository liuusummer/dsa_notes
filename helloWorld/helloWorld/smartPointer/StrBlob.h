#ifndef StrBlob_h_
#define StrBlob_h_
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <iterator>
class StrBlobPtr;  // 必要的前置声明
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
	// 添加和删除元素
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();

	// 定义begin end操作
	StrBlobPtr begin();
	StrBlobPtr end();
	
	

	// 元素访问
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
	// 如果data[i]不合法 抛出一个异常
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
	StrBlobPtr &incr(); // 前缀递增
private:
	// 若检查成功，check返回一个指向vector的shard_ptr
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string &)const;

	// 保存一个weak_ptr 意味着底层vector可能会被销毁
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;  // 在数组中的当前位置
};

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg)const {
	auto ret = wptr.lock(); // vector是否还存在
	if (!ret) {   // vector已销毁，lock()返回一个空指针
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size()) {
		throw std::out_of_range(msg);
	}
	return ret;  // 否则返回指向vector的shared_ptr
}

std::string &StrBlobPtr::deref()const {
	auto p = check(curr, "deference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
	// 如果curr已经指向容器尾后位置，就不能递增他
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

// 定义begin end操作
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}



#endif