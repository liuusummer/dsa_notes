#ifndef CHAIN_H_
#define CHAIN_H_
#include <iostream>
#include <sstream>
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
	void binSort(int range);

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

template <class T>
int chain<T>::indexOf(const T &theElement)const {
	// 返回元素theElment首次出现的索引
	// 若该元素不存在，返回-1
	chainNode<T> *currentNode = firstNode;
	int index = 0;  // 当前节点的索引
	while (currentNode != nullptr && currentNode->element != theElement) {
		currentNode = currentNode->next;
		index++;
	}
	// 确定是否找到所需的元素
	if (currentNode == nullptr) {
		return -1;
	}
	else {
		return index;
	}
}

template <class T>
void chain<T>::erase(int theIndex) {
	// 删除索引为index的元素
	
	// 若该索引不存在，则抛出异常
	checkIndex(theIndex);

	// 索引有效，需找到要删除的元素节点
	chainNode<T> *deleteNode;  // deleteNode 指向要删除的节点
	if (theIndex == 0) {
		// 删除链表的首节点
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else {
		// 其他节点
		// 用指针p指向要删除的前驱节点
		chainNode<T> *p = firstNode;
		for (int i = 0; i < theIndex-1; i++) {
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;   // 删除deleteNode指向的节点
	}
	listSize--;
	delete deleteNode;
}
template <class T>
void chain<T>::insert(int theIndex, const T &theElement) {
	// 插入元素theElement并使其索引为theIndex
	if (theIndex <0 || theIndex>listSize) {
		// 无效索引
		std::ostringstream s;
		s << "theIndex = " << theIndex << ",listSize = " << listSize;
		throw illegalIndex(s.str());
	}
	// 在链表头插入
	if (theIndex == 0) {                                                                                                                                                                                                                      
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else {
		// 其他位置,找到索引为index-1的元素   即新元素的前驱
		chainNode<T> *p = firstNode;
		for (int i = 0; i < theIndex - 1; i++) {
			p = p->next;
		}
		// 在p之后插入
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
void chain<T>::binSort(int range) {// 对链表中的节点排序
	
	// 创建并初始化箱子
	/* ****每个箱子都以底部节点作为首节点，顶部节点作为尾节点 
	*******每个箱子都有两个指针，分别存储在数组bottem和top中，分别指向尾节点和头节点
	*******bottem[theBin]指向箱子theBin的尾节点
	* *****top[theBin]指向箱子theBin的首节点
	*/
	chainNode<T> **bottom, **top;
	bottom = new chainNode<T>*[range + 1];
	top = new chainNode<T>*[range + 1];   // 指向节点的指针的数组  bottem[i]是指向节点的指针

	for (int b = 0; b <= range; b++) {
		bottom[b] = nullptr;
	}

	// 把链表的节点分配到箱子
	for (; firstNode != nullptr; firstNode = firstNode->next) {
		// 把首节点firstNode添加到箱子中
		int theBin = firstNode->element;   // 元素类型转换为int
		if (bottom[theBin] == nullptr) {  // 箱子为空
			bottom[theBin] = top[theBin] = firstNode;
		}
		else {  // 箱子不空
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;
		}
	}

	// 把箱子中的节点收集到有序链表中
	chainNode<T> *y = nullptr;
	for (int theBin = 0; theBin <= range; theBin++) {
		if (bottom[theBin] != nullptr) {   // 如果箱子非空
			if (y == nullptr) {   // 对于第一个非空箱
				firstNode = bottom[theBin];  // firstNode
				y = top[theBin];  // 让y指向箱子顶部元素
			}
			else {    // 不是第一个非空箱
				y->next = bottom[theBin];// y是上一个箱子顶部元素
								// y-next 指向新箱子的底部
				y = top[theBin];  // 再让y指向新箱子顶部元素
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
