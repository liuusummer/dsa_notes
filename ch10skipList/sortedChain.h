#ifndef SortedChain_
#define SortedChain_
#include <iostream>
#include "dictionary.h"
#include "pairNode.h"
using namespace std;
template <class K,class E>
class sortedChain :public dictionary<K, E> {
public:
	sortedChain() { firstNode = nullptr; dSize = 0; }
	~sortedChain();

	bool empty()const { return dSize == 0; }
	int size()const { return dSize; }
	pair<const K, E> *find(const K &)const;
	void erase(const K &);
	void insert(const pair<const K, E> &);
	void output(ostream &out)const;
protected:
	pairNode<K, E> *firstNode;   // pointer to first node in chain
	int dSize;      // number of elements in dictionary
};

template <class K,class E>
sortedChain<K, E>::~sortedChain() {
	while (firstNode != nullptr) {
		pairNode<K, E> *nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template <class K,class E>
pair<const K, E> *sortedChain<K, E>::find(const K &theKey)const {
	// ����ƥ�����Ե�ָ��
	// ���������ƥ������ԣ�����NULL
	pairNode<K, E> *currentNode = firstNode;
	// �����ؼ���ΪtheKey������
	while (currentNode != nullptr
		&& currentNode->element.first != theKey) {
		currentNode = currentNode->next;
	}
	// �ж��Ƿ�ƥ��
	if (currentNode != nullptr 
		&& currentNode->element.first == theKey) {
		// �Ҵ�ƥ������
		return &currentNode->element;
	}
	// ��ƥ�������
	return nullptr;
}

template <class K,class E>
void sortedChain<K, E>::insert(const pair<const K, E> &thepair) {
	// ���ֵ��в���thepair
	// �����Ѿ����ڵ�ƥ�������
	pairNode<K, E> *p = firstNode, *tp = nullptr;   
	// �ƶ�ָ��tp,ʹthepair���Բ���tp�ĺ���
	while (p != nullptr && p->element.first < thepair.first) {
		tp = p;
		p = p->next;
	}
	// ����Ƿ���ƥ�������
	if (p != nullptr && p->element.first == thepair.first) {
		// �滻��ֵ
		p->element.second = thepair.second;
		return;
	}

	// ��ƥ������ԣ�Ϊthepair�����½ڵ�
	pairNode<K, E> *newNode = new pairNode<K, E>(thepair, p);
	// ��tp֮�����
	if (tp == nullptr) {
		firstNode = newNode;
	}
	else {
		tp->next = newNode;
	}

	dSize++;
	return;
}


//void erase(const K &);
//void insert(const pair<const K, E> &);
//void output(ostream &out)const;
template<class K,class E>
void sortedChain<K, E>::erase(const K &theKey) {
	pairNode<K, E> *p = firstNode, *tp = nullptr;
	// �����ؼ���ΪtheKey������
	while (p != nullptr && p->element.first < theKey) {
		tp = p;
		p = p->next;
	}
	// ȷ���Ƿ�ƥ��
	if (p != nullptr && p->element.first == theKey) {
	// �ҵ�һ��ƥ�������
		// ��������ɾ��p
		if (tp == nullptr) {
			firstNode = p->next;  // p�ǵ�һ���ڵ�
		}
		else {
			tp->next = p->next;
		}
		delete p;
		dSize--;
	}
}

template <class K,class E>
void sortedChain<K, E>::output(ostream &out)const 
	{// Insert the chain elements into the stream out.
		for (pairNode<K, E> *currentNode = firstNode;
			currentNode != NULL;
			currentNode = currentNode->next)
			out << currentNode->element.first << " "
			<< currentNode->element.second << "  ";
	}

// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, const sortedChain<K, E> &x) 	{
x.output(out); return out;}



#endif