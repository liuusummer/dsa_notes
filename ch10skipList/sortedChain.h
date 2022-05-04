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
	// 返回匹配数对的指针
	// 如果不存在匹配的数对，返回NULL
	pairNode<K, E> *currentNode = firstNode;
	// 搜索关键字为theKey的数对
	while (currentNode != nullptr
		&& currentNode->element.first != theKey) {
		currentNode = currentNode->next;
	}
	// 判断是否匹配
	if (currentNode != nullptr 
		&& currentNode->element.first == theKey) {
		// 找打匹配数对
		return &currentNode->element;
	}
	// 无匹配的数对
	return nullptr;
}

template <class K,class E>
void sortedChain<K, E>::insert(const pair<const K, E> &thepair) {
	// 往字典中插入thepair
	// 覆盖已经存在的匹配的数对
	pairNode<K, E> *p = firstNode, *tp = nullptr;   
	// 移动指针tp,使thepair可以插在tp的后面
	while (p != nullptr && p->element.first < thepair.first) {
		tp = p;
		p = p->next;
	}
	// 检查是否有匹配的数对
	if (p != nullptr && p->element.first == thepair.first) {
		// 替换旧值
		p->element.second = thepair.second;
		return;
	}

	// 无匹配的数对，为thepair建立新节点
	pairNode<K, E> *newNode = new pairNode<K, E>(thepair, p);
	// 在tp之后插入
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
	// 搜索关键字为theKey的数对
	while (p != nullptr && p->element.first < theKey) {
		tp = p;
		p = p->next;
	}
	// 确定是否匹配
	if (p != nullptr && p->element.first == theKey) {
	// 找到一个匹配的数对
		// 从链表中删除p
		if (tp == nullptr) {
			firstNode = p->next;  // p是第一个节点
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