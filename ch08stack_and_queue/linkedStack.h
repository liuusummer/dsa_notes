/* ���� ����ջ
	ѡ������������Ϊջ��
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
	chainNode<T>* stackTop;   // ջ��ָ��
	int stackSize;   // ջ��Ԫ�ظ���
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
	// ɾ��ջ��Ԫ��
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

// ����ƥ��
void printMatchedPairs(std::string expr) {
	linkedStack<int> s;
	// int length = (int)expr.size();
	auto length = expr.size();
	// ɨ����ʽexpr,Ѱ�������ź�������
	for (size_t i = 0; i < length; i++) {
		if (expr.at(i) == '(') {
			s.push(i);
		}
		else if (expr.at(i) == ')') {
			// ��ջ��ɾ��ƥ���������
			try {
				std::cout << s.top() << ' ' << i << std::endl;
				s.pop();
			}
			catch (stackEmpty) {
				// ջΪ�գ�û��ƥ���������
				std::cout << "No match for right parenthesis"
					<< " at " << i << std::endl;
			}
		}
	}
	// ջ��Ϊ�ա�ʣ����ջ�е��������ǲ�ƥ���
	while (!s.empty()) {
		std::cout << "No match for left parenthesis at " << s.top() << std::endl;
		s.pop();
	}
}

// ��ŵ��-�ݹ�
void towersOfHanoi(int n, int x, int y, int z) {
	// ����x������n�������Ƶ���y
	// ����z��Ϊ��ת��
	if (n > 0) {
		towersOfHanoi(n - 1, x, z, y);
		std::cout << "Move top disk from tower " << x
			<< " to top of tower " << y << std::endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}
#endif

