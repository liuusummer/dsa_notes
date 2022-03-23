#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_
#include <sstream>
#include "stack.h"
#include "D:\\dsa_notes\\myExceptions.h"
#include "D:\\dsa_notes\\changeLength1D.h"

template <class T>
class arrayStack : public stack<T> {
public:
	arrayStack(int initialCapacity = 10);
	arrayStack() { delete[]stack; }
	bool empty() const { return stackTop == -1; }
	int size()const { return stackTop + 1; }
	T &top() {
		if (stackTop == -1) {
			throw stackEmpty();
		}
		return stack[stackTop];
	}
	void pop() {
		if (stackTop == -1) {
			throw stackEmpty();
		}
		stack[stackTop--].~T();  // T的析构函数
	}
	void push(const T &theElement);
private:
	int stackTop;   // 当前栈顶
	int arrayLength; // 栈容量
	T *stack;        // 元素数组
};
template <class T>
arrayStack<T>::arrayStack(int initialCapacity) {
	// constructor
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << "must be >= 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1; // 空栈
}
template <class T>
void arrayStack<T>::push(const T &theElement) {
	if (stackTop == arrayLength - 1) {
		// 空间已满 容量加倍
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	// 在栈顶插入
	stack[++stackTop] = theElement;
}



#endif
