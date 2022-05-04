#ifndef HasPtr_h_
#define HasPtr_h_
#include <iostream>
#include <string>

class HasPtr {
public:
	// ���캯�������µ�string���µļ����� ����������Ϊ1
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {
	}
	// �������캯����������������Ա ������������
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
	size_t *use;  // ���ü���  ������¼�ж��ٸ�������*ps�ĳ�Ա
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
	if (-- * use == 0) {  // ������ü�����Ϊ0
 		delete ps; // �ͷ�string�ڴ�
		delete use;  // �ͷż������ڴ�
	}
}



#endif