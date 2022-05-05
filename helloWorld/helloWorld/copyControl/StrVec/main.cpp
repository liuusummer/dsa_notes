#include "StrVec.h"
#include <iostream>
#include <algorithm>
void print(const StrVec &sv) {
	std::cout << "<" << &sv << "> size: " << sv.size()
		<< " capacity: " << sv.capacity() << " contents:";
	for (const auto &s : sv)
		std::cout << " <" << s << ">";
	std::cout << std::endl;
}
using namespace std;
std::allocator<std::string> StrVec::alloc;  // ?? 注释掉error 无法解析的外部命令
// 原因是我们如果只是声明静态变量而没有初始化的话，
//编译器是不会为这个静态变量分配空间的，
//只有当初始化静态变量之后，
//编译器才会在内存的静态区给这个变量分配空间，
//这样程序才能在数据区找到这个变量并继续使用。
int main() {
	
	StrVec sv;
	print(sv);

	sv.push_back("s1"); print(sv);
	sv.push_back("s2"); print(sv);
	sv.push_back("s3"); print(sv);
	sv.push_back("s4"); print(sv);
	sv.push_back("s5"); print(sv);

	{
		StrVec sv2(sv); print(sv2);
		sv2.push_back("s6"); print(sv); print(sv2);
		sv.pop_back(); print(sv); print(sv2);
		sv = sv2; print(sv); print(sv2);
	}

	sv.reserve(sv.capacity() / 2); print(sv);
	sv.reserve(sv.capacity() * 2); print(sv);

	sv.resize(sv.size() + 2); print(sv);
	sv.resize(sv.size() + 2, "s7"); print(sv);
	sv.resize(sv.size() - 2); print(sv);
	sv.resize(sv.size() - 2, "s7"); print(sv);

	StrVec sv2{ "il1", "il2", "il3", "il4", "il5" }; print(sv2);
	StrVec sv3 = { "il1", "il2", "il3", "il4", "il5" }; print(sv3);

	sv3[1] = "test";
	print(sv3);
	return 0;
}