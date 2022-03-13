#ifndef CHAIN_H_
#define CHAIN_H_
#include <iostream>
#include "D:\\dsa_notes\\ch05\\linearList.h"
#include "D:\\dsa_notes\\myExceptions.h"
// ����ڵ�Ľṹ����
template <class T>
struct chainNode {
	// ���ݳ�Ա
	T element;
	chainNode<T> *next;

	// ����
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

	// ������������ADT�ķ���
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;

protected:
	void checkIndex(int theIndex)const;
			// ���������Ч���׳��쳣
	chainNode<T> *firstNode;   // ָ�������һ���ڵ��ָ��
	int listSize;				// ���Ա��Ԫ�ظ���
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
		// ����theListΪ��
		firstNode = nullptr;
		return;
	}

	// ���� theList�ǿ�
	chainNode<T> *sourceNode = theList.firstNode;
				// Ҫ��������theList�Ľڵ�
	firstNode = new chainNode<T>(sourceNode->element);
					// ��������theList��ͷ�ڵ�
	chainNode<T> *targetNode = firstNode;
					// targetNodeָ��Ŀ����������һ���ڵ�

	// ��ʼ��������Ԫ��
	while (sourceNode != nullptr) {
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr;  // �������
}
template <class T>
chain<T>::~chain() {
	// destructor ɾ���������нڵ�
	while (firstNode != nullptr) {
		// ɾ���׽ڵ�
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
	// ����������theIndex��Ԫ��
	// ����Ԫ�ز��������׳��쳣
	checkIndex(theIndex);

	// ��������Ҫ�Ľڵ�
	chainNode<T> *currentNode = firstNode;
	for (int i = 0; i != theIndex; i++) {
		currentNode = currentNode->next;
	}
	return currentNode->element;
}




#endif
