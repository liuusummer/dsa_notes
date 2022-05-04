#ifndef StrVec_h_
#define StrVer_h_
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
using std::cout;

class StrVec {
public:
	// allocate��Ա����Ĭ�ϳ�ʼ��
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {};
	// ����һ��initialize_list�����Ĺ��캯��
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec &);  // copy constructor
	StrVec &operator=(const StrVec &);  // copy assignment operator
	~StrVec();    // destructor

	void push_back(const std::string &);
	void pop_back();
	size_t size()const { return first_free - elements; }
	size_t capacity()const { return cap - elements; }
	std::string *begin() { std::cout << "#1\n"; return elements; }
	std::string *end() { std::cout << "#2\n"; return first_free; }
	const std::string *begin()const { std::cout << "#3\n"; return elements; }
	const std::string *end()const { std::cout << "#4\n"; return first_free; }
	const std::string *cbegin()const { std::cout << "#5\n"; return elements; }
	const std::string *cend() const { std::cout << "#6\n"; return first_free; }

	bool empty() { return cbegin() == cend(); }

	
	// reserve() resize()
	void reserve(size_t);
	void resize(size_t,const std::string & = std::string());

private:
	static std::allocator<std::string> alloc;   // ����Ԫ��

	// �� ���Ԫ�صĺ��� ��ʹ��
	void chk_n_alloc() {
		if ((size() == capacity())) {
			reallocate();
		}
	}

	// ���ߺ���  ���������캯������ֵ�����������������ʹ��
	std::pair<std::string *, std::string *> alloc_n_copy
	(const std::string *, const std::string *);

	void free();  // ����Ԫ�ز��ͷ��ڴ�
	void reallocate();   // ��ø����ڴ沢��������Ԫ��
	std::string *elements;    // ָ��������Ԫ�ص�ָ��
	std::string *first_free;   // ָ�������һ������Ԫ�ص�ָ��
	std::string *cap;     // ָ������β��λ�õ�ָ��

};

// push_back
void StrVec::push_back(const std::string &s) {
	chk_n_alloc();  // ȷ���пռ�������Ԫ��
	// ��first_freeָ���Ԫ���й���s�ĸ���
	alloc.construct(first_free++, s);
}

StrVec::StrVec(std::initializer_list<std::string> il):StrVec() {
	for (const auto &s : il) {
		push_back(s);
	}
}

std::pair<std::string*,std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
	// ����ռ��Ա��������Χ��Ԫ��
	auto data = alloc.allocate(e - b);
	// ��ʼ��������һ��pair 
	// pair.first ��data ָ�������ڴ�Ŀ�ʼλ��
	// second ����unitialized_copy�ķ���ֵ  ֻ�����һ������Ԫ��֮���λ��
	return { data,std::uninitialized_copy(b,e,data) };
}
void StrVec::free() {
	if (elements) {
		//for (auto p = first_free; p != elements;/*��*/) {
		//	alloc.destroy(--p);
		//}
		for_each(elements, first_free, [](std::string &p) {alloc.destroy(&p); });
		alloc.deallocate(elements, cap - elements);
	}
}
StrVec::StrVec(const StrVec &s) {
	// ����alloc_n_copy����ռ���������s��һ�����Ԫ��
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::~StrVec() {
	free();
}
StrVec &StrVec::operator=(const StrVec &rhs) {
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

// reallocate��Ա
void StrVec::reallocate() {
	// �����䵱ǰ��С�������ڴ�ռ�
	auto newcapacity = size() ? 2 * size() : 1;
	// �������ڴ�
	auto newdata = alloc.allocate(newcapacity);
	// �����ݴӾ��ڴ��ƶ������ڴ�
	auto dest = newdata;   // ָ������������һ������λ��
	auto elem = elements;   // ָ�����������һ������λ��
	for (size_t i = 0; i != size(); i++) {
		alloc.construct(dest++, std::move(*elem++));
	}
	free();   // �ƶ��������ͷž��ڴ�ռ�
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
void StrVec::pop_back() {
	if (size() > 0) {
		alloc.destroy(--first_free);
	}
}
void StrVec::reserve(size_t n) {
	if (n > capacity()) {
		auto new_first_elem = alloc.allocate(n);
		auto new_first_free = new_first_elem;
		auto old_first_element = elements;
		for (size_t i = 0; i != size(); i++) {
			alloc.construct(new_first_free++, std::move(*old_first_element++));
		}
		free();
		elements = new_first_elem;
		first_free = new_first_free;
		cap = elements + n;
	}
}
void StrVec::resize(size_t n, const std::string &s) {
	if (n > size()) {
		for (int i = n - size(); i != 0; i--) {
			push_back(s);
		}
	}
	else if(n < size()) {
		for (int i = size() - n; i != 0; --i) {
			pop_back();
		}
	}
}


#endif