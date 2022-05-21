#ifndef Template_h_
#define Template_h_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <stdexcept>

// 16.19打印容器内容 使用容器的size_type 和size()成员
template <typename Container>
std::ostream &print(const Container &container, std::ostream &os) {
	for (typename Container::size_type i = 0; i < container.size(); i++) {
		os << container[i] << " ";
	}
	return os;
}
// 16.20 打印容器内容  使用迭代器
//template <typename Container>
//std::ostream &print(const Container &container, std::ostream &os) {
//	for (auto curr = container.cbegin(); curr != container.cend(); curr++) {
//		os << *curr << " ";
//	}
//	return os;
//}
// 函数对象类 对给定指针执行delete
class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr) :os(s) {}

	template <typename T>
	void operator()(typename T *p)const {
		os << "deleting unique_ptr " << std::endl; delete p;
	}
private:
	std::ostream &os;
};




template <typename> class BlobPtr;   // 前置声明  == template<typename T>class BlobPtr(why?)

template <typename T> 
bool operator ==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template <typename T>
bool operator < (const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template <typename T> class Blob {
	friend class BlobPtr<T>;
public:
	using value_type = T;
	typedef typename std::vector<T>::size_type size_type;
	// using size_type = typename std::vector<T>::size_type;

	// constructor
	Blob();
	Blob(std::initializer_list<T> il);
	// 接受迭代器的构造函数  成员模板
	template <typename It>
	Blob(It b, It e);

	// Blob中的元素数目
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }

	// 添加和删除元素
	void push_back(const T &t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();

	// 元素访问
	T &back();
	T &operator[](size_type i);

	const T &back()const;
	const T &operator[](size_type i)const;
private:

	std::shared_ptr<std::vector<T>> data;
	// 若data[i]无效 则抛出msg
	void check(size_type i, const std::string &msg)const;
};


template <typename T>
void Blob<T>::check(size_type i, const std::string &msg)const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e) :data(std::make_shared<std::vector<T>>(b,e)){
}

template <typename T>
T &Blob<T>::back() {
	check(0, "back on empty");
	return data->back();
}
template<typename T>
const T &Blob<T>::back() const {
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T>
T & Blob<T>::operator[](size_type i) {
	check(i, "subscript out of range");
	return (*data)[i];
}
template<typename T>
const T &Blob<T>::operator [](size_type i) const {
	// if i is too big, check function will throw, preventing access to a nonexistent element
	check(i, "subscript out of range");
	return (*data)[i];
}
template <typename T> void Blob<T>::pop_back() {
	check(0, "pop_back on empty Blob");
	data->pop_back();
}

template <typename T>
Blob<T>::Blob():data(std::make_shared<std::vector<T>>()) {
}
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {
}


// 若试图访问一个不存在的元素 BlobPtr抛出一个异常
template <typename T> class BlobPtr {
	friend bool operator == <T>
		(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
	friend bool operator < <T>
		(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
public:
	BlobPtr():curr(0){}
	BlobPtr(Blob<T> &a, size_t sz = 0) :
		wptr(a.data), curr(sz) {
	}
	T &operator*()const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	// 递增和递减
	BlobPtr &operator++();  // 前置
	BlobPtr &operator--();

	BlobPtr operator++(int);  // 后置递增
	BlobPtr operator--(int);

private:
	// 若检查成功 check返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<T>>
		check(std::size_t, const std::string &)const;
	// 保存一个weak_ptr，表示底层vector可能被销毁
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr; // 数组中的当前位置
};

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string &msg)const {
	auto ret = wptr.lock();  // vector是否还存在
	if (!ret) {
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size()) {
		throw std::out_of_range(msg);
	}
	return ret;   // 否则 返回指向vector的shared_ptr
}
template <typename T>
BlobPtr<T> &BlobPtr<T>::operator ++() {
	// if curr already points past the end of the container, can't increment it
	check(curr, "increment past end of StrBlob");
	++curr;
	return *this;
}

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator --() {
	--curr;
	check(curr, "decrement past begin of BlobPtr");

	return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {    // 返回类型
	BlobPtr ret = *this;
	++ *this;
	return ret;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator --(int) {
	BlobPtr ret = *this;
	-- *this;

	return ret;
}

template <typename T> bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
	if (lhs.wptr.lock() != rhs.wptr.lock()) {
		throw std::runtime_error("ptrs to diffferent Blobs!");
	}
	return lhs.curr == rhs.curr;
}

template <typename T> bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
	if (lhs.wptr.lock() != rhs.wptr.lock()) {
		throw std::runtime_error("ptrs to diffferent Blobs!");
	}
	return lhs.curr < rhs.curr;
}

#endif