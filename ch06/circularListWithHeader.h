/* ����ͷ�ڵ��ѭ������ */
#ifndef CIRCULARWITHHEADER_H_
#define CIRCULARWITHHEADER_H_
#include "D:\\dsa_notes\\myExceptions.h"
#include <iostream>
#include <sstream>
#include <string>
template <class T>
struct chainNode {
	// �ڵ㶨��

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
	chainNode<T> *headerNode;   // ָ��ͷ�ڵ��ָ��
	int listSize;     // �����е�Ԫ�ظ���
};
template <class T>
circularListWithHeader<T>::circularListWithHeader() {
	// constructor
	// ����������   ͷ�ڵ��ָ��ָ���Լ�
	headerNode = new chainNode<T>();
	headerNode = headerNode->next;
	listSize = 0;
}
template <class T>
int circularListWithHeader<T>::indexOf(const T &theElement)const {
	// ����Ԫ��theElement�״γ��ֵ�����
	// ����Ԫ�ز����ڣ��򷵻�-1

	// ��Ԫ�ش���ͷ�ڵ���
	headerNode->element = theElement;
	// ������������Ԫ��theElment
	chainNode<T> *currentNode = headerNode->next;
	// ��ǰ�ڵ������
	int index = 0;
	while (currentNode->element != theElement) {
		// �ƶ�����һ���ڵ�
		currentNode = currentNode->next;
		index++;
	}

	// ȷ���Ƿ��ҵ�Ԫ�� theElement
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
	// �������  �����׳��쳣
	if (theIndex < 0 || theIndex > listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << ",listSize = " << listSize;
		throw illegalIndex(s.str());
	}

	/*
	* 
	* if (theIndex == 0) {
		// ���׽ڵ�λ�ò���
		headerNode->next = new chainNode<T>(theElement, headerNode->next);
	}
	else {
		// ����λ��
		// �ҵ�ǰ���ڵ�
		chainNode<T> *p = headerNode;
		for (int i = 0; i < theIndex; i++) {
			p = p->next;
		}
		// p������½ڵ�
		p->next = new chainNode<T>(theElement,p->next)
	} 
	*/
	// ���Ժϲ������ÿ����Ƿ���ͷ�ڵ�	
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
