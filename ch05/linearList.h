#ifndef LINEARLIST_H_
#define LINEARLIST_H_
#include <iostream>
// 一个线性表的抽象描述
template <class T>
class linearList {
public:
	virtual ~linearList() {};
	//当且仅当线性表为空返回true
	virtual bool empty()const = 0;
	// 返回线性表元素的个数
	virtual int size()const = 0;
	// 返回索引为theIndex的元素
	virtual T &get(int theIndex)const = 0;
	// 返回元素theElement第一次出现时的索引
	virtual int indexOf(const T &theElement)const = 0;
	// 删除索引为theIndex的元素
	virtual void erase(int theIndex) = 0;
	// 把theElement插入线性表中索引为theIndex的位置上
	virtual void insert(int theIndex, const T &theElement) = 0;
	// 把线性表插入输出流out
	virtual void output(std::ostream &out)const = 0;
};

#endif

