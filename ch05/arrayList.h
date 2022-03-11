#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_


/*
* 定义抽象类linearList的派生类arrayList
* arrayList是一个具体类，必须实现抽象类linearList的所有方法。还包括linearList没有声明的方法
* 方法capacity给出的是数组element当前的长度
* 方法checkIndex要确定一个元素在范围0到listSize-1内的索引
*/
#include <iostream>
#include "D:\\dsa_notes\\myExceptions.h"
#include "linearList.h"
#include "D:\\dsa_notes\\changeLength1D.h"
#include <string>
#include <sstream>
#include <algorithm>

template<class T>
class arrayList : public linearList<T> {
public:
	// 构造函数、拷贝构造函数、析构函数
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T> &);
	~arrayList() { delete[]element; }

	// ADT方法
	bool empty()const { return listSize == 0; }
	int size()const { return listSize; }
	T &get(int theIndex)const;
	int indexOf(const T &theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T &theElement);
	void output(std::ostream &out)const;

	// 其他方法
	int capacity()const { return arrayLength; }
	
	//// 类arrayList的一个迭代器
	//class iterator;
	//iterator begin() { return iterator(element); }
	//iterator end() { return iterator(element + listSize); }

	//class iteraotr {
	//public:
	//	// 用typedef实现双向迭代器
	//	typedef bidirectional_iterator_tag iterator_category;
	//	typedef T value_type;
	//	typedef ptrdiff_t difference_type;
	//	typedef T *pointer;
	//	typedef T &reference;

	//	// 构造函数
	//	iterator(T *thePosition = 0) { position = thePosition; }

	//	// 解引用操作符
	//	T &operator*()const { return *position; }
	//	T *operator->()const { return &*position; }

	//	// 迭代器的值增加
	//	iterator &operator++() {   // 前加
	//		++position; return *this;
	//	}
	//	iterator operator++(int) {   // 后加
	//		iterator old = *this;
	//		++position;
	//		return old;
	//	}

	//	// 迭代器的值减少
	//	iterator &operator--() {
	//		--position; return *this;
	//	}
	//	iterator operator--(int) {
	//		iterator old = *this;
	//		--postion;
	//		return old;
	//	}
	//	// 测试是否相等
	//	bool operator!=(const iterator right)const {
	//		return position != right.position;
	//	}
	//	bool operator==(const iterator right)const {
	//		return position == right.position;
	//	}
	//protected:
	//	T *position;   // 指向表元素的指针
	//};
protected:
	void checkIndex(int theIndex)const;
	// 若索引theIndex无效，则抛出异常
	T *element;    // 存储线性表元素的一维数组
	int arrayLength;  // 一维数组的容量
	int listSize;     // 线性表的元素个数
};

// 构造函数和拷贝构造函数
template <class T>
arrayList<T>::arrayList(int initialCapacity) { // 构造函数
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial Capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList) {   // 拷贝构造函数
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int theIndex)const {   // 确定索引theIndex在0和listSize-1之间
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}
template <class T>
T &arrayList<T>::get(int theIndex)const {  // 返回索引是theIndex的元素
	// 若此元素不存在，则抛出异常
	checkIndex(theIndex);
	return element[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement)const {
	// 返回元素theElement第一次出现时的索引
	// 若该元素不存在，则返回-1

	// 查找元素theElement
	int theIndex = (int)(find(element, element + listSize, theElement) - element);
	// 确定元素是否找到
	if (theIndex == listSize) {  // 没找到
		return -1;
	}
	else {
		return theIndex;
	}
}
template <class T>
void arrayList<T>::erase(int theIndex) {  // 删除索引为theIndex的元素
	// 如果元素不存在，则抛出异常
	checkIndex(theIndex);
	// 确定是有效索引后，移动其索引大于theIndex的元素
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	// listSize的值-1
	element[--listSize].~T();   // 析构原来的最后一个元素
}
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement) { // 在theIndex位置插入值theElement
	if (theIndex<0 || theIndex>listSize) {
		// 无效索引
		std::ostringstream s;
		s << "index = " << theIndex << "size = " << listSize;
		throw illegalIndex(s.str());
	}
	// 有效索引，确定数组是否已满
	if (listSize == arrayLength) {
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	// 把元素向右移动一个位置
	/*copy_backward像 copy() 那样复制元素，但是从最后一个元素开始直到第一个元素*/
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	// 插入元素
	element[theIndex] = theElement;
	listSize++;
}
template <class T>
void arrayList<T>::output(std::ostream &out)const { // 把线性表插入到输出流
	copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}
template <class T>
std::ostream &operator<<(std::ostream &out, const arrayList<T>&x) {
	x.output(out);
	return out;
}
#endif
