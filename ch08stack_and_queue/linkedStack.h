/* 定制 链表栈
	选择链表的左端作为栈顶
*/
#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_
#include <iostream>
#include <string>
#include "D:\\dsa_notes\\ch06\\chain.h"
#include "stack.h"
#include "D:\\dsa_notes\\myExceptions.h"
template <class T>
class linkedStack :public stack<T> {
public:
	linkedStack(int initialCapacity = 10) {
		stackTop = nullptr;
		stackSize = 0;
	}
	~linkedStack();
	bool empty()const {
		return (stackSize == 0);
	}
	int size()const {
		return stackSize;
	}
	T &top() {
		if (stackSize == 0) {
			throw stackEmpty();
		}
		return stackTop->element;
	}
	void pop();
	void push(const T &theElement);



private:
	chainNode<T>* stackTop;   // 栈顶指针
	int stackSize;   // 栈中元素个数
};
template <class T>
linkedStack<T>::~linkedStack() {
	while (stackTop != nullptr) {
		chainNode<T> *next = stackTop->next;
		delete stackTop;
		stackTop = next;
	}
}
template <class T>
void linkedStack<T>::pop() {
	// 删除栈顶元素
	if (stackSize == 0) {
		throw stackEmpty();
	}
	chainNode<T> *nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}
template <class T>
void linkedStack<T>::push(const T &theElement) {
	stackTop = new chainNode<T>(theElement, stackTop);
	stackSize++;
}

// 括号匹配
void printMatchedPairs(std::string expr) {
	linkedStack<int> s;
	// int length = (int)expr.size();
	auto length = expr.size();
	// 扫描表达式expr,寻找左括号和右括号
	for (size_t i = 0; i < length; i++) {
		if (expr.at(i) == '(') {
			s.push(i);
		}
		else if (expr.at(i) == ')') {
			// 从栈中删除匹配的左括号
			try {
				std::cout << s.top() << ' ' << i << std::endl;
				s.pop();
			}
			catch (stackEmpty) {
				// 栈为空，没有匹配的左括号
				std::cout << "No match for right parenthesis"
					<< " at " << i << std::endl;
			}
		}
	}
	// 栈不为空。剩余在栈中的左括号是不匹配的
	while (!s.empty()) {
		std::cout << "No match for left parenthesis at " << s.top() << std::endl;
		s.pop();
	}
}

// 汉诺塔-递归
void towersOfHanoi(int n, int x, int y, int z) {
	// 把塔x顶部的n个碟子移到塔y
	// 用塔z作为中转地
	if (n > 0) {
		towersOfHanoi(n - 1, x, z, y);
		std::cout << "Move top disk from tower " << x
			<< " to top of tower " << y << std::endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}
#endif

