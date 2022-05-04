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
	// allocate成员进行默认初始化
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {};
	// 接受一个initialize_list参数的构造函数
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
	static std::allocator<std::string> alloc;   // 分配元素

	// 被 添加元素的函数 所使用
	void chk_n_alloc() {
		if ((size() == capacity())) {
			reallocate();
		}
	}

	// 工具函数  被拷贝构造函数、赋值运算符和析构函数所使用
	std::pair<std::string *, std::string *> alloc_n_copy
	(const std::string *, const std::string *);

	void free();  // 销毁元素并释放内存
	void reallocate();   // 获得更多内存并拷贝已有元素
	std::string *elements;    // 指向数组首元素的指针
	std::string *first_free;   // 指向数组第一个空闲元素的指针
	std::string *cap;     // 指向数组尾后位置的指针

};

// push_back
void StrVec::push_back(const std::string &s) {
	chk_n_alloc();  // 确保有空间容纳新元素
	// 在first_free指向的元素中构造s的副本
	alloc.construct(first_free++, s);
}

StrVec::StrVec(std::initializer_list<std::string> il):StrVec() {
	for (const auto &s : il) {
		push_back(s);
	}
}

std::pair<std::string*,std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
	// 分配空间以保存给定范围的元素
	auto data = alloc.allocate(e - b);
	// 初始化并返回一个pair 
	// pair.first 是data 指向分配的内存的开始位置
	// second 则是unitialized_copy的返回值  只想最后一个构造元素之后的位置
	return { data,std::uninitialized_copy(b,e,data) };
}
void StrVec::free() {
	if (elements) {
		//for (auto p = first_free; p != elements;/*空*/) {
		//	alloc.destroy(--p);
		//}
		for_each(elements, first_free, [](std::string &p) {alloc.destroy(&p); });
		alloc.deallocate(elements, cap - elements);
	}
}
StrVec::StrVec(const StrVec &s) {
	// 调用alloc_n_copy分配空间以容纳与s中一样多的元素
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

// reallocate成员
void StrVec::reallocate() {
	// 将分配当前大小两倍的内存空间
	auto newcapacity = size() ? 2 * size() : 1;
	// 分配新内存
	auto newdata = alloc.allocate(newcapacity);
	// 将数据从旧内存移动到新内存
	auto dest = newdata;   // 指向新数组中下一个空闲位置
	auto elem = elements;   // 指向旧数组中下一个空闲位置
	for (size_t i = 0; i != size(); i++) {
		alloc.construct(dest++, std::move(*elem++));
	}
	free();   // 移动完数据释放旧内存空间
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