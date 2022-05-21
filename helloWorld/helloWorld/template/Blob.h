#ifndef Template_h_
#define Template_h_
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <stdexcept>

// 16.19��ӡ�������� ʹ��������size_type ��size()��Ա
template <typename Container>
std::ostream &print(const Container &container, std::ostream &os) {
	for (typename Container::size_type i = 0; i < container.size(); i++) {
		os << container[i] << " ";
	}
	return os;
}
// 16.20 ��ӡ��������  ʹ�õ�����
//template <typename Container>
//std::ostream &print(const Container &container, std::ostream &os) {
//	for (auto curr = container.cbegin(); curr != container.cend(); curr++) {
//		os << *curr << " ";
//	}
//	return os;
//}
// ���������� �Ը���ָ��ִ��delete
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




template <typename> class BlobPtr;   // ǰ������  == template<typename T>class BlobPtr(why?)

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
	// ���ܵ������Ĺ��캯��  ��Աģ��
	template <typename It>
	Blob(It b, It e);

	// Blob�е�Ԫ����Ŀ
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }

	// ��Ӻ�ɾ��Ԫ��
	void push_back(const T &t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();

	// Ԫ�ط���
	T &back();
	T &operator[](size_type i);

	const T &back()const;
	const T &operator[](size_type i)const;
private:

	std::shared_ptr<std::vector<T>> data;
	// ��data[i]��Ч ���׳�msg
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


// ����ͼ����һ�������ڵ�Ԫ�� BlobPtr�׳�һ���쳣
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
	// �����͵ݼ�
	BlobPtr &operator++();  // ǰ��
	BlobPtr &operator--();

	BlobPtr operator++(int);  // ���õ���
	BlobPtr operator--(int);

private:
	// �����ɹ� check����һ��ָ��vector��shared_ptr
	std::shared_ptr<std::vector<T>>
		check(std::size_t, const std::string &)const;
	// ����һ��weak_ptr����ʾ�ײ�vector���ܱ�����
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr; // �����еĵ�ǰλ��
};

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string &msg)const {
	auto ret = wptr.lock();  // vector�Ƿ񻹴���
	if (!ret) {
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= ret->size()) {
		throw std::out_of_range(msg);
	}
	return ret;   // ���� ����ָ��vector��shared_ptr
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
BlobPtr<T> BlobPtr<T>::operator++(int) {    // ��������
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