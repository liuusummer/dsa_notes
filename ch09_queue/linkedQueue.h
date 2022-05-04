/* 队列的链表描述 */
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
	// 删除队首元素
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
	// 把元素theElement插入到队尾
	// 申请新元素节点
	chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
	// 把新节点插到队尾
	if (queueSize == 0) {
		queueFront = newNode;   // 队列空
	}
	else {
		queueBack->next = newNode;  // 队列不空
	}
	queueBack = newNode;
	queueSize++;
}

#endif
