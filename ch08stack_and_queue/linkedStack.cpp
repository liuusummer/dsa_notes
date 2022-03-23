#include <iostream>
#include "linkedStack.h"
#include "D:\\dsa_notes\\myExceptions.h"

using std::endl;
using std::cout;


int main() {

	//linkedStack<int> s;
	//s.push(10);
	//s.push(20);
	//s.push(30);
	//s.push(30);

	//// test empty and size
	//if (s.empty())
	//	cout << "The stack is empty" << endl;
	//else
	//	cout << "The stack is not empty" << endl;

	//cout << "The stack size is " << s.size() << endl;

	//while (!s.empty()) {
	//	cout << "Stack top is " << s.top() << endl;
	//	s.pop();
	//	cout << "Popped top element" << endl;
	//}

	// std::string test("(a+b))(");
	//std::string test("(a*(b+c)+d)");
	// printMatchedPairs(test);
	towersOfHanoi(3, 1, 2, 3);
	return 0;
}
