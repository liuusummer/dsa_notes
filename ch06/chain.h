#ifndef CHAIN_H_
#define CHAIN_H_
#include <iostream>
#include "D:\\dsa_notes\\ch05\\linearList.h"
#include "D:\\dsa_notes\\myExceptions.h"
// 链表节点的结构定义
template <class T>
struct chainNode {
	// 数据成员
	T element;
	chainNode<T> *next;

	// 方法
	chainNode() {}
	chainNode(const T&element) {
		this->element = element;
	}
	chainNode(const T &element, chainNode<T> *next) {
		this->element = element;
		this->next = next;
	}
};

template <class T>
class chain :public linearList<T> {
public:
	// constructor,copy constructor,destructor
	chain(int initialCapacity = 10);
	chain(const chain<T> &);
	~chain();

	// 抽象数据类型ADT的方法
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;

protected:
	void checkIndex(int theIndex)const;
			// 如果索引无效，抛出异常
	chainNode<T> *firstNode;   // 指向链表第一个节点的指针
	int listSize;				// 线性表的元素个数
};
template<class T>
chain<T>::chain(int initialCapacity) {   
	// constructor
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initialcapacity = " << initialCapacity
			<< "Must be > 0.";
		throw illegalParameterValue(s.str());
	}
	firstNode = nullptr;
	listSize = 0;
}
template <class T>
chain<T>::chain(const chain<T> &theList) {
	// copy constructor
	listSize = theList.listSize;

	if (listSize == 0) {
		// 链表theList为空
		firstNode = nullptr;
		return;
	}

	// 链表 theList非空
	chainNode<T> *sourceNode = theList.firstNode;
				// 要复制链表theList的节点
	firstNode = new chainNode<T>(sourceNode->element);
					// 复制链表theList的头节点
	chainNode<T> *targetNode = firstNode;
					// targetNode指向目的链表的最后一个节点

	// 开始复制其他元素
	while (sourceNode != nullptr) {
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr;  // 链表结束
}
template <class T>
chain<T>::~chain() {
	// destructor 删除链表所有节点
	while (firstNode != nullptr) {
		// 删除首节点
		chainNode<T> *next = firstNode->next;
		delete firstNode;

		firstNode = next;
	}
}

// checkIndex
template<class T>
void chain<T>::checkIndex(int theIndex)const {
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "theIndex = " << theIndex << " ,size = " << listSize;
		throw illegalIndex(s.str());
	}
}
// get
template<class T>
T &chain<T>::get(int theIndex)const {
	// 返回索引是theIndex的元素
	// 若该元素不存在则抛出异常
	checkIndex(theIndex);

	// 移向所需要的节点
	chainNode<T> *currentNode = firstNode;
	for (int i = 0; i != theIndex; i++) {
		currentNode = currentNode->next;
	}
	return currentNode->element;
}




#endif
