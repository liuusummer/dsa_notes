/* ���е��������� */
/* derived from ADT queue*/
#ifndef LINKEDQUEUE_H_
#define LINKEDQUEUE_H_
#include "queue.h"
#include "D:\\dsa_notes\\chainNode.h"
#include "D:\\dsa_notes\\myExceptions.h"
#include <sstream>
template <class T>
class linkedQueue :public queue<T> {
public:
	linkedQueue(int initalCapacity = 10) {
		queueFront = nullptr;
		queueBack = nullptr;
		queueSize = 0;
	}
	~linkedQueue();
	bool empty()const {
		return queueSize == 0;
	}
	int size()const {
		return queueSize;
	}
	T &front() {
		if (queueSize == 0) {
			throw queueEmpty();
		}
		return queueFront->element;
	}
	T &back() {
		if (queueSize == 0) {
			throw queueEmpty();
		}
		return queueBack->element;
	}
	void pop();
	void push(const T &theElement);
private:
	chainNode<T> *queueFront;   // pointer to queue front
	chainNode<T> *queueBack;    // pointer to queue back
	int queueSize;              // numbers of elements in queue
};

template <class T>
linkedQueue<T>::~linkedQueue() {
	// destructor
	while (queueFront != nullptr) {
		chainNode<T> *nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
}
template <class T>
void linkedQueue<T>::pop() {
	// ɾ������Ԫ��
	if (queueFront == nullptr) {
		throw queueEmpty();
	}
	chainNode<T> *nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}
template<class T>
void linkedQueue<T>::push(const T &theElement) {
	// ��Ԫ��theElement���뵽��β
	// ������Ԫ�ؽڵ�
	chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
	// ���½ڵ�嵽��β
	if (queueSize == 0) {
		queueFront = newNode;   // ���п�
	}
	else {
		queueBack->next = newNode;  // ���в���
	}
	queueBack = newNode;
	queueSize++;
}

#endif
