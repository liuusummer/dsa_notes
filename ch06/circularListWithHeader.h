/* 带有头节点的循环链表 */
#ifndef CIRCULARWITHHEADER_H_
#define CIRCULARWITHHEADER_H_
#include "D:\\dsa_notes\\myExceptions.h"
#include <iostream>
#include <sstream>
#include <string>
template <class T>
struct chainNode {
	// 节点定义

	// data members
	T element;
	chainNode<T> *next;
	// methods
	chainNode(){
	}
	chainNode(const T &element) {
		this->element = element;
	}
	chainNode(const T &element, chainNode<T> *next) {
		this->element = element;
		this->next = next;
	}
};

template <class T>
class circularListWithHeader {
public:
	// constructor
	circularListWithHeader();

	// some methods
	int size()const { return listSize; }
	int indexOf(const T &t)const;
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;
protected:
	void checkIndex(int theIndex)const;
	chainNode<T> *headerNode;   // 指向头节点的指针
	int listSize;     // 链表中的元素个数
};
template <class T>
circularListWithHeader<T>::circularListWithHeader() {
	// constructor
	// 创建空链表   头节点的指针指向自己
	headerNode = new chainNode<T>();
	headerNode = headerNode->next;
	listSize = 0;
}
template <class T>
int circularListWithHeader<T>::indexOf(const T &theElement)const {
	// 返回元素theElement首次出现的索引
	// 若该元素不存在，则返回-1

	// 将元素存在头节点中
	headerNode->element = theElement;
	// 在链表中搜索元素theElment
	chainNode<T> *currentNode = headerNode->next;
	// 当前节点的索引
	int index = 0;
	while (currentNode->element != theElement) {
		// 移动到下一个节点
		currentNode = currentNode->next;
		index++;
	}

	// 确定是否找到元素 theElement
	if (currentNode == headerNode) {
		return -1;
	}
	else {
		return index;
	}
}
template <class T>
void circularListWithHeader<T>::checkIndex(int theIndex)const {
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << ",listSize = " << listSize;
		throw illegalIndex(s.str());
	}
}
template <class T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) {
	// 检查索引  不对抛出异常
	if (theIndex < 0 || theIndex > listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << ",listSize = " << listSize;
		throw illegalIndex(s.str());
	}

	/*
	* 
	* if (theIndex == 0) {
		// 在首节点位置插入
		headerNode->next = new chainNode<T>(theElement, headerNode->next);
	}
	else {
		// 其他位置
		// 找到前驱节点
		chainNode<T> *p = headerNode;
		for (int i = 0; i < theIndex; i++) {
			p = p->next;
		}
		// p后插入新节点
		p->next = new chainNode<T>(theElement,p->next)
	} 
	*/
	// 可以合并，不用考虑是否是头节点	
	chainNode<T> *p = headerNode;
	for (int i = 0; i < theIndex; i++)
		p = p->next;

	// insert after p
	p->next = new chainNode<T>(theElement, p->next);
	listSize++;
}

template <class T>
void circularListWithHeader<T>::output(std::ostream &out)const {
	for (chainNode<T> *currentNode = headerNode->next;
		currentNode != headerNode;
		currentNode = currentNode->next) {
		out << currentNode->element << " ";
	}
	
}
// overload <<
template <class T>
ostream &operator<<(std::ostream &out, const circularListWithHeader<T> &x) 	{
x.output(out); return out;}


#endif
