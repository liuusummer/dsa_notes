#include <iostream>
#include <string>
// #include "Blob.h"
using std::endl;
using std::cout;
template <typename T>
void f(T) {
	cout << "f(T)" << endl;
}

template <typename T>
void f(const T *) {
	cout << "f(const T *)" << endl;
}

template <typename T>
void g(T) {
	cout << "g(T)" << endl;
}
template <typename T>
void g(T *) {
	cout << "g(T *)" << endl;
}
template <typename T,typename ... Args>
void foo(const T &t, const Args&...rest) {
	cout << "sizeof...(Args) = " << sizeof...(Args) << endl;
	cout << "sizeof...(rest) = " << sizeof...(rest) << endl;
}

template <typename T>
std::ostream &print(std::ostream &os, const T &t) {
	return os << t << " ";
}
template <typename T,typename ...Args>
std::ostream &print(std::ostream &os, const T &t, const Args&...rest) {
	os << t << " ";
	return print(os, rest...);
}
int main() {
	
	// std::unique_ptr<int, DebugDelete> p(new int, DebugDelete());
	
	/*int i = 42, *p = &i;
	const int ci = 0, *p2 = &ci;
	f(p);*/

	/*int i = 0;
	double d = 3.14;
	std::string s = "how now brown cow";

	foo(i, s, 42, d);
	foo(s, 42, "hi");
	foo(d, s);
	foo("hi");*/

	int i = 100;
	std::string s("hello");
	print(cout, i, s, 42);

	return 0;
}
