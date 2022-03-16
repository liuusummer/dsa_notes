#ifndef CHAIN_H_
#define CHAIN_H_
#include <iostream>
#include <sstream>
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
	void binSort(int range);

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

template <class T>
int chain<T>::indexOf(const T &theElement)const {
	// ����Ԫ��theElment�״γ��ֵ�����
	// ����Ԫ�ز����ڣ�����-1
	chainNode<T> *currentNode = firstNode;
	int index = 0;  // ��ǰ�ڵ������
	while (currentNode != nullptr && currentNode->element != theElement) {
		currentNode = currentNode->next;
		index++;
	}
	// ȷ���Ƿ��ҵ������Ԫ��
	if (currentNode == nullptr) {
		return -1;
	}
	else {
		return index;
	}
}

template <class T>
void chain<T>::erase(int theIndex) {
	// ɾ������Ϊindex��Ԫ��
	
	// �������������ڣ����׳��쳣
	checkIndex(theIndex);

	// ������Ч�����ҵ�Ҫɾ����Ԫ�ؽڵ�
	chainNode<T> *deleteNode;  // deleteNode ָ��Ҫɾ���Ľڵ�
	if (theIndex == 0) {
		// ɾ��������׽ڵ�
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else {
		// �����ڵ�
		// ��ָ��pָ��Ҫɾ����ǰ���ڵ�
		chainNode<T> *p = firstNode;
		for (int i = 0; i < theIndex-1; i++) {
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;   // ɾ��deleteNodeָ��Ľڵ�
	}
	listSize--;
	delete deleteNode;
}
template <class T>
void chain<T>::insert(int theIndex, const T &theElement) {
	// ����Ԫ��theElement��ʹ������ΪtheIndex
	if (theIndex <0 || theIndex>listSize) {
		// ��Ч����
		std::ostringstream s;
		s << "theIndex = " << theIndex << ",listSize = " << listSize;
		throw illegalIndex(s.str());
	}
	// ������ͷ����
	if (theIndex == 0) {                                                                                                                                                                                                                      
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else {
		// ����λ��,�ҵ�����Ϊindex-1��Ԫ��   ����Ԫ�ص�ǰ��
		chainNode<T> *p = firstNode;
		for (int i = 0; i < theIndex - 1; i++) {
			p = p->next;
		}
		// ��p֮�����
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}
template <class T>
void chain<T>::output(std::ostream &out)const {
	chainNode<T> *currentNode = firstNode;
	while (currentNode != nullptr) {
		out << currentNode->element << " ";
		currentNode = currentNode->next;
	}
}
template <class T>
std::ostream &operator<<(std::ostream &os, const chain<T> &ch) {
	ch.output(os);
	return os;
}
template <class T>
void chain<T>::binSort(int range) {// �������еĽڵ�����
	
	// ��������ʼ������
	/* ****ÿ�����Ӷ��Եײ��ڵ���Ϊ�׽ڵ㣬�����ڵ���Ϊβ�ڵ� 
	*******ÿ�����Ӷ�������ָ�룬�ֱ�洢������bottem��top�У��ֱ�ָ��β�ڵ��ͷ�ڵ�
	*******bottem[theBin]ָ������theBin��β�ڵ�
	* *****top[theBin]ָ������theBin���׽ڵ�
	*/
	chainNode<T> **bottom, **top;
	bottom = new chainNode<T>*[range + 1];
	top = new chainNode<T>*[range + 1];   // ָ��ڵ��ָ�������  bottem[i]��ָ��ڵ��ָ��

	for (int b = 0; b <= range; b++) {
		bottom[b] = nullptr;
	}

	// ������Ľڵ���䵽����
	for (; firstNode != nullptr; firstNode = firstNode->next) {
		// ���׽ڵ�firstNode��ӵ�������
		int theBin = firstNode->element;   // Ԫ������ת��Ϊint
		if (bottom[theBin] == nullptr) {  // ����Ϊ��
			bottom[theBin] = top[theBin] = firstNode;
		}
		else {  // ���Ӳ���
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;
		}
	}

	// �������еĽڵ��ռ�������������
	chainNode<T> *y = nullptr;
	for (int theBin = 0; theBin <= range; theBin++) {
		if (bottom[theBin] != nullptr) {   // ������ӷǿ�
			if (y == nullptr) {   // ���ڵ�һ���ǿ���
				firstNode = bottom[theBin];  // firstNode
				y = top[theBin];  // ��yָ�����Ӷ���Ԫ��
			}
			else {    // ���ǵ�һ���ǿ���
				y->next = bottom[theBin];// y����һ�����Ӷ���Ԫ��
								// y-next ָ�������ӵĵײ�
				y = top[theBin];  // ����yָ�������Ӷ���Ԫ��
			}
		}
	}

	if (y != nullptr) {
		y->next = nullptr;
	}
	delete[]bottom;
	delete[]top;
}
#endif
