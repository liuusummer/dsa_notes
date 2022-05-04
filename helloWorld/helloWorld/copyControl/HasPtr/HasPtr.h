#ifndef HasPtr_h_
#define HasPtr_h_
#include <iostream>
#include <string>

class HasPtr {
public:
	// 构造函数分配新的string和新的计数器 将计数器置为1
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {
	}
	// 拷贝构造函数拷贝所有三个成员 并递增计数器
	HasPtr(const HasPtr &ori) :ps(ori.ps), i(ori.i), use(ori.use) {
		++ *use;
	}
	HasPtr &operator=(const HasPtr &);

	std::string &get()const { return *ps; }
	void set(const std::string &s) { *ps = s; }
	~HasPtr();
private:
	std::string *ps;
	int i;
	size_t *use;  // 引用计数  用来记录有多少个对象共享*ps的成员
};
HasPtr &HasPtr::operator=(const HasPtr &rhs) {
	++ *rhs.use;
	if (-- * use) {
		delete use;
		delete ps;
	}
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this;
}
HasPtr::~HasPtr() {
	if (-- * use == 0) {  // 如果引用计数变为0
 		delete ps; // 释放string内存
		delete use;  // 释放计数器内存
	}
}



#endif