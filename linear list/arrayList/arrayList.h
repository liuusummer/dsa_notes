#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
#include "linearList.h"
#include <iostream>
#include "D:\\dsa\\myExceptions.h"
#include "D:\\dsa\\changeLength1D.h"
#include <string>
#include <sstream>
#include <algorithm>
/*
* 定义抽象类linearList的派生类arrayList
* arrayList是一个具体类，必须实现抽象类linearList的所有方法。还包括linearList没有声明的方法
* 方法capacity给出的是数组element当前的长度
* 方法checkIndex要确定一个元素在范围0到listSize-1内的索引
*/

template <typename T> class arrayList;
// operator << 
template<typename T>
std::ostream &operator<<(std::ostream &, const arrayList<T> &);


template<typename T>
class arrayList : public linearList<T> {
public:
	// constructor  copy constructor destructor
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T> &);
	~arrayList() { delete[]element; }

	// ADT方法
	virtual bool empty()const override{ return listSize == 0; }
	virtual int size()const override{ return listSize; }
	virtual T &get(int theIndex)const override;
	virtual int indexOf(const T &theElement)const override;
	virtual void erase(int theIndex) override;
	virtual void insert(int theIndex, const T &theElement) override;
	virtual void output(std::ostream &out)const override;

	// 其他方法
	int capacity()const { return arrayLength; }

protected:
	void checkIndex(int theIndex)const;
	// 若索引theIndex无效，则抛出异常
	T *element;    // 存储线性表元素的一维数组
	int arrayLength;  // 一维数组的容量
	int listSize;     // 线性表的元素个数
};


#endif
